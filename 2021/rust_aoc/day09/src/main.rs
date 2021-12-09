use std::collections::VecDeque;
use std::fs;

const INPUT_FILE: &str = "day09/src/input";

fn parse() -> Vec<String> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .lines()
        .map(|str| str.to_string())
        .collect()
}

fn coord_not_oob(new_x: i32, new_y: i32, v: &[String]) -> bool {
    !(new_x < 0 || new_x == v[0].len() as i32 || new_y < 0 || new_y == v.len() as i32)
}

fn part_one(v: &[String]) -> u32 {
    let mut sum = 0;
    let delta = vec![(1, 0), (0, 1), (-1, 0), (0, -1)];

    for (y, line) in v.iter().enumerate() {
        for (x, byte) in line.as_bytes().iter().enumerate() {
            let mut lowest = true;
            for d in &delta {
                let (new_x, new_y) = (x as i32 + d.0, y as i32 + d.1);
                if coord_not_oob(new_x, new_y, v)
                    && v[new_y as usize].as_bytes()[new_x as usize] <= *byte
                {
                    lowest = false;
                }
            }
            if lowest {
                sum += 1 + (byte - b'0') as u32;
            }
        }
    }

    sum
}

fn should_visit(x: i32, y: i32, v: &[String], visited: &[Vec<i32>]) -> bool {
    coord_not_oob(x, y, v)
        && v[y as usize].as_bytes()[x as usize] != b'9'
        && visited[y as usize][x as usize] == -1
}

fn bfs(x: i32, y: i32, v: &[String], visited: &mut [Vec<i32>], next: i32) {
    let mut queue: VecDeque<(i32, i32)> = VecDeque::from([(x, y)]);
    let delta: Vec<(i32, i32)> = vec![(1, 0), (0, 1), (-1, 0), (0, -1)];

    while !queue.is_empty() {
        let (curr_x, curr_y) = queue.pop_front().unwrap();
        visited[curr_y as usize][curr_x as usize] = next;

        for d in &delta {
            if should_visit(curr_x + d.0, curr_y + d.1, v, visited) {
                queue.push_back((curr_x + d.0, curr_y + d.1));
            }
        }
    }
}

fn part_two(v: &[String]) -> u32 {
    // Find and union might be better.
    let mut visited = vec![vec![-1; v[0].len()]; v.len()];
    let mut next: i32 = 0;

    for (y, line) in v.iter().enumerate() {
        for x in 0..line.as_bytes().len() {
            if should_visit(x as i32, y as i32, v, &visited) {
                bfs(x as i32, y as i32, v, &mut visited, next);
                next += 1;
            }
        }
    }

    let mut counter = vec![0; next as usize];

    for (y, line) in v.iter().enumerate() {
        for x in 0..line.as_bytes().len() {
            if visited[y][x] != -1 {
                counter[visited[y][x] as usize] += 1;
            }
        }
    }

    counter.sort_by(|a, b| b.cmp(a));
    counter[0] * counter[1] * counter[2]
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
