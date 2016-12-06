from PIL import Image

R_ = 0.299
G_ = 0.587
B_ = 0.114

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

def L(rgb):
	return R_ * rgb[0] + G_ * rgb[1] + B_ * rgb[2]

minlum = process('minlum.png')
maxlum = process('maxlum.png')

L_min = L(minlum)
L_max = L(maxlum)

print "Min luminosity:", L_min
print "Max luminosity:", L_max
print "Diff: ", (L_max - L_min) / 255