
from tkinter import *
from PIL import ImageTk, Image
import sys

raw = Image.open("batiment.jpeg")
height = raw.height
width = raw.width

root = Tk()
cnv = Canvas(root, width=width, height=height)
cnv.pack()

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

def empty_coords(t):
    for i in range(len(t)):
        if 0 in t[i]:
            return i, t[i].index(0)
    return 0, 0

board, n = parse_board(sys.argv[1])
target = [[n*i+j for j in range(n)] for i in range(n)]
i0, j0 = empty_coords(board)

cx = width / n
cy = height / n
imgtab = [[ImageTk.PhotoImage(raw.crop((j * cx, i * cy, (j+1) * cx, (i+1) * cy))) for j in range(n)] for i in range(n)]

objboard = [ [ cnv.create_image(cx * j, cy * i, image=imgtab[board[i][j] // n][board[i][j] % n], anchor="nw") if (i+j)!=0 else None for j in range(n) ] for i in range(n) ]

def soft_move(obj, dx, dy):
    f = lambda c : cnv.move(obj, dx*c, dy*c)
    x, y = cnv.coords(obj)

    for i in range(10):
        mv = 1 - (i / 10)**2
        cnv.after(i*10, f, mv / 7.15)

    cnv.after(100, lambda : cnv.moveto(obj, x+dx, y+dy))

def move(dx, dy):
    global i0, j0
    newi, newj = i0 - dy, j0 - dx
    if newi < 0 or newi >= n or newj < 0 or newj >= n:
        return
    obj = objboard[newi][newj]
    objboard[newi][newj], objboard[i0][j0] = objboard[i0][j0], objboard[newi][newj]
    board[newi][newj], board[i0][j0] = board[i0][j0], board[newi][newj]
    i0, j0 = newi, newj
    soft_move(obj, dx * cx, dy * cy)
    if board == target:
        print("You win !")
        exit()

def key_press(event):
    code = event.keycode
    if event.char == 'q':
        root.destroy()
        exit()
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
    move(dx, dy)

root.bind('<KeyPress>', key_press)

root.mainloop()