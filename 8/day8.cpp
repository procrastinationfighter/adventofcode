#include <iostream>
#include <vector>

enum class Instruction {
  NOP,
  ACC,
  JMP
};

Instruction str_to_instr(const std::string &s) {
  if (s == "nop") {
    return Instruction::NOP;
  }
  else if (s == "acc") {
    return Instruction::ACC;
  }
  else if (s == "jmp") {
    return Instruction::JMP;
  }
  else {
    throw std::domain_error(s);
  }
}

std::vector<std::pair<Instruction, int>> instructions;

void init() {
  std::string curr;
  while(std::getline(std::cin, curr)) {
    std::string instruction_type = curr.substr(0, 3);
    std::string value = curr.substr(4);
    Instruction instr = str_to_instr(instruction_type);
    int val = std::stoi(value);

    instructions.emplace_back(instr, val);
  }
}

int part_one() {
  std::vector<int> counting(instructions.size(), 0);
  int i = 0;
  int sum = 0;
  while (counting[i] == 0 && i < instructions.size()) {
    counting[i]++;

    switch (instructions[i].first) {
      case Instruction::ACC: sum += instructions[i].second;
        break;
      default:
        break;
    }

    if (instructions[i].first == Instruction::JMP) {
      i += instructions[i].second;
    } else {
      i++;
    }
  }

  return sum;
}

bool is_there_a_loop(std::vector<int> counting, int i) {
  counting[i]--;
  while(counting[i] == 0 && i < instructions.size()) {
    counting[i]++;

    if (instructions[i].first == Instruction::JMP) {
      i += instructions[i].second;
    } else {
      i++;
    }
  }

  return i < instructions.size();
}

int part_two() {
  int sum = 0;
  std::vector<int> counting(instructions.size(), 0);
  int i = 0;
  bool continue_testing = true;

  while (counting[i] == 0 && i < instructions.size()) {
    counting[i]++;

    switch (instructions[i].first) {
      case Instruction::ACC: sum += instructions[i].second;
        break;
      case Instruction::NOP:
        if(continue_testing) {
          instructions[i].first = Instruction::JMP;
          if (is_there_a_loop(counting, i)) {
            instructions[i].first = Instruction::NOP;
          }
          else {
            continue_testing = false;
          }
        }
        break;

      case Instruction::JMP:
        if(continue_testing) {
          instructions[i].first = Instruction::NOP;
          if (is_there_a_loop(counting, i)) {
            instructions[i].first = Instruction::JMP;
          }
          else {
            continue_testing = false;
          }
        }
        break;
      default:
        break;
    }

    if (instructions[i].first == Instruction::JMP) {
      i += instructions[i].second;
    } else {
      i++;
    }
  }

  return sum;
}

int main() {
  init();
  std::cout << part_one() << " " << part_two() << "\n";
  return 0;
}