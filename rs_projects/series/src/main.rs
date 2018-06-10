use std::f64;

static DELTA: f64 = 1.0e-6;

fn main() {
    let arr = [0.0, 0.5, 1.0, f64::sqrt(2.0), 10.0, 100.0, 300.0];
    for x in arr.iter() {
        println!("{:<6.2} , {:<20.14e}", x, solve(*x));
    }
}


fn solve(x: f64) -> f64 {
    let mut sum: f64 = 0.0;
    let n = 1 + {
        if x > 0.0 {
            (1.0/(DELTA*(1.0 + 0.5*DELTA*f64::floor(x)))) as usize
        }
        else if x == 0.0 {
            f64::floor(1.0/DELTA - 0.5) as usize
        }
        else { panic!("We expect 'x' is positive, find x = {}" , x); }
    };
    let mut tmp: f64 = 0.0;
    for i in 1..=n {
        let k = i as f64;
        tmp = k*(k+x);
        tmp = 1.0/tmp;
        sum += tmp;
    }
    sum
}
