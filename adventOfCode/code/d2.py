import string
from pathlib import Path


ROOT = Path().absolute()

FILENAME = "data/d2.txt"
path = ROOT / FILENAME

def part1():
    lines = read_file()
    
    ranges = [list(map(int, n.strip().split("-"))) for n in lines.split(",")]
    total = 0
    for nums in ranges:
        for i in range(nums[0], nums[-1]+1):
            s = str(i)
            n = len(s)
            if n  % 2 == 0 and s[:n//2] == s[n//2:]:
                total += i

    return total
        




        
        
def part2() -> int:

    lines = read_file()
    
    ranges = [list(map(int, n.strip().split("-"))) for n in lines.split(",")]
    numbers = sum((list(range(a, b + 1)) for a, b in ranges),[])
    total = 0

    for num in numbers:
        s = str(num)
        for i in range(2, len(s) + 1):
            if len(s) % i == 0 and s[: (len(s) // i) ] * i  == s:
                total += num
                break

    return total
def read_file():

    with open(path, 'r') as f:
        lines = f.read()
    return lines   




print(part1())
print(part2())

