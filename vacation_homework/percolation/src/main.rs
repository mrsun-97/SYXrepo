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
    num: u16,
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
            num: 0_u16,
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

    fn mark(&mut self, num: u16) {
        self.sited = true;
        self.num = num;
    }

    fn erase(&mut self) {
        self.sited = false;
        self.num = 0;
    }

    fn is_sited(&self) -> Option<u16> {
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

    fn find_way(&mut self) -> u16 {
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
        let mut number: u16 = 3;
        //let mut tmp: u16;
        for yi in 1..=yd {
            for xj in 1..=xd {
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
        1_u16
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
    let mut g = Graph::new(x as usize, y as usize);
    let mut rng = Xoshiro256StarStar::seed_from_u64(2);
    for _i in 0..4000 {
        g.put_one(&mut rng);
    }
    println!("finished calculating, now drawing...");
    let img1 = ImageBuffer::from_fn(x, y, |a, b| {
        if g.graph[b as usize][a as usize].sited == false {
            //白背景
            image::Rgb([0xFF,0xFF,0xFF])
        } else {
            //黑图案
            image::Rgb([0x00,0x00,0x00])
        }
    });
    img1.save("img1.png").unwrap();
}

