from PIL import Image


def loadImage(pic):
  im = Image.open(pic)
  im = im.resize((im.size[0]//5, im.size[1]//5))
  im = im.rotate(90)
  return im
  pix = im.load()
  return (pix, im.size)

def addPixel(pix, im_size, char: str):
  for i in range(im_size[0]):
    for j in range(im_size[1]):
      print(i, j)
      print(pix[i][j])
      # if pix[i][j] != -1:
        # print(pix[i][j])
        # pix[i][j] = -1
      return


picture = "Pictures/pica.png"
im = loadImage(picture)
addPixel(im, "*")

# print(im.size)
