fn main() {
    use std::f64;
    const T: usize = 90;
    const N:usize = 300;
    const H: f64 = 0.08;
    const K: [f64;5] = [0.0, 0.082, 0.37, 0.045, 0.028];
    const C: [f64;5] = [0.0, 4.131e5, 1.8102e6, 1.280692e5, 1.1859e3];
    const A: f64 = 1.4e-4;
    const SIG: f64 = 0.15 * 5.6704e-8;
    let t: f64 = 60.0 / ((N*N) as f64);
    let h: f64 = H / (N as f64);
    let p1 = K[4]/C[4];
    let r1 = 0.15;
    let mut arr: [f64;N] = [25.0;N];
    arr[0] = 37.0;
    arr[1] = 37.0;
    arr[N-2] = 75.0;
    arr[N-1] = 75.0;
    let mut art = arr.clone();
    let g = |x:f64| {
        (
            A*(x-25.0) + SIG*(
                (x+273.15).powi(4)-((37.0+273.15) as f64).powi(4)
            )
        )/K[4]
    };
    for j in 0..N*N/2*T{
        {
            art[0] = arr[0] + 2.0/r1*t*p1*(
                (-3.0*arr[0]+4.0*arr[1]-arr[2])/(2.0*h)
                /* +(5.0*arr[0]-11.0*arr[1]+7.0*arr[2]-arr[3])/(4.0*h*h) */
                -g(arr[0])
            );
            art[1] = arr[1] + t*p1*(
                (-arr[0]+arr[2])/(2.0*h*(r1+h))
                +(3.0*arr[0]-5.0*arr[1]+arr[2]+arr[3])/(4.0*h*h)
            );
            for i in 2..(N-2) {
                let r = r1 + h*(i as f64);
                art[i] = arr[i] + t*p1*(
                    (-arr[i-1]+arr[i+1])/(2.0*h*r)
                    +(arr[i-2]-2.0*arr[i]+arr[i+2])/(4.0*h*h)
                );
            }
            art[N-2] = arr[N-2] + t*p1*(
                (-arr[N-3]+arr[N-1])/(2.0*h*(r1+H-h))
                +(arr[N-4]+arr[N-3]-5.0*arr[N-2]+3.0*arr[N-1])/(4.0*h*h)
            );
        }

        {   
            arr[0] = art[0] + 2.0/r1*t*p1*(
                (-3.0*art[0]+4.0*art[1]-art[2])/(2.0*h)
                /* +(5.0*art[0]-11.0*art[1]+7.0*art[2]-art[3])/(4.0*h*h) */
                -g(art[0])
            );
            arr[1] = art[1] + t*p1*(
                (-art[0]+art[2])/(2.0*h*(r1+h))
                +(3.0*art[0]-5.0*art[1]+art[2]+art[3])/(4.0*h*h)
            );
            for i in 2..(N-2) {
                let r = r1 + h*(i as f64);
                arr[i] = art[i] + t*p1*(
                    (-art[i-1]+art[i+1])/(2.0*h*r)
                    +(art[i-2]-2.0*art[i]+art[i+2])/(4.0*h*h)
                );
            }
            arr[N-2] = art[N-2] + t*p1*(
                (-art[N-3]+art[N-1])/(2.0*h*(r1+H-h))
                +(art[N-4]+art[N-3]-5.0*art[N-2]+3.0*art[N-1])/(4.0*h*h)
            );

        }
        if j%4500 == 0 {
            if j%(N*N/2) == 0 {
                println!("{}", j/(N*N/2));
            }
            for k in 0..20 {
                print!("{:<.2}  ", arr[k*N/20]);
            }
            println!("{:<.2}", arr[N-2]);
        }
    }
}
