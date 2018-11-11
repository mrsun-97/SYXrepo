//use std::f64;

pub mod integrate{

    pub fn t_integrate<U: Fn(f64)->f64 >(f: U, a: f64, b: f64, k: usize) -> Vec<f64> {
        if k > 50 {
            panic!("The number is not proper!\n");
        }
        if (b-a).abs() < 1e3*std::f64::EPSILON {
            panic!("The top meets the bottom!\n");
        }
        
        let mut n = 1;          //n = 1, 2, 4, ... 2^k.
        let mut h = b-a;
        let mut T: Vec<f64> = Vec::with_capacity(k+1);
        T.push((f(a)+f(b))*h/2.0);
        for i in 0..k {
            let mut sum = 0.0;
            let mut x = a;
            x += h/2.0;
            for _j in 0..n {     //n = 2^(i-1)
                sum += f(x);
                x += h;
            }
            sum *= h;           //sum = Hn(f)
            sum = (T[i] + sum)/2.0;
            T.push(sum);
            n = def_pow(2,i+1);
            h /= 2.0;
        }
        T   //return
    }

    pub fn s_integrate<U: Fn(f64)->f64 >(f: U, a: f64, b: f64, k: usize) -> Vec<f64> {
        //利用Romberg积分简化计算
        let S = t_integrate(f, a, b, k+1);
        let mut T: Vec<f64> = Vec::with_capacity(k+1);
        for i in 0..=k {
            T.push(
                (4.0*S[i+1]-S[i])/3.0
            )
        }
        T
    }

    pub fn def_pow(x: usize, i: usize) -> usize {
        let mut mult: usize = 1;
        for _j in 0..i {
            mult *= x;
        }
        mult
    }

}



#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
