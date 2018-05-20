extern crate elimination;
use elimination::partialpivoting::solve;
use elimination::partialpivoting::tests;

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
    
    println!("根为: ");
    for (i, iter) in solve(&A, &B).iter().enumerate() {
        //println!("x{} = {:>20.14e}", i+1, iter);
        println!(" {:>20.14e}", iter);
    }
    

    let A: Vec<Vec<f64>> = vec![
        vec![0.0003, 3.0000],
        vec![1.0000, 1.0000]
    ];
    let B: Vec<f64> = vec![
        2.0001,
        1.0000
    ];

    println!("根为:(直接法) ");
    for (i, iter) in tests(&A, &B).iter().enumerate() {
        println!("x{} = {:>20.14e}", i+1, iter);
    }

}