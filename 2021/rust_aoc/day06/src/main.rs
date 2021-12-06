use std::fs;

const INPUT_FILE: &str = "day06/src/input";
const BREED_TIME: u32 = 7;
const DELAY: u32 = 2;

fn parse() -> Vec<u8> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .lines()
        .collect::<String>()
        .split(',')
        .map(|str| str.parse().expect(str))
        .collect()
}

fn part_one(n: u32, v: &[u8]) -> u64 {
    let mut arr: Vec<u64> = vec![];
    arr.resize(n as usize, 0);

    let mut sum: u64 = 0;
    for fish in v {
        let mut i: u32 = *fish as u32;
        while i < n {
            arr[i as usize] += 1;
            i += BREED_TIME;
        }
    }

    for i in 0..n {
        sum += arr[i as usize];
        let mut j = i + BREED_TIME + DELAY;
        while j < n {
            arr[j as usize] += arr[i as usize];
            j += BREED_TIME;
        }
    }

    sum + (v.len() as u64)
}

fn main() {
    let v = parse();
    println!(
        "Part one: {}, part two {}",
        part_one(80, &v),
        part_one(256, &v)
    );
}
