use std::collections::VecDeque;
use std::fs;

const INPUT_FILE: &str = "day10/src/input";

fn parse() -> Vec<String> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .lines()
        .map(|x| x.to_string())
        .collect()
}

fn part_one(v: &[String]) -> (u32, Vec<&String>) {
    let mut sum = 0;
    let mut good_lines: Vec<&String> = vec![];

    for line in v {
        let last_sum = sum;
        let mut stack = VecDeque::new();

        for byte in line.bytes() {
            match byte {
                b'(' => stack.push_back(byte),
                b'[' => stack.push_back(byte),
                b'{' => stack.push_back(byte),
                b'<' => stack.push_back(byte),
                b')' => {
                    if stack.pop_back().unwrap_or(0) != b'(' {
                        sum += 3;
                        break;
                    }
                }
                b']' => {
                    if stack.pop_back().unwrap_or(0) != b'[' {
                        sum += 57;
                        break;
                    }
                }
                b'}' => {
                    if stack.pop_back().unwrap_or(0) != b'{' {
                        sum += 1197;
                        break;
                    }
                }
                b'>' => {
                    if stack.pop_back().unwrap_or(0) != b'<' {
                        sum += 25137;
                        break;
                    }
                }
                _ => panic!("Bad byte found!"),
            }
        }

        if last_sum == sum {
            good_lines.push(line);
        }
    }

    (sum, good_lines)
}

fn part_two(v: &[&String]) -> u64 {
    let mut points: Vec<u64> = vec![];
    for line in v {
        let mut stack = VecDeque::new();
        for byte in line.bytes() {
            match byte {
                b'(' => stack.push_back(byte),
                b'[' => stack.push_back(byte),
                b'{' => stack.push_back(byte),
                b'<' => stack.push_back(byte),
                _ => {
                    stack.pop_back();
                }
            };
        }

        let mut curr_points: u64 = 0;
        while !stack.is_empty() {
            curr_points *= 5;
            match stack.pop_back().unwrap() {
                b'(' => curr_points += 1,
                b'[' => curr_points += 2,
                b'{' => curr_points += 3,
                b'<' => curr_points += 4,
                _ => panic!("Wrong byte!"),
            }
        }

        points.push(curr_points);
    }

    points.sort_unstable();
    points[points.len() / 2]
}

fn main() {
    let v = parse();
    let (one, good) = part_one(&v);
    println!("Part one: {}, part two: {}", one, part_two(&good));
}
