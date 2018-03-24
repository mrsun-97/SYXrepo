pub mod basic {

    //take the place of f64::fabs()
    pub fn fabs(x: f64) -> f64 {
        if x >= 0.0 {x}
        else {-x}
    }

    /*
    fn Cauchy_fx(x: f64) -> f64 {
        1.0/(x*x+1.0)
    }
    */

    pub fn generate<T: Fn(f64)->f64, U: Fn(f64)->f64>(f1: T, n: usize, fx: U) -> (Vec<f64>, Vec<f64>) {
        let mut vec_x: Vec<f64> = Vec::with_capacity(n+1);
        let mut vec_y: Vec<f64> = Vec::with_capacity(n+1);
        for i in 0..(n+1) {
            vec_x.push(f1(i as f64));
            vec_y.push(fx(f1(i as f64)));
        }
        //println!("{:#?}",vec_y);
        (vec_x,vec_y)
    }
}

pub mod sort {

    //lagrange interpolation function
    pub fn lagrange(axes_x: &[f64], axes_y: &[f64], x: f64) -> f64 {
        if axes_x.len() != axes_y.len() {
            panic!("Input error!");
        }
        let n = axes_x.len();
        //let mut i = 0;
        //let mut j = 0;
        let mut sum = 0.00;
        let mut tmp = 1.00;
        for j in 0..n {
            for i in 0..j {
                tmp *= (x-axes_x[i])/(axes_x[j]-axes_x[i]);
            }
            for i in (j+1)..n {
                tmp *= (x-axes_x[i])/(axes_x[j]-axes_x[i]);
            }
            sum += tmp * axes_y[j];
            tmp = 1.00;         //Don't forget this!
        }
        sum
    }

    pub fn newton(axes_x: &[f64], axes_y: &[f64]) -> (Vec<f64>, Vec<f64>) {
        if axes_x.len() != axes_y.len() {
            panic!("Input error!");
        }
        let n = axes_x.len();
        let mut data: Vec<f64> = Vec::with_capacity(n);
        let mut x: Vec<f64> = Vec::with_capacity(n);
        for k in 0..n {
            data.push(axes_y[k]);
            x.push(axes_x[k]);
        }
        for j in 0..n {
            let mut i = n-1;
            while i > j {
                data[i] = (data[i]-data[i-1])/(axes_x[i]-axes_x[i-1-j]);
                i -= 1;
            }
        }
        (data, x)
    }

    pub fn calculate(data: &[f64], x0: &[f64], x: &[f64]) -> Vec<f64> {
        let n = x0.len();
        let m = data.len();
        let mut y: Vec<f64> = Vec::with_capacity(n);
        for i in 0..n {
            let mut sum = data[m-1];
            let mut j = m-2;
            loop {
                sum = sum * (x[i] - x0[j]) + data[j];
                if j == 0 {break}
                j -= 1;
            }
            y.push(sum);
        }
        y
    }

}


#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(1+1, 2);
    }
}
