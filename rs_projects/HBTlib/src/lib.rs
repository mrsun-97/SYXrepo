#[no_mangle]

use std::cmp::Ordering;

pub extern fn concu(p_stam:Vec<f64>, p_chan:Vec<f64>, num: usize, step: f64) -> i32 {
    let len = p_stam.len();
    if len <= num {
        return -1;
    }
    let count: i32 = 0;
    let mut arr: Vec<(f64,f64)> = Vec::with_capacity(num);
    for i in 0..num {
        arr.push((p_stam[i], p_chan[i]));
    }
    arr.sort_by(
        |a1, a2| a1.partial_cmp(a2).unwrap_or(Ordering::Greater)
    );

    //未完待续
    count
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
