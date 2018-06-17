extern crate ode45;
use ode45::solve;

fn main(){

    let f = |x:f64,y:f64| { -(x*y)*(x*y) };
    let yreal = |x:f64| {3.0/(1.0 + x*x*x)};
    /*
    let f = |x:f64,y:f64| { 2.0*x*(x-y) + 1.0 };
    let yreal = |x:f64| { 3.0*(-x*x).exp() + x };
    */
    let mut E: Vec<f64> = vec!();
    let h: f64 = 0.1;
    let b: f64 = 1.5;
    for i in 0..=3 {
        let k = 2.0_f64.powf(i as f64);
        let mut y = solve::rk4(&f, 0.0, 3.0,b, h/k);
        if let Some(e) = y.pop() {
            let e: f64 = (e - yreal(b)).abs();
            E.push(e);
            let o: f64 = (E[0]/E[i]).ln()/k.ln();
            println!("步长: {:<.4} , {:<20.14e} , {:<20.14e}", h/k, e, o);
        }
    }
    print!("\n");
    E.truncate(0);
    for i in 0..=3 {
        let k = 2.0_f64.powf(i as f64);
        let mut y = solve::adams(&f, 0.0, 3.0, b, h/k);
        if let Some(e) = y.pop() {
            let e: f64 = (e - yreal(b)).abs();
            E.push(e);
            let o: f64 = (E[0]/E[i]).ln()/k.ln();
            println!("步长: {:<.4} , {:<20.14e} , {:<20.14e}", h/k, e, o);
        }
    }
    
}