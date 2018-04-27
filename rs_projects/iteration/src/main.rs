extern crate iteration;
use iteration::iteration::newton as solve1;
use iteration::iteration::secant as solve2;

fn main(){
    println!("\n牛顿法");
    {
        let arr: [f64;4] = [0.1, 0.2, 0.9, 9.0];
        let f = |x| {(x*x/3.0-1.0)*x};
        let df = |x| {x*x-1.0};
        for &i in arr.iter() {
            let (value, count) = solve1(&f, &df, i);
            println!("初值 {:3} , {:<20.14e} , {}", i, value, count);
        }
    }
    
    println!("\n弦截法");
    {   
        let arr: [(f64,f64);4] = [(0.0,0.1), (0.1,0.2), (0.2,0.9), (8.0,9.0)];
        let f = |x| {(x*x/3.0-1.0)*x};
        for &(a, b) in arr.iter() {
            let (value, count) = solve2(&f, a, b);
            println!("初值 {:3} {:3} , {:<20.14e} , {}", a, b, value, count);
        }
    }

}