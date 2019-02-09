extern crate image;
use image::{
    ImageBuffer
};

use std::f64;
//use std::cmp::{min, max};
use rand::{Rng,SeedableRng};
use rand_xoshiro::Xoshiro256StarStar;

const PI:f64 = f64::consts::PI;
const R1:f64 = 100.0;
const R2:f64 = 110.0;
const PHI:f64 = PI/2.0;

#[derive(Clone)]
struct Site {
    sited: bool,
    num: u32,
}

struct Graph {
    x_length: usize,
    y_length: usize,
    graph: Vec<Vec<Site>>,
}

#[allow(dead_code)]
impl Site {
    //! true  -> 1
    //! false -> 0
    fn new() -> Site {
        Site {
            sited: false,
            num: 0_u32,
        }
    }

    fn hold(&mut self) {
        self.sited = true;
        self.num = 0;
    }

    fn inv(&mut self) {
        self.sited = !self.sited;
        self.num = 0;
    }

    fn mark(&mut self, num: u32) {
        self.sited = true;
        self.num = num;
    }

    fn erase(&mut self) {
        self.sited = false;
        self.num = 0;
    }

    fn is_sited(&self) -> Option<u32> {
        if self.sited {
            Option::Some(self.num)
        }
        else {
            Option::None
        }
    }

}

impl Graph {
    fn new(x_length:usize, y_length:usize) -> Graph {
        Graph {
            x_length,
            y_length,
            //Graph[y][x], Graph[0][0]--upperleft
            graph: vec![vec![Site::new();x_length]; y_length],
        }
    }

    fn put_one<T: Rng>(&mut self, rng:&mut T) {
        let (x0, y0, theta) = rng.gen::<(f64,f64,f64)>();
        let x0 = x0 * (self.x_length as f64 + 2.0*R2) - R2;
        let y0 = y0 * (self.y_length as f64 + 2.0*R2) - R2;
        let theta = (2.0*theta-1.0)*PI;
        //确定扫描范围，防止越界。
        let ya = f64::max((y0-R2).floor(), 0.0) as usize;
        let xa = f64::max((x0-R2).floor(), 0.0) as usize;
        let yb = f64::min((y0+R2).ceil(), self.y_length as f64 - 1.0) as usize;
        let xb = f64::min((x0+R2).ceil(), self.x_length as f64 - 1.0) as usize;
        for i in ya..=yb {
            for j in xa..=xb {
                let x = j as f64 - x0;
                let y = i as f64 - y0;
                if modpi(f64::atan2(y,x), theta) <= PHI {
                    let r2 = x*x + y*y;
                    if r2 > R1*R1 && r2 <= R2*R2 {
                        self.graph[i][j].hold();
                    }
                }
            }
        }
    }//end fn

    fn find_way(&mut self) -> u32 {
        let xd = self.x_length-2;
        let yd = self.y_length-2;
        //初始化上下边界
        for i in 0..self.x_length {
            self.graph[0][i].mark(1);
            self.graph[yd+1][i].mark(2);
        }
        //截断左右边界
        for j in 1..=yd {
            self.graph[j][0].erase();
            self.graph[j][xd+1].erase();
        }
        //对每个可能独立的集团编号
        let mut number: u32 = 3;
        //let mut tmp: u32;
        for yi in 1..=yd {
            for xj in 1..=xd {
                if self.graph[yi][xj].is_sited() != None {
                    if let Some(tmp) = self.graph[yi-1][xj].is_sited() {
                        self.graph[yi][xj].mark(tmp);
                        continue;
                    }
                    if let Some(tmp) = self.graph[yi][xj-1].is_sited() {
                        self.graph[yi][xj].mark(tmp);
                        continue;
                    }
                    self.graph[yi][xj].mark(number);
                    number +=1;
                }
            }
        }
        println!("---> ");
        //定义一次遍历
        let mut f = |xa:usize,xb:usize,ya:usize,yb:usize| -> bool {
            let (x_range, dx) = if xa <= xb {
                ((xa..=xb).collect::<Vec<usize>>(), -1_isize)
            } else {
                ((xb..=xa).rev().collect::<Vec<usize>>(), 1_isize)
            };
            let (y_range, dy) = if ya <= yb {
                ((ya..=yb).collect::<Vec<usize>>(), -1_isize)
            } else {
                ((yb..=ya).rev().collect::<Vec<usize>>(), 1_isize)
            };

            let mut flag = false;   //标记是否有修改
            for y in y_range {
                for x in x_range.clone() {
                    if self.graph[y][x].is_sited() != None {
                        let mut num = u32::max_value();
                        if let Some(tmp) = self.graph[(y as isize+dy) as usize][x].is_sited() {
                            num = tmp;
                        }
                        if let Some(tmp) = self.graph[y][(x as isize+dx) as usize].is_sited() {
                            num = u32::min(num, tmp);
                        }
                        if num != u32::max_value() && num != self.graph[y][x].num {
                            flag = true;
                            self.graph[y][x].mark(num);
                        }
                    }
                }
            }
            flag
        };  //end cluster
        println!("begin loop");
        let mut count = 1_usize;
        while count <= 200 {
            let mut flag :bool;
            flag = f(1,xd,1,yd);
            flag = f(xd,1,1,yd) || flag;
            flag = f(xd,1,yd,1) || flag;
            flag = f(1,xd,yd,1) || flag;
            println!("{}",count);
            count += 1;
            if !flag { break }
        }
        f(1,xd,yd+1,yd+1);
        f(xd,1,yd+1,yd+1);
        self.graph[yd+1][1].num
    }
}

//给定两角度[-pi,pi]，求出二者之差，[0,pi]
fn modpi(theta1:f64, theta2:f64) -> f64 {
    let a:f64 = (theta1-theta2).abs();
    if a <= PI {
        a
    } else {
        2.0*PI - a
    }
}

//fn output();

fn main() {
    let x :u32= 10240;
    let y :u32= 10240;
    print!("generating lattice... ");
    let mut g = Graph::new(x as usize, y as usize);
    println!("done");
    print!("initializing random number generator... ");
    let mut rng = Xoshiro256StarStar::seed_from_u64(2);
    println!("done");
    print!("puting circles on the lattice... ");
    for _i in 0..4000 {
        g.put_one(&mut rng);
    }
    println!("done");
    println!("calculating...");
    g.find_way();
    println!("finished calculating, now drawing...");
    //绘图
    /*
    let ctab = vec![
        image::Rgb([0x66,0x33,0x33]),
        image::Rgb([0xFF,0x00,0x33]),
        image::Rgb([0x00,0x33,0xFF]),
    ];
    */
    let img1 = ImageBuffer::from_fn(x, y, |a, b| {
        let site = &g.graph[b as usize][a as usize];
        if !site.sited {
            //白背景
            image::Rgb([0xFF,0xFF,0xFF])
        } else {
            match site.num {
                1 => image::Rgb([0xFF,0x00,0x33]),  //red
                2 => image::Rgb([0x00,0x33,0xFF]),  //blue
                _ => image::Rgb([0x66,0x33,0x33]),
            }
        }
    });
    img1.save("img1.png").unwrap();
    println!("finished")
}

