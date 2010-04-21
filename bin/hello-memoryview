#! /bin/env python

import argparse
import curses
import time
import random

import numpy as np

import life

def gen_offsets():
    for i in (-1, 0, 1):
        for j in (-1, 0, 1):
            if i or j:
                yield i, j

def lifestub(curr, next):
    """
    Implement Conway Life rules.
    A cell is born if it has exactly 3 neighbours,
    stays alive if it has 2 or 3 living neighbours, and dies otherwise.
    @param curr: numpy 2d int array (will not be modified)
    @param next: numpy 2d int array (will be modified)
    """
    nrows, ncols = curr.shape
    for i in range(nrows):
        for j in range(ncols):
            value = curr[i, j]
            nneighbors = 0
            for di, dj in gen_offsets():
                ni = (i + di) % nrows
                nj = (j + dj) % ncols
                nneighbors += curr[ni, nj]
            if value and nneighbors in (2, 3):
                next[i, j] = 1
            elif (not value) and nneighbors == 3:
                next[i, j] = 1
            else:
                next[i, j] = 0

def draw_board(scr, board):
    nrows, ncols = board.shape
    for i in range(nrows):
        for j in range(ncols):
            c = 'O' if board[i, j] else '.'
            # A benign exception is raised when you draw on the last
            # character of a row, so ignore the exception.
            try:
                scr.addstr(i, j, c)
            except curses.error, e:
                pass
    scr.refresh()

def main(stdscr, args):
    # get the screen size
    nrows, ncols = stdscr.getmaxyx()
    # initialize the game of life board
    board_a = np.array([
        [random.randrange(2) for i in range(ncols)]
        for j in range(nrows)])
    # this is the back buffer for updating the board
    board_b = board_a.copy()
    # draw the board
    draw_board(stdscr, board_a)
    # do the main loop
    countbuffer = []
    while True:
        c = stdscr.getkey()
        if c == 'n':
            count = 1
            if countbuffer:
                count = int(''.join(countbuffer))
                countbuffer = []
            for i in range(count):
                # go to the next generation
                if args.fast:
                    life.step(board_a, board_b)
                else:
                    lifestub(board_a, board_b)
                # flip the boards
                board_a, board_b = board_b, board_a
            # draw the updated board
            draw_board(stdscr, board_a)
        elif c.isdigit():
            countbuffer.append(c)
        else:
            return

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fast', action='store_true',
            help='use a C extension for speed')
    args = parser.parse_args()
    curses.wrapper(main, args)
