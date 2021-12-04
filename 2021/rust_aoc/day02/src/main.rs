use std::fs;

const INPUT_FILE: &str = "day02/src/input";

fn parse() -> Vec<(String, u32)> {
    let x = fs::read_to_string(INPUT_FILE).expect("file not read");
    x.lines()
        .map(|s| {
            let x: Vec<&str> = s.split_whitespace().collect();
            (x[0].to_string(), x[1].parse().expect("parse error"))})
        .collect()
}

fn part_one(v: &[(String, u32)]) -> u64 {
    let mut h: i64 = 0;
    let mut s = 0;
    for (dir, val) in v {
        match dir.as_str() {
            "forward" => s += *val,
            "up" => h -= *val as i64,
            "down" => h += *val as i64,
            _ => panic!("unknown direction")
        };
    }

    (h * (s as i64)) as u64
}

fn part_two(v: &[(String, u32)]) -> u64 {
    let mut aim: i64 = 0;
    let mut h: i64 = 0;
    let mut s = 0;
    for (dir, val) in v {
        match dir.as_str() {
            "forward" => {
                s += *val;
                h += (*val as i64) * aim
            },
            "up" => aim -= *val as i64,
            "down" => aim += *val as i64,
            _ => panic!("unknown direction")
        };
    }

    (h * (s as i64)) as u64
}

fn main() {
    let v = parse();
    println!("Part 1: {}, part 2: {}", part_one(&v), part_two(&v));
}
