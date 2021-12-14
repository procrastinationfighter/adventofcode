use std::collections::HashMap;
use std::fs;

const INPUT_FILE: &str = "day14/src/input";

fn parse() -> (Vec<char>, HashMap<(char, char), char>) {
    let input = fs::read_to_string(INPUT_FILE).unwrap();
    let mut lines = input.lines();
    let starting: Vec<char> = lines.next().unwrap().chars().collect();
    lines.next();

    let map: HashMap<(char, char), char> = lines
        .map(|line| {
            let mut x = line.split(" -> ");
            let mut left_iter = x.next().unwrap().chars();
            let right = x.next().unwrap().chars().next().unwrap();

            (
                (left_iter.next().unwrap(), left_iter.next().unwrap()),
                right,
            )
        })
        .collect();

    (starting, map)
}

fn find_diff(map: HashMap<char, u64>) -> u64 {
    let mut max: u64 = 0;
    let mut min = u64::MAX;

    for (_, times) in map {
        if times > max {
            max = times;
        }

        if times < min {
            min = times;
        }
    }

    max - min
}

fn part_one(starting: &[char], map: &HashMap<(char, char), char>) -> u64 {
    let mut prev = starting.to_vec();
    let mut appearences: HashMap<char, u64> = HashMap::new();

    for ch in starting {
        *appearences.entry(*ch).or_insert(0) += 1;
    }

    for _ in 0..10 {
        let mut new_vec: Vec<char> = Vec::with_capacity(2 * prev.len());
        new_vec.push(prev[0]);

        for i in 0..(prev.len() - 1) {
            let new_insert = map.get(&(prev[i], prev[i + 1])).unwrap();
            new_vec.push(*new_insert);
            new_vec.push(prev[i + 1]);
            *appearences.entry(*new_insert).or_insert(0) += 1;
        }

        prev = new_vec
    }

    find_diff(appearences)
}

fn part_two(starting: &[char], map: &HashMap<(char, char), char>) -> u64 {
    let mut appearences: HashMap<char, u64> = HashMap::new();
    for ch in starting {
        *appearences.entry(*ch).or_insert(0) += 1;
    }

    let mut counts: HashMap<(char, char), u64> = map.iter().map(|(seq, _)| (*seq, 0)).collect();

    for i in 0..(starting.len() - 1) {
        *counts.get_mut(&(starting[i], starting[i + 1])).unwrap() += 1;
    }

    for _ in 0..40 {
        let mut new_counts = HashMap::new();
        for (key, value) in counts {
            let new_insert = map.get(&key).unwrap();

            *new_counts.entry((key.0, *new_insert)).or_insert(0) += value;
            *new_counts.entry((*new_insert, key.1)).or_insert(0) += value;
            *appearences.entry(*new_insert).or_insert(0) += value;
        }
        counts = new_counts;
    }

    find_diff(appearences)
}

fn main() {
    let v = parse();

    println!(
        "Part one: {}, part two: {}",
        part_one(&v.0, &v.1),
        part_two(&v.0, &v.1)
    );
}
