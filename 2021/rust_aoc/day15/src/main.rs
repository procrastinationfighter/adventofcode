use std::collections::{BinaryHeap, HashMap};
use std::fs;

const INPUT_FILE: &str = "day15/src/input";
const DELTA: [(i8, i8); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

fn parse() -> Vec<Vec<i32>> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .lines()
        .map(|x| x.as_bytes().iter().map(|y| (*y - b'0') as i32).collect())
        .collect()
}

fn in_bounds(x: i32, y: i32, len: usize) -> bool {
    x >= 0 && x < len as i32 && y >= 0 && y < len as i32
}

fn part_one(v: &[Vec<i32>]) -> i32 {
    let mut distances: HashMap<(i32, i32), i32> = HashMap::new();
    let mut q: BinaryHeap<(i32, i32, i32)> = BinaryHeap::new();
    let mut finish = false;
    q.push((-v[0][1], 1, 0));
    q.push((-v[1][0], 0, 1));

    while !q.is_empty() && !finish {
        let (dist, x, y) = q.pop().unwrap();
        if x + 1 == v.len() as i32 && y + 1 == v.len() as i32 {
            finish = true;
        }
        for d in &DELTA {
            let new_x = x + d.0 as i32;
            let new_y = y + d.1 as i32;
            if in_bounds(new_x, new_y, v.len()) {
                let old_dist = distances.entry((new_x, new_y)).or_insert(i32::MAX);
                let new_dist = (-dist) + v[new_y as usize][new_x as usize];
                if new_dist < *old_dist {
                    distances.insert((new_x, new_y), new_dist);
                    q.push((-new_dist, new_x, new_y));
                }
            }
        }
    }

    *distances
        .get(&((v.len() - 1) as i32, (v.len() - 1) as i32))
        .unwrap()
}

fn in_bounds2(x: i32, y: i32, len: i32) -> bool {
    x >= 0 && x < 5 * len && y >= 0 && y < 5 * len
}

fn get_val(v: &[Vec<i32>], x: i32, y: i32, len: i32) -> i32 {
    (v[(y % len) as usize][(x % len) as usize] + (x / len) + (y / len) - 1) % 9 + 1
}

fn part_two(v: &[Vec<i32>]) -> i32 {
    let mut distances: HashMap<(i32, i32), i32> = HashMap::new();
    let mut q: BinaryHeap<(i32, i32, i32)> = BinaryHeap::new();
    let mut finish = false;
    let len = v.len() as i32;
    q.push((-v[0][1], 1, 0));
    q.push((-v[1][0], 0, 1));

    while !q.is_empty() && !finish {
        let (dist, x, y) = q.pop().unwrap();
        if x + 1 == 5 * len && y + 1 == 5 * len {
            finish = true;
        }

        for d in &DELTA {
            let new_x = x + d.0 as i32;
            let new_y = y + d.1 as i32;

            if in_bounds2(new_x, new_y, len) {
                let old_dist = distances.entry((new_x, new_y)).or_insert(i32::MAX);
                let new_dist = (-dist) + get_val(v, new_x, new_y, len);

                if new_dist < *old_dist {
                    distances.insert((new_x, new_y), new_dist);
                    q.push((-new_dist, new_x, new_y));
                }
            }
        }
    }

    *distances.get(&(5 * len - 1, 5 * len - 1)).unwrap()
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
