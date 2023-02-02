import sys
import math
import heapq

board = []
for i in range(3):
    board.append([int(j) for j in input().split()])

def print_res(t):
    if not t.parent:
        return
    i,j = t.emptycoord
    print_res(t.parent)
    print(i, j)

def empty_coord(t):
    for i in range(len(t)):
        if 0 in t[i]:
            return i, t[i].index(0)
    return 0, 0

def swap(bd, i0, j0, dr):
    t = [list(bd[i]) for i in range(3)]
    i1 = i0 + (dr == 2) - (dr == 0)
    j1 = j0 + (dr == 1) - (dr == 3)
    tmp = t[i0][j0]
    t[i0][j0] = t[i1][j1]
    t[i1][j1] = tmp
    return t

def hash(board):
    return tuple(tuple(l) for l in board)

def find_conflict(bd):
    cost=0
    for i in range(len(bd)):
        for j in range(len(bd[0])):
            if i - bd[i][j] // 4 == 0:
                for j2 in range(j+1, len(bd[0])):
                    if i - bd[i][j2] // 4 == 0 and 0 < bd[i][j2] < bd[i][j]:
                        cost+=1
            if j - bd[i][j] % 4 == 0:
                for i2 in range(i+1, len(bd)):
                    if j - bd[i2][j] % 4 == 0 and 0 < bd[i2][j] < bd[i][j]:
                        cost+=1
    return cost

def estimate_cost(bd):
    cost = 2* find_conflict(bd)
    for i in range(len(bd)):
        for j in range(len(bd[0])):
            if bd[i][j] != 0:
                cost += 0.25 * (bd[i][j] % 4+1) * (abs(i - bd[i][j] // 4) + abs(j - bd[i][j] % 4))
    return cost

class State:
    def __init__(self, f, board, emptycoord, parent) -> None:
        self.f = f
        self.g = estimate_cost(board)
        self.board = board
        self.emptycoord = emptycoord
        self.parent = parent
    
    def update(self, f, parent):
        self.f = f
        self.parent = parent

    def __lt__(self, o):
        return self.f + self.g < o.f + o.g
    
    def __repr__(self):
        return f"STATE f: {self.f}   g: {self.g}   board: {self.board}"

initState = State(0, board, empty_coord(board), None)
opened = [initState]
heapq.heapify(opened)
openset = {
    hash(board) : initState
} # hashable state => State node

# Moves: how to caracterize a move
#   a move is a direction

closed = []
target = [[4*i, 4*i+1, 4*i+2, 4*i+3] for i in range(3)]
targetset = set()
targetset.add(hash(target))

while opened:
    curr = heapq.heappop(opened)
    # print(curr)
    # print(openset)
    del openset[hash(curr.board)]
    f = curr.f
    i0, j0 = curr.emptycoord
    closed.append(curr)
    for dr in range(4):
        if not 0 <= i0 + (dr == 2) - (dr == 0) < 3:
            continue
        if not 0 <= j0 + (dr == 1) - (dr == 3) < 4:
            continue
        newboard = swap(curr.board, i0, j0, dr)

        h = hash(newboard)
        new_empty = i0 + (dr == 2) - (dr == 0), j0 + (dr == 1) - (dr == 3)
        if h in targetset:
            print("trouvé")
            print_res(curr)
            i, j = new_empty
            print(i, j)
            exit()

        if h not in openset:
            openset[h] = State(f+1, newboard, new_empty, curr)
            heapq.heappush(opened, openset[h])
        elif f+1 < openset[h].f:
            openset[h].f = f+1
            heapq.heapify(opened)
    #print(closed[-1][:2], file=sys.stderr, flush=True)

t = closed[-1]

print_res(t)
print('caca')
# To debug: print("Debug messages...", file=sys.stderr, flush=True)

