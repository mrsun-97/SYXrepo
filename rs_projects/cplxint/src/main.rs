use std::f64;
extern crate cplxint;
use cplxint::integrate::t_integrate as ft;
use cplxint::integrate::s_integrate as fs;
use cplxint::integrate::def_pow;

fn main (){
    let f = |x| {f64::sin(x)};
    let I: f64 = f64::cos(1.0) - f64::cos(5.0);
    let t1 = ft(&f, 1.0, 5.0, 12);
    let t2 = fs(&f, 1.0, 5.0, 12);
    let mut e1: Vec<f64> = Vec::with_capacity(13);
    let mut e2: Vec<f64> = Vec::with_capacity(13);
    for i in &t1 {
        e1.push(f64::abs(I-i));     //存入对应误差
    }
    for i in 0..13 {
        println!("N = {:5},\t {:.*e},\t {:.*e}", def_pow(2,i), 14, e1[i], 12, f64::ln(e1[0]/e1[i])/((i as f64)*f64::ln(2.0)));
    }
    println!("");
    for i in &t2 {
        e2.push(f64::abs(I-i));
    }
    for i in 0..13 {
        println!("N = {:5},\t {:.*e},\t {:.*e}", def_pow(2,i), 14, e2[i], 12, f64::ln(e2[0]/e2[i])/((i as f64)*f64::ln(2.0)));
    }
}