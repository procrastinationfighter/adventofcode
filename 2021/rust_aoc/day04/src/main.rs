use std::fs;
const INPUT_FILE: &str = "day04/src/input";

#[derive(Clone)]
struct BingoBoard {
    board: [[i8; 5]; 5],
    solved: bool,
}

impl BingoBoard {
    fn mark_num(&mut self, num: i8) -> Option<u32> {
        if self.solved {
            return None;
        }

        for i in 0..5 {
            for j in 0..5 {
                if self.board[i][j] == num {
                    self.board[i][j] = -1;
                    if self.check_bingo(i, j) {
                        self.solved = true;
                        return Some(self.sum_unmarked());
                    }
                }
            }
        }

        None
    }

    fn check_bingo(&self, i: usize, j: usize) -> bool {
        let mut column_good = true;
        let mut row_good = true;

        for k in 0..5 {
            if self.board[i][k] >= 0 {
                row_good = false;
            }
            if self.board[k][j] >= 0 {
                column_good = false;
            }
        }

        column_good || row_good
    }

    fn sum_unmarked(&self) -> u32 {
        let mut sum: u32 = 0;

        for line in self.board {
            for num in line {
                if num > 0 {
                    sum += num as u32;
                }
            }
        }

        sum
    }
}

fn parse() -> (Vec<i8>, Vec<BingoBoard>) {
    let x = fs::read_to_string(INPUT_FILE).expect("file not read");
    let mut iter = x.lines();
    let numbers: Vec<i8> = iter
        .next()
        .unwrap()
        .split(',')
        .map(|y| y.parse().unwrap())
        .collect();
    let mut boards = vec![];

    while let Some(_) = iter.next() {
        let mut arr: [[i8; 5]; 5] = [[0i8; 5]; 5];
        for line in &mut arr {
            let nums: Vec<i8> = iter
                .next()
                .unwrap()
                .split_whitespace()
                .map(|y| y.parse().unwrap())
                .collect();
            line[..5].clone_from_slice(&nums[..5]);
        }
        boards.push(BingoBoard {
            board: arr,
            solved: false,
        });
    }
    (numbers, boards)
}

fn part_one(nums: &[i8], mut boards: Vec<BingoBoard>) -> u32 {
    for num in nums {
        for board in &mut boards {
            if let Some(x) = board.mark_num(*num) {
                return x * (*num as u32);
            }
        }
    }
    0
}

fn part_two(nums: &[i8], mut boards: Vec<BingoBoard>) -> u32 {
    let mut i = boards.len();

    for num in nums {
        for board in &mut boards {
            if let Some(x) = board.mark_num(*num) {
                i -= 1;

                if i == 0 {
                    return x * (*num as u32);
                }
            }
        }
    }
    0
}

fn main() {
    let (nums, boards) = parse();
    println!(
        "Part one: {}, part two: {}",
        part_one(&nums, boards.clone()),
        part_two(&nums, boards)
    );
}
