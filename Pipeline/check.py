
import os

results = file("TestResults", "r").readlines()

x = False

#Hashtags can be used for comments in the test files
#Otherwise, only a first character of "0" means success
#Anything else will fail!
for i in results:
	print "[PYTHON TESTER] " + i
	if "0" != i[0] and "#" != i[0]:
		x = True
		break

if (x):
	print "Failed!"
	os.system("make -C ./.fail/")
else:
	print "[PYTHON TESTER] All tests have passed successfully!"