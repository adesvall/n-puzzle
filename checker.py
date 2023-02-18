import sys

def empty_coords(t):
    for i in range(len(t)):
        if 0 in t[i]:
            return i, t[i].index(0)
    return 0, 0

def parse_board(file):
    boardfile = open(file, "r")
    t = boardfile.read().split('\n')
    if t[0][0] == '#':
        t = t[1:]
    n = int(t[0])
    t = t[1:]
    nt = []
    res = []
    for a in t:
        if a != '':
            nt.append(int(a))
            if len(nt) == n:
                res.append(nt)
                nt = []
    return res, n

def read_moves():
    file = open("sol.txt", "r")
    return [list(map(int, line.split())) for line in file]

board, n = parse_board(sys.argv[1])
target = [[n*i+j for j in range(n)] for i in range(n)]
moves = read_moves()
i0,j0 = empty_coords(board)
for i,j in moves:
    board[i][j], board[i0][j0] = board[i0][j0], board[i][j]
    i0, j0 = i, j

if board == target:
    print("You win !")
else:
    print("Error :")
    print(board)

