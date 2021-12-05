use std::fs;
const INPUT_FILE: &str = "day03/src/input";

fn parse() -> Vec<String> {
    let x = fs::read_to_string(INPUT_FILE).expect("file not read");
    x.lines().map(|x| x.to_string()).collect()
}

fn calculate_prevailing(v: &[String]) -> Vec<i32> {
    let mut prevailing: Vec<i32> = vec![];
    prevailing.resize(v[0].len(), 0);

    for num in v {
        for (i, ch) in num.chars().enumerate() {
            prevailing[i] += if ch == '1' {
                1
            } else if ch == '0' {
                -1
            } else {
                println!("Wrong char!");
                0
            };
        }
    }

    prevailing
}

fn part_one(v: &[String]) -> u32 {
    let prevailing = calculate_prevailing(v);

    let mut gamma = 0;
    let mut epsilon = 0;
    for val in prevailing.into_iter() {
        gamma *= 2;
        epsilon *= 2;

        if val >= 0 {
            gamma += 1;
        } else if val < 0 {
            epsilon += 1;
        }
    }

    gamma * epsilon as u32
}

fn get_rating(v: &[String], dominating: bool) -> u32 {
    let mut nums: Vec<&String> = v.iter().collect::<Vec<&String>>();
    for i in 0..v[0].len() {
        let wanted = {
            let mut sum = 0;
            for num in nums.iter() {
                sum += if num.as_bytes()[i] as char == '1' {
                    1
                } else {
                    -1
                };
            }
            if (sum >= 0 && dominating) || (sum < 0 && !dominating) {
                '1'
            } else {
                '0'
            }
        };

        let mut new_nums: Vec<&String> = Vec::with_capacity(nums.len());

        for num in nums {
            if num.as_bytes()[i] as char == wanted {
                new_nums.push(num);
            }
        }

        nums = new_nums;
        if nums.len() == 1 {
            break;
        }
    }
    u32::from_str_radix(nums[0], 2).expect("Not parsed")
}

fn part_two(v: &[String]) -> u32 {
    get_rating(v, false) * get_rating(v, true)
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
