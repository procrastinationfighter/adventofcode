use crate::Packet::{FourType, OtherType};
use std::fs;
use to_binary::BinaryString;

const INPUT_FILE: &str = "day16/src/input";

enum Packet {
    FourType(u8, u8, u64),
    OtherType(u8, u8, Vec<Packet>),
}

// Version, type id, type len, value, subpackets.
// pub type Packet = (u8, u8, u8, u32, Vec<Box<Packet>>);

fn read_packet(bits: &str) -> (Packet, usize) {
    let packet_version = u8::from_str_radix(&bits[0..3], 2).unwrap();
    let packet_type_id = u8::from_str_radix(&bits[3..6], 2).unwrap();

    let mut j = 6;
    return match packet_type_id {
        4 => {
            let mut value: u64 = 0;
            let mut finish = false;
            while !finish {
                finish = &bits[j..(j + 1)] == "0";
                value *= 16;
                value += u64::from_str_radix(&bits[(j + 1)..(j + 5)], 2).unwrap();
                j += 5;
            }
            (FourType(packet_version, packet_type_id, value), j)
        }
        _ => {
            let mut subpackets: Vec<Packet> = vec![];
            let packet_len_type_id = u8::from_str_radix(&bits[(j)..(j + 1)], 2).unwrap();
            j += 1;
            match packet_len_type_id {
                0 => {
                    let bits_count = usize::from_str_radix(&bits[j..(j + 15)], 2).unwrap();
                    j += 15;
                    let mut k = 0;
                    loop {
                        let pack = read_packet(&bits[(j + k)..]);
                        subpackets.push(pack.0);

                        k += pack.1;
                        if k == bits_count {
                            j += k;
                            break;
                        }
                    }
                }
                1 => {
                    let bits_count = usize::from_str_radix(&bits[j..(j + 11)], 2).unwrap();
                    j += 11;
                    let mut k = 0;
                    for _ in 0..bits_count {
                        let pack = read_packet(&bits[(j + k)..]);
                        subpackets.push(pack.0);
                        k += pack.1;
                    }
                    j += k;
                }
                _ => panic!("Unknown len type id: {}", packet_len_type_id),
            }
            (OtherType(packet_version, packet_type_id, subpackets), j)
        }
    };
}

fn parse() -> Packet {
    read_packet(
        BinaryString::from_hex(
            fs::read_to_string(INPUT_FILE)
                .unwrap()
                .lines()
                .next()
                .unwrap(),
        )
        .unwrap()
        .to_string()
        .as_str(),
    )
    .0
}

fn sum_version_numbers(packet: &Packet) -> u32 {
    let mut sum: u32 = 0;

    match packet {
        FourType(ver, _, _) => sum += *ver as u32,
        OtherType(ver, _, subpackets) => {
            sum += *ver as u32;
            for packet in subpackets {
                sum += sum_version_numbers(packet);
            }
        }
    }

    sum
}

fn part_one(packet: &Packet) -> u32 {
    sum_version_numbers(packet)
}

fn calculate(packet: &Packet) -> u64 {
    match packet {
        FourType(_, _, val) => *val,
        OtherType(_, id_type, packets) => {
            let values: Vec<u64> = packets.iter().map(|packet| calculate(packet)).collect();
            match id_type {
                0 => values.iter().sum(),
                1 => {
                    let mut mul: u64 = 1;
                    for val in values {
                        mul *= val;
                    }
                    mul
                }
                2 => *values.iter().min().unwrap(),
                3 => *values.iter().max().unwrap(),
                5 => {
                    if values[0] > values[1] {
                        1
                    } else {
                        0
                    }
                }
                6 => {
                    if values[0] < values[1] {
                        1
                    } else {
                        0
                    }
                }
                7 => {
                    if values[0] == values[1] {
                        1
                    } else {
                        0
                    }
                }
                _ => panic!("Wrong id type"),
            }
        }
    }
}

fn part_two(packet: &Packet) -> u64 {
    calculate(packet)
}

fn main() {
    let v = parse();
    println!("Part one: {}, part two: {}", part_one(&v), part_two(&v));
}
