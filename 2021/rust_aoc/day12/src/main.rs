use std::collections::{HashMap, HashSet};
use std::fs;

const INPUT_FILE: &str = "day12/src/input";

fn parse() -> HashMap<String, HashSet<String>> {
    let mut m = HashMap::new();
    for line in fs::read_to_string(INPUT_FILE).unwrap().lines() {
        let mut caves = line.split('-');
        let left = caves.next().unwrap().to_string();
        let right = caves.next().unwrap().to_string();
        m.entry(left.clone())
            .or_insert_with(HashSet::new)
            .insert(right.clone());
        m.entry(right).or_insert_with(HashSet::new).insert(left);
    }
    m
}

fn visit_one(
    starting: &str,
    m: &HashMap<String, HashSet<String>>,
    visited: &mut HashSet<String>,
) -> u32 {
    if starting == "end" {
        return 1;
    }

    let mut sum = 0;
    for neigh in m.get(starting).unwrap() {
        if !visited.contains(neigh) {
            if neigh.as_bytes()[0].is_ascii_lowercase() {
                visited.insert(neigh.clone());
            }
            sum += visit_one(neigh, m, visited);
            visited.remove(neigh);
        }
    }

    sum
}

fn part_one(m: &HashMap<String, HashSet<String>>) -> u32 {
    let mut visited_small = HashSet::new();
    visited_small.insert("start".to_string());
    visit_one("start", m, &mut visited_small)
}

fn visit_two(
    starting: &str,
    m: &HashMap<String, HashSet<String>>,
    visited: &mut HashSet<String>,
    was_visited_twice: bool,
) -> u32 {
    if starting == "end" {
        return 1;
    }

    let mut sum = 0;
    for neigh in m.get(starting).unwrap() {
        if neigh.as_str() != "start" && !(was_visited_twice && visited.contains(neigh)) {
            let mut twice_next = was_visited_twice;
            let mut this_twice = false;

            if neigh.as_bytes()[0].is_ascii_lowercase() && !visited.insert(neigh.clone()) {
                twice_next = true;
                this_twice = true;
            }

            sum += visit_two(neigh, m, visited, twice_next);

            if !this_twice {
                visited.remove(neigh);
            }
        }
    }

    sum
}

fn part_two(m: &HashMap<String, HashSet<String>>) -> u32 {
    let mut visited_once = HashSet::new();
    visited_once.insert("start".to_string());
    visit_two("start", m, &mut visited_once, false)
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
