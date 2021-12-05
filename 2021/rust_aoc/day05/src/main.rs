use std::collections::HashSet;
use gcd::Gcd;

const INPUT_FILE: &str = "day05/src/input";

type Point = (i32, i32);

fn parse() -> Vec<(Point, Point)> {
    std::fs::read_to_string(INPUT_FILE).unwrap().lines()
        .map(|line| {
            let points: Vec<(i32, i32)> = line.split(" -> ")
                .map(|point| {
                    let nums: Vec<i32> = point.split(',')
                        .map(|num| num.parse().unwrap())
                        .collect();
                    (nums[0], nums[1])
                })
                .collect();
            (points[0], points[1])
        }
        )
        .collect()
}

fn add_points(all: &mut HashSet<Point>, intersections: &mut HashSet<Point>, line: &(Point, Point)) {
    let delta = (line.0.0 - line.1.0, line.0.1 - line.1.1);
    let gcd = (i32::abs(delta.1) as u32).gcd(i32::abs(delta.0) as u32) as i32;
    let delta = (delta.0 / gcd, delta.1 / gcd);

    let mut curr = line.1;
    while !(curr.0 == line.0.0 + delta.0 && curr.1 == line.0.1 + delta.1) {
        if all.contains(&curr) {
            intersections.insert(curr);
        } else {
            all.insert(curr);
        }
        curr.0 += delta.0;
        curr.1 += delta.1;
    }
}

fn part_one(v: &[(Point, Point)]) -> u32 {
    let mut all: HashSet<Point> = HashSet::new();
    all.reserve(v.len());
    let mut intersections: HashSet<Point> = HashSet::new();

    for line in v {
        if line.0.0 == line.1.0 || line.0.1 == line.1.1 {
            add_points(&mut all, &mut intersections, line);
        }
    }

    intersections.len() as u32
}

fn part_two(v: &[(Point, Point)]) -> u32 {
    let mut all: HashSet<Point> = HashSet::new();
    all.reserve(v.len());
    let mut intersections: HashSet<Point> = HashSet::new();

    for line in v {
        add_points(&mut all, &mut intersections, line)
    }

    intersections.len() as u32
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
