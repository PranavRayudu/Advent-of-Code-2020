import re
from sys import stdin

# https://adventofcode.com/2020/day/4


data_table = {
    "byr": lambda arg: arg.isdigit() and 1920 <= int(arg) <= 2002,
    "iyr": lambda arg: arg.isdigit() and 2010 <= int(arg) <= 2020,
    "eyr": lambda arg: arg.isdigit() and 2020 <= int(arg) <= 2030,
    "hgt": lambda arg: (arg[-2:] == "cm" and arg[:-2].isdigit() and 150 <= int(arg[:-2]) <= 193)
                    or (arg[-2:] == "in" and arg[:-2].isdigit() and 59 <= int(arg[:-2]) <= 76),
    "hcl": lambda arg: re.compile("#[0-9a-f]{6}").match(arg),
    "ecl": lambda arg: arg in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"],
    "pid": lambda arg: len(arg) == 9 and arg.isdigit(),
    "cid": lambda arg: True
}

def process_data(data):
    tokens = data.split()
    valid_passport = True
    num_tokens = 0
    for token in tokens:
        key, val = token.split(":")
        if key not in data_table or not data_table[key](val):
            valid_passport = False
            break
        elif key != "cid":
            num_tokens += 1
    return valid_passport and num_tokens == 7

valid = 0
data = ""
for line in stdin:
    line = line.strip()
    if line:
        data += line + " "
    else:
        valid += 1 if process_data(data) else 0
        data = ""

valid += 1 if process_data(data) else 0

print(valid)
