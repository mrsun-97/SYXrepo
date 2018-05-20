pub mod solve{

    const DELTA: f64 = 1e-6;

    pub fn sor(A: &Vec<Vec<f64>>, b: &Vec<f64>, w: f64, def_n: i32) -> (Vec<f64>, i32) {
        //check
        let n = A.len();
        if n != b.len() {panic!("Invalid input!")};
        for i in 0..n {
            if n != A[i].len() {panic!("Invalid input!")};
        }
        let mut a = A.clone();
        let mut g = b.clone();
        {   //calculate a and g that: X`(k+1) = aX`(now) + g;
            for i in 0..n {
                let tr = a[i][i];
                g[i] /= tr;
                if tr == 0.0 {
                    panic!("A[{0}][{0}] = 0, exit.", i+1);
                }
                for j in 0..n {
                    a[i][j] = -a[i][j] / tr;
                }
                a[i][i] = 0.0;
            }
        }
        let mut x: Vec<f64> = Vec::with_capacity(n);
        for _i in 0..n {x.push(0.0)};
        let count = 
        {   //iterating!
            let mut count: i32 = 0;
            let v = 1.0 - w;
            loop {
                count -= 1;
                let y = x.clone();
                for j in 0..n {
                    x[j] = v * x[j] + w * (g[j] + (&x).iter().zip(&a[j])
                    .map(|(p, q)| p*q).fold(0.0, |sum, t| sum + t));
                }
                if x.iter().zip(y).map(|(p, q)| f64::abs(p-q))
                .fold(0.0, |sum, t| max(sum, t)) < DELTA
                {   
                    count = -count;
                    break;
                }
                if count == -def_n {break;}
            }
            count
        };
        (x, count)
    }

    pub fn gs(A: &Vec<Vec<f64>>, b: &Vec<f64>, def_n: i32) -> (Vec<f64>, i32) {
        sor(A, b, 1.0, def_n)
    }

    fn max(a: f64, b: f64) -> f64 {
        if a >= b {a}
        else {b}
    }

}



#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
