use std::fs;

#[derive(Clone)]
enum SnailNumber {
    Num(u8),
    Pair(Box<SnailNumber>, Box<SnailNumber>),
}

const INPUT_FILE: &str = "day18/src/input";

fn read_snail_num(text: &str) -> (Box<SnailNumber>, usize) {
    if text[0..1] == *"[" {
        let (left, left_id) = read_snail_num(&text[1..]);
        assert_eq!(text[left_id + 1..left_id + 2], *",");
        let (right, right_id) = read_snail_num(&text[(left_id + 2)..]);
        assert_eq!(text[left_id + right_id + 2..left_id + right_id + 3], *"]");
        (
            Box::new(SnailNumber::Pair(left, right)),
            left_id + right_id + 3,
        )
    } else {
        // Must be a number.
        (
            Box::new(SnailNumber::Num(text[0..1].parse::<u8>().unwrap())),
            1,
        )
    }
}

fn parse() -> Vec<Box<SnailNumber>> {
    fs::read_to_string(INPUT_FILE)
        .unwrap()
        .lines()
        .map(|x| read_snail_num(x).0)
        .collect()
}

fn split(snail: &mut Box<SnailNumber>) -> bool {
    match snail.as_mut() {
        SnailNumber::Num(n) => {
            if *n >= 10 {
                **snail = SnailNumber::Pair(
                    Box::new(SnailNumber::Num(*n / 2)),
                    Box::new(SnailNumber::Num((*n + 1) / 2)),
                );
                true
            } else {
                false
            }
        }
        SnailNumber::Pair(l, r) => {
            let mut ok = split(l);
            if !ok {
                ok = split(r);
            }

            ok
        }
    }
}

fn add_to_right(snail: &mut Box<SnailNumber>, val: u8) {
    match snail.as_mut() {
        SnailNumber::Num(n) => *n += val,
        SnailNumber::Pair(_, r) => add_to_right(r, val),
    }
}

fn add_to_left(snail: &mut Box<SnailNumber>, val: u8) {
    match snail.as_mut() {
        SnailNumber::Num(n) => *n += val,
        SnailNumber::Pair(l, _) => add_to_left(l, val),
    }
}

fn explode(snail: &mut Box<SnailNumber>, depth: u8) -> (bool, Option<u8>, Option<u8>) {
    match snail.as_mut() {
        SnailNumber::Num(_) => (false, None, None),
        SnailNumber::Pair(l, r) => {
            if depth == 4 {
                match (&**l, &**r) {
                    (SnailNumber::Num(left), SnailNumber::Num(right)) => {
                        let ret = (true, Some(*left), Some(*right));
                        **snail = SnailNumber::Num(0);
                        ret
                    }
                    (_, _) => panic!("Tree too deep already!"),
                }
            } else {
                let left = explode(l, depth + 1);
                if left.0 {
                    if let Some(val) = left.2 {
                        add_to_left(r, val);
                        (true, left.1, None)
                    } else {
                        left
                    }
                } else {
                    let right = explode(r, depth + 1);
                    if right.0 {
                        if let Some(val) = right.1 {
                            add_to_right(l, val);
                            (true, None, right.2)
                        } else {
                            right
                        }
                    } else {
                        (false, None, None)
                    }
                }
            }
        }
    }
}

fn calc_magnitude(snail: &SnailNumber) -> u64 {
    match snail {
        SnailNumber::Num(n) => *n as u64,
        SnailNumber::Pair(l, r) => 3 * calc_magnitude(l) + 2 * calc_magnitude(r),
    }
}

fn reduce(snail: &mut Box<SnailNumber>) {
    loop {
        let x = explode(snail, 0);
        if !x.0 {
            let x = split(snail);
            if !x {
                break;
            }
        }
    }
}

fn part_one(v: &[Box<SnailNumber>]) -> u64 {
    let mut sum = v[0].clone();
    for snail in v[1..].iter() {
        sum = Box::new(SnailNumber::Pair(sum, snail.clone()));
        reduce(&mut sum);
    }
    calc_magnitude(&sum)
}

fn part_two(v: &[Box<SnailNumber>]) -> u64 {
    let mut max = 0;

    for (i, snail) in v.iter().enumerate() {
        for second_snail in v[i + 1..].iter() {
            let mut left = Box::new(SnailNumber::Pair(snail.clone(), second_snail.clone()));
            let mut right = Box::new(SnailNumber::Pair(second_snail.clone(), snail.clone()));
            reduce(&mut left);
            reduce(&mut right);
            max = u64::max(max, u64::max(calc_magnitude(&left), calc_magnitude(&right)));
        }
    }

    max
}

fn print_snail(snail: &SnailNumber) {
    match snail {
        SnailNumber::Num(n) => {
            print!("{}", *n)
        }
        SnailNumber::Pair(l, r) => {
            print!("[");
            print_snail(l);
            print!(",");
            print_snail(r);
            print!("]");
        }
    }
}

fn main() {
    let v = parse();

    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
