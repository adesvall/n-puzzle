
from tkinter import Tk, Canvas, Label
from PIL import ImageTk, Image 

# image1 = Image.open("batiment.jpeg")
height = 720
width = 1080
n = 4
board = [[4*i+j for j in range(n)] for i in range(n)]

root = Tk()
cnv = Canvas(root, width=width, height=height)
cnv.pack()

# test = ImageTk.PhotoImage(image1)

# label1 = Label(image=test)
# # label1.image = test

# # Position image
# label1.place(x=0, y=0, relwidth=width / image1.width, relheight=image1.height / height)

# # cnv.create_rectangle(20, 20, 80, 80, fill='red', outline='')

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

def key_release(event):
    # print(int(event.keycode))
    pass

root.bind('<KeyPress>', key_press)
root.bind('<KeyRelease>', key_release)

objboard = cnv.create_rectangle(100, 20, 100+42, 20+42, fill='blue', outline='')

def move(dx, dy):
    cnv.move(objboard, dx*42, dy*42)

# def effacer(c):
#     cnv.create_rectangle(100, 20, 100+c, 20+c, fill='white', outline='')
#     cnv.after(1000, dessiner, c)

# cnv.after(1000, dessiner, 42)

root.mainloop()