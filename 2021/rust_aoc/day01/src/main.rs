use std::fs;

const INPUT_FILE: &str = "day01/src/input";

fn parse() -> Vec<u32> {
    let x = fs::read_to_string(INPUT_FILE).expect("file not read");
    x.split_whitespace()
        .map(|s| s.parse().expect("parse error"))
        .collect()
}

fn first_part(nums: &[u32]) -> u32 {
    let mut last: u32 = 0;
    let mut count = 0;
    for (i, num) in nums.iter().enumerate() {
        if i != 0 {
            if *num > last {
                count += 1;
            }

            last = *num;
        }
    }

    count
}

fn second_part(nums: &[u32]) -> u32 {
    let mut count = 0;
    let mut last = 0;

    for i in 0..(nums.len() - 2) {
        let sum = nums[i] + nums[i + 1] + nums[i + 2];
        if i != 0 && sum > last {
            count += 1;
        }

        last = sum;
    }

    count
}

fn main() {
    let numbers = parse();
    println!(
        "First part: {}, second part: {}",
        first_part(&numbers),
        second_part(&numbers)
    );
}
