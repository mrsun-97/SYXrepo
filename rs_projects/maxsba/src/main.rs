fn main() {

}

fn find_max_subarray<'s, T>(arr: &'s [T], a: usize, b: usize) -> &'s [T] {
    &arr[a..b]
}