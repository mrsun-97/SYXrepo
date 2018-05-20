
pub mod iteration{
    
    const DELTA: f64 = 1e-6;       //容许误差
    
    
    pub fn newton<T: Fn(f64)->f64, U: Fn(f64)->f64>(f:T, df:U, x0:f64) -> (f64, usize) {
        let mut x2 = x0;
        let mut x1 = 0.0;
        let mut i: usize = 0;
        loop{
            x1 = x2;
            x2 = x2 - f(x2)/df(x2);
            i += 1;
            if fabs(x2-x1) < DELTA {break}
            else if i == 0 {panic!("Counter overflowed.")};
        }
        (x2, i)     //返回根与迭代计数
    }


    pub fn secant<T: Fn(f64)->f64>(f:T, a:f64, b:f64) -> (f64, usize) {
        let mut x2 = b;
        let mut x1 = a;
        let mut i: usize = 0;
        loop{
            let t = x2;
            x2 = x2 - (x2-x1)/(1.0-f(x1)/f(x2));
            x1 = t;
            i += 1;
            if fabs(x2-x1) < DELTA {break}
            else if i == 0 {panic!("Counter overflowed.")};
        }
        (x2, i)
    }

    fn fabs(x: f64)-> f64 {
        if x < 0.0 {
            return -x;
        };
        x
    }
}



#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
