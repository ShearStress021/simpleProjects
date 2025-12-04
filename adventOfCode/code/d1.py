from pathlib import Path
from typing import List



ROOT = Path().absolute()

FILENAME = "data/d1.txt"


PATH = ROOT / FILENAME 


def read_files():
    with open(PATH , 'r') as f:
        line = f.readline()






