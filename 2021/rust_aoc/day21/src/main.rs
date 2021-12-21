const PLAYER_1_START: u32 = 4;
const PLAYER_2_START: u32 = 9;

// Calculated in Python, possible moves: Counter({6: 7, 5: 6, 7: 6, 4: 3, 8: 3, 3: 1, 9: 1})
const PART_TWO_MOVES: [(u64, u64); 7] = [(6, 7), (5, 6), (7, 6), (4, 3), (8, 3), (3, 1), (9, 1)];

fn part_one() -> u32 {
    let mut dice_val = 1;
    let (mut first_pos, mut first_score) = (PLAYER_1_START, 0);
    let (mut second_pos, mut second_score) = (PLAYER_2_START, 0);
    let mut roll_count = 0;
    let mut first_now = true;

    loop {
        let move_val = dice_val + (dice_val % 100 + 1) + ((dice_val + 1) % 100 + 1);
        dice_val = ((dice_val + 2) % 100) + 1;
        roll_count += 3;

        if first_now {
            first_pos = (first_pos + move_val - 1) % 10 + 1;
            first_score += first_pos;
            first_now = false;
        } else {
            second_pos = (second_pos + move_val - 1) % 10 + 1;
            second_score += second_pos;
            first_now = true;
        }

        if second_score >= 1000 || first_score >= 1000 {
            break;
        }
    }

    roll_count * u32::min(first_score, second_score)
}

fn calc(first: (u64, u64), second: (u64, u64), first_now: bool) -> (u64, u64) {
    if first.0 >= 21 {
        return (1, 0);
    } else if second.0 >= 21 {
        return (0, 1);
    }

    let mut sum: (u64, u64) = (0, 0);

    for mov in &PART_TWO_MOVES {
        if first_now {
            let new_pos = (first.1 + mov.0 - 1) % 10 + 1;
            let res = calc((first.0 + new_pos, new_pos), second, false);
            sum.0 += mov.1 * res.0;
            sum.1 += mov.1 * res.1;
        } else {
            let new_pos = (second.1 + mov.0 - 1) % 10 + 1;
            let res = calc(first, (second.0 + new_pos, new_pos), true);
            sum.0 += mov.1 * res.0;
            sum.1 += mov.1 * res.1;
        }
    }

    sum
}

fn part_two() -> u64 {
    let res = calc((0, PLAYER_1_START as u64), (0, PLAYER_2_START as u64), true);

    u64::max(res.0, res.1)
}

fn main() {
    println!("Part one: {}, part two: {}", part_one(), part_two());
}
