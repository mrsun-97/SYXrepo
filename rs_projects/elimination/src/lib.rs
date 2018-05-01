
pub mod partialpivoting{

    pub fn solve(A: &Vec<Vec<f64>>, B: &Vec<f64>) -> Vec<f64> {
        let n = B.len();
        if n != A.len() {
            panic!("Input error!");
        }
        let mut a = A.clone();
        let mut b = B.clone();
        for i in 0..b.len() {
            let mut k = i;
            for j in (i+1)..n {
                if abs(a[k][i]) < abs(a[k][j]) {k = j};
            }
            for j in i..n {
                let t = a[i][j];
                a[i][j] = a[k][j];
                a[k][j] = t;
            }
            {
                let t = b[i];
                b[i] = b[k];
                b[k] = t;
            }
            for j in (i+1)..n {
                a[j][i] /= a[i][i];
                for k in (i+1)..n {
                    a[j][k] -= a[j][i] * a[i][k];
                }
                b[j] -= a[j][i] * b[i];
            }
        }
        for i in (0..n).map(|x| n-x-1) {
            for j in (i+1)..n {
                b[i] -= a[i][j]*b[j];
            }
            b[i] /= a[i][i];
        }
        b
    }

    fn abs(x:f64) -> f64 {
        if x < 0.0 {-x}
        else {x}
    }

}



#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
