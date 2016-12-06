from PIL import Image

def process(filename):
	imageFile = Image.open(filename)
	image = imageFile.load();

	rgb = [0,0,0]
	sizer = float(imageFile.width * imageFile.height)

	for x in xrange(imageFile.width):
		for y in xrange(imageFile.height):
			for i in [0,1,2]:
				rgb[i] += image[x, y][i] / sizer
	return rgb

print process('minlum.png')
print process('maxlum.png')