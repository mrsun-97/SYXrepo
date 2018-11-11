use std::cmp::Ordering;

fn main(){
    let a: [i32; 10] = [2, 5, 4, 6, 7, 1, 8, 0, 9, 3];
    let b: [i32; 10] = [2, 2, 0, 1, 0, 2, 1, 0, 0, 2];
    let len_a = a.len();
    let mut arr: Vec<(i32,i32)> = Vec::with_capacity(len_a);
    for j in 0..len_a {
        arr.push((a[j],b[j]));
    }
    arr.sort_by(|a1, a2| a1.partial_cmp(a2).unwrap_or(Ordering::Greater));
    println!("{:?}", arr);
}