import os

results = file("TestResults", "r").readlines()

failed = False

#Hashtags can be used for comments in the test files
#Otherwise, only a first character of "0" means success
#Anything else will fail!
for line in map(lambda s: s.strip(), results):
	print "[PYTHON TESTER] " + line

	lineList = map(lambda s: s.strip(), line.split(" "))

	#TESTER 0 Test ## Success/fail: comment
	if lineList[0] == "TESTER" and lineList[1] == "1":
		failed = True
		break

if failed:
	print "Failed!"
	raise Exception("Failure!")
else:
	print "[PYTHON TESTER] All tests have passed successfully!"
