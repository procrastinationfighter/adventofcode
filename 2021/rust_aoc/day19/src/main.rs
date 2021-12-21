use std::fs;

const INPUT_FILE: &str = "day19/src/input";

type Point = (i32, i32, i32);

struct Scanner {
    beacons: Vec<Point>,
    // Relative to 0's position
    location: Point,
    x: bool,
    y: bool,
    z: bool,
}

fn parse() -> Vec<Vec<Point>> {
    let input = fs::read_to_string(INPUT_FILE).unwrap();
    input
        .split("\n\n")
        .map(|scanner| {
            let mut line_iter = scanner.lines();
            line_iter.next();
            line_iter
                .map(|line| {
                    let (x, yz) = line.split_once(",").unwrap();
                    let (y, z) = yz.split_once(",").unwrap();
                    (
                        x.parse().unwrap(),
                        y.parse().unwrap(),
                        z.parse().expect(&*format!("{}", z)),
                    )
                })
                .collect()
        })
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
    for (i, scanner) in v.iter().enumerate() {
        println!("Scanner {}", i);
        for p in scanner {
            println!("{} {} {}", p.0, p.1, p.2);
        }
    }
    // println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
