
from tkinter import *
from PIL import ImageTk, Image
import sys, time

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
    return [list(map(int, line.split())) for line in sys.stdin]

def empty_coords(t):
    for i in range(len(t)):
        if 0 in t[i]:
            return i, t[i].index(0)
    return 0, 0

def launch():
    t = 0
    for i,j in moves:
        cnv.after(t*100, boardmove, i, j)
        t += 1

def soft_move(obj, newx, newy):
    x, y = cnv.coords(obj)
    dx, dy = newx - x, newy - y
    f = lambda c : cnv.move(obj, dx*c, dy*c)

    for i in range(10):
        mv = 1 - (i / 10)**2
        cnv.after(i*10, f, mv / 7.15)

    cnv.after(101, lambda : cnv.moveto(obj, newx, newy))

def boardmove(newi, newj):
    global i0, j0
    dx, dy = j0-newj, i0-newi
    # print("move", dx, dy)
    if (abs(dx) != 1 and abs(dy) != 1) or (dx and dy):
        print("invalid_move")
        return
    if newi < 0 or newi >= n or newj < 0 or newj >= n:
        print("invalid_move: out")
        return
    obj = objboard[board[newi][newj]]
    board[newi][newj], board[i0][j0] = board[i0][j0], board[newi][newj]
    soft_move(obj, j0 * cx, i0 * cy)
    i0, j0 = newi, newj
    # print(board)
    if board == target:
        print("You win !")
        # exit()
    
    

def key_press(event):
    code = event.keycode
    global i0, j0
    if event.char == 'q':
        root.destroy()
        exit()
    elif event.char == 'p':
        launch()
        return
    dx, dy = 0, 0
    if code == 113:
        print('left')
        dx -= 1
    elif code == 111:
        print('up')
        dy -= 1
    elif code == 114:
        print('right')
        dx += 1
    elif code == 116:
        print('down')
        dy += 1
    boardmove(i0-dy, j0-dx)

board, n = parse_board(sys.argv[1])
target = [[n*i+j for j in range(n)] for i in range(n)]
# board = target
i0, j0 = empty_coords(board)

moves = read_moves()

raw = Image.open("batiment.jpeg").reduce(2)
height = raw.height
width = raw.width

root = Tk()
cnv = Canvas(root, width=width, height=height)
cnv.pack()

cx = width / n
cy = height / n
imgtab = []
for i in range(n):
    for j in range(n):
        imgtab.append(ImageTk.PhotoImage(raw.crop((j * cx, i * cy, (j+1) * cx, (i+1) * cy))))
objboard = [None] * (n*n)
for j in range(n):
    for i in range(n):
        if board[i][j]:
            objboard[board[i][j]] = cnv.create_image(j * cx, i * cy, image=imgtab[board[i][j]], anchor="nw")


root.bind('<KeyPress>', key_press)

# cnv.after(1000, launch)
root.mainloop()