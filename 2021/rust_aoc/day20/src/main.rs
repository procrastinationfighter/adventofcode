use std::collections::HashMap;
use std::fs;

const INPUT_FILE: &str = "day20/src/input";

const DELTA: [(i64, i64); 9] = [
    (-1, -1),
    (0, -1),
    (1, -1),
    (-1, 0),
    (0, 0),
    (1, 0),
    (-1, 1),
    (0, 1),
    (1, 1),
];

fn parse() -> (Vec<u8>, Vec<Vec<u8>>) {
    let input = fs::read_to_string(INPUT_FILE).unwrap();
    let mut iter = input.lines();
    let code: Vec<u8> = iter.next().unwrap().bytes().collect();
    iter.next();
    let screen = iter.map(|x| x.bytes().collect()).collect();

    (code, screen)
}

fn calc_pixel(alg: &[u8], curr: &HashMap<(i64, i64), u8>, x: i64, y: i64, default: u8) -> u8 {
    let mut index = 0;

    for d in &DELTA {
        index *= 2;
        let (new_x, new_y) = (x as i64 + d.0, y as i64 + d.1);
        let ch = curr.get(&(new_x, new_y)).unwrap_or(&default);
        if *ch == b'#' {
            index += 1;
        }
    }

    alg[index]
}

fn calculate(alg: &[u8], screen: &[Vec<u8>], count: i64) -> u64 {
    let mut curr: HashMap<(i64, i64), u8> = HashMap::new();
    for (y, line) in screen.iter().enumerate() {
        for (x, pixel) in line.iter().enumerate() {
            curr.insert((x as i64, y as i64), *pixel);
        }
    }

    let mut default = b'.';

    for i in 0..count {
        let mut next: HashMap<(i64, i64), u8> = HashMap::new();
        for x in (-(i as i64) - 1)..(screen[0].len() as i64 + i + 1) {
            for y in (-(i as i64) - 1)..(screen.len() as i64 + i + 1) {
                next.insert((x, y), calc_pixel(alg, &curr, x, y, default));
            }
        }
        default = if i % 2 == 0 { alg[0] } else { alg[511] };
        curr = next;
    }

    curr.iter()
        .map(|x| if *x.1 == b'#' { 1_u64 } else { 0_u64 })
        .sum()
}

fn part_one(alg: &[u8], screen: &[Vec<u8>]) -> u64 {
    calculate(alg, screen, 2)
}

fn part_two(alg: &[u8], screen: &[Vec<u8>]) -> u64 {
    calculate(alg, screen, 50)
}

fn main() {
    let (alg, screen) = parse();
    println!(
        "Part one: {}, part two: {}",
        part_one(&alg, &screen),
        part_two(&alg, &screen)
    );
}
