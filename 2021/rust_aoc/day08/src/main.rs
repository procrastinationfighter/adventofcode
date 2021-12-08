use std::collections::HashSet;
use std::fs;

const INPUT_FILE: &str = "day08/src/input";

fn parse() -> Vec<(Vec<String>, Vec<String>)> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .lines()
        .map(|line| {
            let mut x = line.split(" | ");
            let left = x
                .next()
                .unwrap()
                .split(' ')
                .map(|str| str.to_string())
                .collect::<Vec<String>>();
            let right = x
                .next()
                .unwrap()
                .split(' ')
                .map(|str| str.to_string())
                .collect::<Vec<String>>();
            (left, right)
        })
        .collect()
}

fn part_one(v: &[(Vec<String>, Vec<String>)]) -> u32 {
    let unique: Vec<usize> = vec![2, 3, 4, 7];
    let mut sum = 0;
    for (_, right) in v {
        for str in right {
            if unique.contains(&str.len()) {
                sum += 1;
            }
        }
    }

    sum
}

fn calc_output(left: &[String], right: &[String]) -> u32 {
    // We get numbers in the following order:
    // 1, 7, 4, 8 (const number of digits),
    // 3 (5 elements with chars of 7),
    // 2 (5 elements, only 2 common with '4')
    // 5 (5 elements, the remaining one)
    // 9 (6 elements with digits of 4),
    // 6 (6 elements without one char of 1),
    // 0 (6 elements, the remaining one),
    let mut digits: Vec<HashSet<char>> = vec![HashSet::new(); 10];
    let mut six_dig: Vec<usize> = vec![];
    let mut five_dig: Vec<usize> = vec![];

    // First loop, match strings with num of digits.
    for (i, str) in left.iter().enumerate() {
        match str.len() {
            2 => digits[1] = str.chars().collect(),
            3 => digits[7] = str.chars().collect(),
            4 => digits[4] = str.chars().collect(),
            5 => five_dig.push(i),
            6 => six_dig.push(i),
            7 => digits[8] = str.chars().collect(),
            _ => println!("Wrong len of string!"),
        }
    }

    // Find 2, 3, 5.
    for num in five_dig {
        let digs: HashSet<char> = left[num].chars().collect();
        if digs.is_superset(&digits[7]) {
            digits[3] = digs;
        } else if digs.intersection(&digits[4]).count() == 2 {
            digits[2] = digs;
        } else {
            digits[5] = digs;
        }
    }

    // Find 9, 6, 0
    for num in six_dig {
        let digs: HashSet<char> = left[num].chars().collect();
        if digs.is_superset(&digits[4]) {
            digits[9] = digs;
        } else if digs.intersection(&digits[1]).count() == 1 {
            digits[6] = digs;
        } else {
            digits[0] = digs;
        }
    }

    let mut sum: u32 = 0;

    for str in right {
        let digs: HashSet<char> = str.chars().collect();
        sum *= 10;

        for (i, digit) in digits.iter().enumerate() {
            if digs.eq(digit) {
                sum += i as u32;
                break;
            }
        }
    }

    sum
}

fn part_two(v: &[(Vec<String>, Vec<String>)]) -> u32 {
    let mut sum = 0;

    for (left, right) in v {
        sum += calc_output(left, right);
    }

    sum
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
