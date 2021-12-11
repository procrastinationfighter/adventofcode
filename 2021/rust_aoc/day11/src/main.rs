use std::fs;

const INPUT_FILE: &str = "day11/src/input";
const DELTA: [(i8, i8); 8] = [
    (1, 0),
    (-1, 0),
    (0, -1),
    (0, 1),
    (1, 1),
    (1, -1),
    (-1, 1),
    (-1, -1),
];

fn parse() -> Vec<Vec<i8>> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .lines()
        .map(|x| x.as_bytes().iter().map(|y| (*y - b'0') as i8).collect())
        .collect()
}

fn the_loop(v: &mut Vec<Vec<i8>>) -> u32 {
    let mut flashes = 0;

    for line in v.iter_mut() {
        for byte in line.iter_mut() {
            *byte += 1;
        }
    }

    let mut con = true;

    while con {
        con = false;
        for y in 0..v.len() {
            for x in 0..v[0].len() {
                if v[y][x] > 9 {
                    flashes += 1;
                    v[y][x] = -20;
                    con = true;
                    for (dx, dy) in &DELTA {
                        let (newx, newy) = (x as i8 + *dx, y as i8 + *dy);
                        if !(newx < 0
                            || newx as usize >= v[0].len()
                            || newy < 0
                            || newy as usize >= v.len())
                        {
                            v[newy as usize][newx as usize] += 1;
                        }
                    }
                }
            }
        }
    }

    for line in v.iter_mut() {
        for byte in line.iter_mut() {
            if *byte < 0 {
                *byte = 0;
            }
        }
    }

    flashes
}

fn part_one(mut v: Vec<Vec<i8>>) -> u32 {
    let mut flashes = 0;

    for _ in 0..100 {
        flashes += the_loop(&mut v);
    }

    flashes
}

fn part_two(mut v: Vec<Vec<i8>>) -> u32 {
    let mut i = 0;
    loop {
        i += 1;
        the_loop(&mut v);

        let mut ok = true;

        for line in &v {
            for byte in line {
                if *byte != 0 {
                    ok = false;
                }
            }
        }

        if ok {
            break;
        }
    }

    i
}

fn main() {
    let v = parse();

    println!(
        "Part one: {}, part two: {}",
        part_one(v.clone()),
        part_two(v)
    );
}
