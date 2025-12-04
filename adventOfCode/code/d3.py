import string
from pathlib import Path


ROOT = Path().absolute()

FILENAME = "data/t.txt"
path = ROOT / FILENAME

def part1():
    lines = read_file()
    total = 0
    for line in lines:
        num = line.strip()
        big = max(num[:-1])
        #print(num[num.index(big) + 1: ])
        one = max(num[num.index(big) + 1: ])
        
        total += int(str(big + one))
    return total
       # print(one)

        
        
def part2() -> int:

    lines = read_file()
    for line in lines:
        num = line.strip()
        print(num)
        print(len(num))
        
def read_file():

    with open(path, 'r') as f:
        lines = f.readlines()
    return lines   




print(part1())
print(part2())

