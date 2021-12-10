use std::fs;

const INPUT_FILE: &str = "day12/src/input";

fn parse() -> Vec<i32> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .map(|x| x.parse().unwrap())
        .collect()
}

fn part_one(v: &[i32]) -> i32 {
    v[0]
}

fn part_two(v: &[i32]) -> i32 {
    v[0]
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
