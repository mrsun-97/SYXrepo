extern crate interpolation;
use interpolation::basic::generate;
use interpolation::sort::lagrange_sort;
use interpolation::basic::fabs;
use std::f64;


fn main() {
    /*
    {   //课后作业部分
        let ax: [f64;3] = [-2.00, 2.00, 5.00];
        let ay: [f64;3] = [0.00, 3.00, 6.00];
        let (a, b) = (lagrange_sort(&ax[..], &ay[..], -1.2),
                      lagrange_sort(&ax[..], &ay[..], 1.2));
        println!("L(-1.2) = {:.*}", 14, a);
        println!("L(+1.2) = {:.*}", 14, b);
        let bx = [81.00, 100.00, 121.00];
        let by = [9.00, 10.00, 11.00];
        let a = lagrange_sort(&bx[..], &by[..], 105.0);
        println!("sqrt(105) = {:.*}\n\n", 14, a);
    }
    */

    //lab02
    println!("lab02: ");
    let arr_n = [5, 10, 20, 40];// N
    println!("(1)");
    for n in arr_n.iter() {     //n: 即为 N
        let fxy = |i: f64| -> f64 {-5.0+10.0*i/(*n as f64)};    //改函数为闭包
        let (ax, ay) = generate(fxy, *n, fx);
        let mut max = 0.0;
        for i in 0..501 {       //500 找误差最值
            let mut j = -5.0+10.0*(i as f64)/500.0;
            let k = lagrange_sort(&ax, &ay, j);
            let l = fx(j);
            j = fabs(l - k);
            if j > max {max = j};
        }
        println!("N = {},\t{}",n ,max);
    }
    println!("\n(2)");
    for n in arr_n.iter() {     //n同N
        let fxy = |i: f64| -> f64 {-5.0*f64::cos((2.0*i+1.0)/(2.0*(*n as f64)+2.0)*f64::consts::PI)};
        let (ax, ay) = generate(fxy, *n, fx);
        let mut max = 0.0;
        for i in 0..501 {       
            let mut j = -5.0+10.0*(i as f64)/500.0;
            let k = lagrange_sort(&ax, &ay, j);
            let l = fx(j);
            j = fabs(l - k);
            if j > max {max = j};
        }
        println!("N = {},\t{}",n ,max);
    }
}

//题中所给函数
fn fx(x: f64) -> f64 {
    1.0/(x*x+1.0)
}

