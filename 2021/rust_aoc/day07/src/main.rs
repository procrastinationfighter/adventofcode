use std::fs;

const INPUT_FILE: &str = "day07/src/input";

fn parse() -> Vec<u32> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .split_whitespace()
        .collect::<String>()
        .split(',')
        .map(|num| num.parse().unwrap())
        .collect()
}

fn part_one(v: &[u32]) -> u32 {
    // Simple O(n^2) solution.
    let min = *v.iter().min().unwrap();
    let max = *v.iter().max().unwrap();

    let mut min_fuel = u32::MAX;

    for i in min..=max {
        let mut curr_fuel = 0;
        for crab in v {
            curr_fuel += i32::abs(*crab as i32 - i as i32) as u32;
        }
        if curr_fuel < min_fuel {
            min_fuel = curr_fuel;
        }
    }

    min_fuel
}

fn part_two(v: &[u32]) -> u32 {
    // Almost the same as part 1.
    let min = *v.iter().min().unwrap();
    let max = *v.iter().max().unwrap();

    let mut min_fuel = u32::MAX;

    for i in min..=max {
        let mut curr_fuel = 0;
        for crab in v {
            let diff = i32::abs(*crab as i32 - i as i32) as u32;
            curr_fuel += ((diff) * (diff + 1)) / 2
        }
        if curr_fuel < min_fuel {
            min_fuel = curr_fuel;
        }
    }

    min_fuel
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
