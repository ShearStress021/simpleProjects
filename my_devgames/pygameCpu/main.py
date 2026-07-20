import pygame
import sys
import numpy
import os

screen = None
win_s = 3
surf = None

cpu_cycles = 0

CYCLES_PER_FRAME = 29780
PC= 0x0000

A=0; X=0;Y=0;S=0xFD;P=0
C=0;Z=0;I=1;D=0;V=0;N=0
opcode = 0x00

RAM = bytearray(0x0800)
MEM = bytearray(0x10000)


#PPU
ppu_open_bus = 0x00

def ppu_write(cpu_addr, val):
    global ppu_open_bus, ppu_ctl,ppu_mask,oam_addr

    ppu_open_bus = val

    reg = 0x2000 + (cpu_addr % 8)

    if reg == 0x2000:
        ppu_ctl = val
        return





def cpu_write(addr, val):
    global MEM
    val &= 0xFF

    if addr < 0x2000:
        global RAM
        RAM[addr % 0x8000] = val
        return 

    if addr < 0x4000:
        ppu_write(addr, val)
        return





def stack_push(val):
    global S
    cpu_write(0x0100+S, val)
    S = (S - 1) & 0xFF


def stack_push_16(val):
    stack_push((val >> 8) & 0xFF)
    stack_push(val & 0xFF)


def BRK():
    global PC,I, P, C, X, I, D,V ,N

    PC = (PC + 1) & 0xFFFF
    stack_push_16(PC)


INSTRUCTION_TABLE = [
     # 0x00 - 0x07
     BRK, ORA_IND_X, None, SLO_IND_X, ILGL_04, ORA_ZP, ASL_ZP, SLO_ZP,  

]


def step_cpu():
    global PC, opcode, cpu_cycles, INSTRUCTION_TABLE


    ...

def step_forward_until_frame():
    global cpu_cycles, CYCLES_PER_FRAME

    cycles_at_start = cpu_cycles

    while (cpu_cycles - cycles_at_start) < CYCLES_PER_FRAME:
        step_cpu()

def init_nonDebug():
    global screen;
    clock = pygame.time.Clock()
    running = True;
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        screen.fill("yellow")

        fps = int(clock.get_fps())
        pygame.display.set_caption(f"PPU ||| FPS: {fps}")
        pygame.display.flip()
        clock.tick(60)
    pygame.quit()
    sys.exit(0)

def main():
    global screen, win_s, surf
    pygame.init()
    screen = pygame.display.set_mode((256*win_s, 240*win_s))
    surf = pygame.Surface((256, 240))


    init_nonDebug()

if __name__ == "__main__":
    main()
