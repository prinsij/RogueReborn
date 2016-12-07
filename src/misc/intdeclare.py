##
# @file 	  declarefinder.py
# @author     Mikhail Andrenkov
# 
# @brief      Accumulates all integer declarations throughout the C++ files.
#

import os, re, sys

## Ignored paths
RE_PATH_IGNORE = re.compile(r"libtcod|ParseTest|html|misc|assets")
## C++ file extensions
RE_EXTENSION = re.compile(r"\.(cpp|h)")
## C++ header file
RE_HEADER_EXTENSION = re.compile(r"\.h$")
## Integer declaration
RE_INT_DECLARE = re.compile(r"(unsigned|int|long)\s+[A-Za-z]+\s*(,|;|=.*)\s*$")

OUTPUT_FILE = "./Declarations.txt"

def findDeclarations(cppFiles):
	declareList = []

	for cppFile in cppFiles:
		content = None
		with open(cppFile, "r") as fileIn:
			content = fileIn.readlines()

		for line in content:
			if RE_INT_DECLARE.search(line):
				declareList.append(line.strip())

	with open(OUTPUT_FILE, "w") as fileOut:
		fileOut.write("\n".join(declareList))
		
	for line in declareList:
		print line


##
#  @brief      Recursively finds all C++ source files
#
def findFiles():
	cppFiles = []
	exploreDirs = ["../."]

	while exploreDirs:
		currentDir = exploreDirs.pop()

		allFiles = os.listdir(currentDir)

		for nextDir in filter(lambda name: os.path.isdir(currentDir + "/" + name), allFiles):
			if not RE_PATH_IGNORE.search(nextDir):
				exploreDirs.append(currentDir + "/" + nextDir)

		for nextFile in filter(lambda name: not os.path.isdir(currentDir + "/" + name), allFiles):
			if RE_EXTENSION.search(nextFile):
				cppFiles.append(currentDir + "/" + nextFile)

	return cppFiles

##
#  @brief      Execution entry point
#
def main():
	cppFiles = findFiles()
	print "Found %d C++ files ..." % len(cppFiles),
	findDeclarations(cppFiles)
	print "Done."

if __name__ == "__main__":
	main()
