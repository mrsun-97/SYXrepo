//use std::f64;

pub mod solve{

    pub static DELTA: f64 = 1e-6;

    pub fn rk4<T: Fn(f64,f64)->f64>(f: &T, a: f64, y0: f64, b: f64, h: f64) -> Vec<f64> {
        let n = ((b-a)/h).abs().floor() as usize;   
        let h = {       //考虑计算上下限对h正负的影响
            if b > a {h.abs()}
            else if b < a {-h.abs()}
            else {return vec!(y0);}
        };
        let mut y: Vec<f64> = Vec::with_capacity(n+1);
        let mut k: [f64;5] = [0.0;5];
        y.push(y0);
        let mut xn: f64 = a;
        let mut _solve = |xn, yn, h| {
            
            k[1] = f(xn,yn);
            k[2] = f(xn+0.5*h, yn+0.5*h*k[1]);
            k[3] = f(xn+0.5*h, yn+0.5*h*k[2]);
            k[4] = f(xn+h, yn+h*k[3]);
            yn+h/6.0*(1.0*k[1]+2.0*k[2]+2.0*k[3]+1.0*k[4])
            /*这个方法有毒 Orz
            k[1] = f(xn,yn);
            k[2] = f(xn+h/3.0, yn+h*k[1]/3.0);
            k[3] = f(xn+2.0/3.0*h, yn+h*k[1]/3.0+h*k[2]);
            k[4] = f(xn+h, yn+h*k[1]-h*k[2]+h*k[3]);
            yn+h/8.0*(1.0*k[1]+3.0*k[2]+3.0*k[3]+1.0*k[4])
            */
        };
        for i in 1..=n {
            xn = a + h*(i as f64);
            let yn = y[i-1];
            y.push(_solve(xn-h,yn,h));
        }
        if (xn-b).abs() >= DELTA {      //收尾
            let h = b-xn;
            let yn = y[n];
            y.push(_solve(xn,yn,h));
        }
        y       //返回整个数组
    }

    pub fn adams<T: Fn(f64,f64)->f64>(f: &T, a: f64, y0: f64, b: f64, h: f64) -> Vec<f64> {
        let n = ((b-a)/h).abs().floor() as usize;
        if n < 3 {
            return rk4(f, a, y0, b, h);
        }
        let h = {
            if b > a {h.abs()}
            else if b < a {-h.abs()}
            else {return vec!(y0);}
        };

        //起步计算
        let mut y = rk4(f, a, y0, a+2.0*h, h);
        if y.len() != 3 {panic!("error")};
        y.reserve(n-2);
        //println!("{}", y.len());
        let mut ff: Vec<f64> = Vec::with_capacity(n-1);
        for (i, yi) in y.iter().enumerate().take(2) {
            ff.push(f(a+h*(i as f64), *yi));
        }
        let mut xn: f64 = 0.0;

        for i in 3..=n {
            xn = a + h*(i as f64);
            let fu = f(xn-h,y[i-1]);
            ff.push(fu);
            //ybar为预估
            let mut ybar = y[i-1] + h/12.0*(23.0*ff[i-1] - 16.0*ff[i-2] + 5.0*ff[i-3]);
            //校正
            ybar = y[i-1] + h/12.0*(5.0*f(xn,ybar) +8.0*ff[i-1] - 1.0*ff[i-2]);
            y.push(ybar);
        };
        if (xn-b).abs() >= DELTA {      //收尾
            let yn = y[n];
            let end = rk4(f, xn, yn, b, h);
            if end.len() == 2 {
                y.push(end[1]);
            }
            else {panic!("Error occurs in the end !");}
        }
        y
    }

}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(1.0+2.0, 3.0);
    }
}
