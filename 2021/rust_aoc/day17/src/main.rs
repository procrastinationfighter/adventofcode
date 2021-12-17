use std::collections::HashSet;
use std::fs;

const INPUT_FILE: &str = "day17/src/input";
type TargetRange = (i32, i32);

fn parse() -> (TargetRange, TargetRange) {
    let input = fs::read_to_string(INPUT_FILE).unwrap();
    let coords = input
        .lines()
        .next()
        .unwrap()
        .split_once(": ")
        .unwrap()
        .1
        .split_once(", ")
        .unwrap();

    let x = coords
        .0
        .split_once('=')
        .unwrap()
        .1
        .split_once("..")
        .unwrap();
    let y = coords
        .1
        .split_once('=')
        .unwrap()
        .1
        .split_once("..")
        .unwrap();

    (
        (x.0.parse().unwrap(), x.1.parse().unwrap()),
        (y.0.parse().unwrap(), y.1.parse().unwrap()),
    )
}

fn in_range(arg: i32, range: &TargetRange) -> bool {
    arg >= range.0 && arg <= range.1
}

fn part_one((x_range, y_range): &(TargetRange, TargetRange)) -> i32 {
    // My input had x >= 0, so I just assume that its a rule.
    // Yes. This is a heuristic.
    let mut curr_max = 0;
    for x in 1..=x_range.1 {
        let min_y = y_range.0 - 1;
        let max_y = -10 * y_range.0;
        for y in min_y..max_y {
            let mut i = 0;
            let mut curr_x = 0;
            let mut curr_y = 0;
            loop {
                curr_x += i32::max(x - i, 0);
                curr_y += y - i;
                if y > 0 && in_range(curr_x, x_range) && in_range(curr_y, y_range) {
                    curr_max = i32::max(curr_max, y * (y + 1) / 2);
                    break;
                } else if curr_x > x_range.1 || curr_y < y_range.0 {
                    break;
                }
                i += 1;
            }
        }
    }

    curr_max
}

fn part_two((x_range, y_range): &(TargetRange, TargetRange)) -> usize {
    let mut velocities: HashSet<(i32, i32)> = HashSet::new();

    for x in 1..=x_range.1 {
        let min_y = y_range.0 - 1;
        let max_y = -10 * y_range.0;
        for y in min_y..max_y {
            let mut i = 0;
            let mut curr_x = 0;
            let mut curr_y = 0;
            loop {
                curr_x += i32::max(x - i, 0);
                curr_y += y - i;
                if in_range(curr_x, x_range) && in_range(curr_y, y_range) {
                    velocities.insert((x, y));
                    break;
                } else if curr_x > x_range.1 || curr_y < y_range.0 {
                    break;
                }
                i += 1;
            }
        }
    }

    velocities.len()
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
