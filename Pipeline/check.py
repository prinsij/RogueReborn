
import os

results = file("TestResults", "r").readlines()

x = False

for i in results:
	if "0" in i:
		x = True

if (x):
	print "Failed!"
	os.system("make -C ./.fail/")
else:
	print "OK!"