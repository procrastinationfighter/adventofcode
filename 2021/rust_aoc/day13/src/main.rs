use std::collections::HashSet;
use std::fs;

const INPUT_FILE: &str = "day13/src/input";

type Point = (u32, u32);
type Fold = (bool, u32);

fn parse() -> (Vec<Point>, Vec<Fold>) {
    let input = fs::read_to_string(INPUT_FILE).unwrap();

    let mut parts = input.split("\n\n");

    let points: Vec<(u32, u32)> = parts
        .next()
        .unwrap()
        .lines()
        .map(|line| {
            let mut p = line.split(',');
            (
                p.next().unwrap().parse().unwrap(),
                p.next().unwrap().parse().unwrap(),
            )
        })
        .collect();

    let folds: Vec<(bool, u32)> = parts
        .next()
        .unwrap()
        .lines()
        .map(|line| {
            let mut p = line.strip_prefix("fold along ").unwrap().split('=');
            let ch = p.next().unwrap();
            (ch == "x", p.next().unwrap().parse().unwrap())
        })
        .collect();

    (points, folds)
}

fn fold(points: HashSet<Point>, fold: &Fold) -> HashSet<Point> {
    let mut after_fold: HashSet<(u32, u32)> = HashSet::new();

    for point in points {
        if fold.0 && point.0 > fold.1 {
            after_fold.insert((2 * fold.1 - point.0, point.1));
        } else if !fold.0 && point.1 > fold.1 {
            after_fold.insert((point.0, 2 * fold.1 - point.1));
        } else {
            after_fold.insert(point);
        }
    }

    after_fold
}

fn part_one(points: &[Point], f: &Fold) -> u32 {
    let curr_points: HashSet<(u32, u32)> = points.to_vec().into_iter().collect();
    let after_fold = fold(curr_points, f);

    after_fold.len() as u32
}

fn part_two(points: &[Point], folds: &[Fold]) {
    let mut curr_points: HashSet<(u32, u32)> = points.to_vec().into_iter().collect();

    for f in folds {
        curr_points = fold(curr_points, f);
    }

    let mut max_x = 0;
    let mut max_y = 0;

    for point in &curr_points {
        if point.0 > max_x {
            max_x = point.0;
        } else if point.1 > max_y {
            max_y = point.1;
        }
    }

    for y in 0..=max_y {
        for x in 0..=max_x {
            let ch = if curr_points.contains(&(x, y)) {
                '#'
            } else {
                '.'
            };
            print!("{}{}", ch, ch);
        }
        println!();
    }
}

fn main() {
    let (points, folds) = parse();

    println!("Part one: {}, part two: ", part_one(&points, &folds[0]));
    part_two(&points, &folds);
}
