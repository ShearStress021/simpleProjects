<<<<<<< HEAD
from pathlib import Path
from typing import List

=======
import string
from pathlib import Path
>>>>>>> origin/master


ROOT = Path().absolute()

FILENAME = "data/d1.txt"
<<<<<<< HEAD


PATH = ROOT / FILENAME 


def read_files():
    with open(PATH , 'r') as f:
        line = f.readline()

=======
path = ROOT / FILENAME

def part1():
    lines = read_file()
    pos = 50
    count = 0
    for line in lines:
        vec = int(line.strip().replace("L", '-').replace("R",''))
        pos = (pos + vec) % 100
        if pos == 0:
            count += 1

    return count


        
        
def part2() -> int:

    lines = read_file()
    pos = 50
    count = 0
    for line in lines:
        vec = int(line.strip().replace("L", '-').replace("R",''))
        if vec < 0:
           n, rem = divmod(vec, -100) 
           count += n
           if pos != 0 and pos + rem <= 0:
               count += 1

        else:
            n, rem = divmod(vec , 100)
            count += n
            if pos + rem >= 100:
                count += 1

        pos = (pos + vec) % 100


    return count



def read_file():

    with open(path, 'r') as f:
        lines = f.readlines()
    return lines   
>>>>>>> origin/master




<<<<<<< HEAD
=======
print(part1())
print(part2())
>>>>>>> origin/master

