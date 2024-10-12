from PIL import Image

NUM_CHARS = 3

def loadImage(pic):
  im = Image.open(pic)
  im = im.resize((im.size[0]//3, im.size[1]//3))
  im = im.rotate(90)
  return im
  pix = im.load()
  return (pix, im.size)

# def addPixel(pix, im_size, char: str):
#   for i in range(im_size[0]):
#     for j in range(im_size[1]):
#       print(i, j)
#       print(pix[i][j])
#       # if pix[i][j] != -1:
#         # print(pix[i][j])
#         # pix[i][j] = -1
#       return

def addAllPixel(im, char: str):
  f = open("./Logs/log.txt", "w")
  x, y = im.size
  for i in range(x):
    for j in range(y):
      coord = i, j
      if im.getpixel(coord) != (0,0,0,0):
        print(f"{i}/{x}, {j}/{y}")
        print(im.getpixel(coord))
        f.write(char*NUM_CHARS)
      else:
        f.write(" "*NUM_CHARS)
    f.write("\n")
  f.close()

def addPixel(im, char: str):
  f = open("./Logs/log.txt", "a")
  
  # input("")
  x, y = im.size
  new = False
  for i in range(x):
    for j in range(y):
      coord = i, j
      # Check if the color is not empty
      if im.getpixel(coord) != (0,0,0,0):
        # Check if we have visited the pixel, continue if we have
        # print("if1")
        if im.getpixel(coord) == (1,0,0, 254):
          # print("if2")
          continue
        new = True
        print(f"{i}/{x}, {j}/{y}")
        # print(im.getpixel(coord))
        f.write(char + char)
        im.putpixel(coord, (1,0,0,254))
        f.close()
        return im
      # If it is empty, and we have not visited it, put a space
      else:
        # print("else")
        new = True
        im.putpixel(coord, (1,0,0,254))
        f.write("  ")
    # print(f"printed new line, {i}, {j}")
    if new:
      f.write("\n")
  f.close()
  return im

f = open("./Logs/log.txt", "w")
f.close()
picture = "Pictures/pica.png"
im = loadImage(picture)
for i in range(im.size[0] * im.size[1]):
  im = addPixel(im, "*")

# input("continue? > ")
# im = loadImage(picture)
# f = open("./Logs/log.txt", "w")
# f.close()
# addAllPixel(im, "*")

print(im.size)
