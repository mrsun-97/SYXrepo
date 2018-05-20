extern crate iter_solve;
use iter_solve::solve::sor;
use iter_solve::solve::gs;

fn main(){
    let A: Vec<Vec<f64>> = vec![
        vec![31.0,  -13.0,  0.0,    0.0,    0.0,    -10.0,  0.0,    0.0,    0.0],

        vec![-13.0, 35.0,   -9.0,   0.0,    -11.0,  0.0,    0.0,    0.0,    0.0],

        vec![0.0,   -9.0,   31.0,   -10.0,  0.0,    0.0,    0.0,    0.0,    0.0],

        vec![0.0,   0.0,    -10.0,    79.0, -30.0,  0.0,    0.0,    0.0,    -9.0],

        vec![0.0,   0.0,    0.0,    -30.0,  57.0,   -7.0,   0.0,    -5.0,   0.0],

        vec![0.0,   0.0,    0.0,    0.0,    -7.0,   47.0,   -30.0,  0.0,    0.0],

        vec![0.0,   0.0,    0.0,    0.0,    0.0,    -30.0,  41.0,   0.0,    0.0],

        vec![0.0,   0.0,    0.0,    0.0,    -5.0,   0.0,    0.0,    27.0,   -2.0],

        vec![0.0,   0.0,    0.0,    -9.0,   0.0,    0.0,    0.0,    -2.0,   29.0]
    ];
    let B: Vec<f64> = vec![-15.0, 27.0, -23.0, 0.0, -20.0, 12.0, -7.0, 7.0, 10.0];
    
    {//Gauss-seidel
        
        let (x, count) = gs(&A, &B, 20);
        println!("根为：");
        for i in x.iter() {
            println!("{:>20.14e}", i);
        }
        print!("Gauss-seidel迭代总迭代步数为：{}", i32::abs(count));
        if count < 0 {
            println!("(已达上限)\n");
        }
        else {
            println!("\n");
        }
        
    }
    {//SOR
        println!("SOR迭代步数为: ");
        let mut best_w = 0.0;
        let mut counts = 50 + 1;
        for i in 1..100 {
            let w = (i as f64)/50.0;
            let (_, count) = sor(&A, &B, w, 99);
            let abs_count = i32::abs(count);
            print!("松弛因子：{:.2} , {}", w, abs_count);
            if count < 0 {
                println!("(截止)");
            }
            else {
                println!("");
            }
            if abs_count < counts {
                counts = abs_count;
                best_w = w;
            }
        }
        println!("最佳松弛因子为：{:.2}", best_w);
    }
    /*
    for w in [0.02, 0.06, 0.10, 0.14, 0.18, 0.22].iter() {    //test
        let (_, count) = sor(&A, &B, *w, 1000000);
        print!("松弛因子：{:.2} , {}", w, i32::abs(count));
        if count < 0 {
            println!("(截止)");
        }
        else {
            println!("");
        }
    }
    */
}
