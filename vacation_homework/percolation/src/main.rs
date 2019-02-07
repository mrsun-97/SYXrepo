extern crate image;
use image::{
    ImageBuffer
};

use std::f64;
use std::cmp::{min, max};
use rand::{Rng,SeedableRng};
use rand_xoshiro::Xoshiro256StarStar;

const PI:f64 = f64::consts::PI;
const R1:f64 = 100.0;
const R2:f64 = 110.0;
const PHI:f64 = PI/2.0;

#[derive(Clone)]
struct Site {
    site: bool,
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
            site: false,
        }
    }

    fn hold(&mut self) {
        self.site = true;
    }

    fn inv(&mut self) {
        self.site = !self.site;
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
        let x0 = x0 * self.x_length as f64;
        let y0 = y0 * self.y_length as f64;
        let theta = (2.0*theta-1.0)*PI;
        //确定扫描范围，防止越界。
        let ya = max((y0-R2).floor() as usize, 0);
        let xa = max((x0-R2).floor() as usize, 0);
        let yb = min((y0+R2).ceil()  as usize, self.y_length-1);
        let xb = min((x0+R2).ceil()  as usize, self.x_length-1);
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

}

//给定两角度，求出二者之差，[0,pi]
fn modpi(theta1:f64, theta2:f64) -> f64 {
    let a:f64 = (theta1-theta2).abs();
    if a <=  PI {
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
    for _i in 0..5000 {
        g.put_one(&mut rng);
    }
    println!("finished calculating, now drawing...");
    let img1 = ImageBuffer::from_fn(x, y, |a, b| {
        if g.graph[b as usize][a as usize].site == false {
            //白背景
            image::Luma([255u8])
        } else {
            image::Luma([0u8])
        }
    });
    img1.save("img1.png").unwrap();
}

