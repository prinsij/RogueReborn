# Formats CPP preambles

import os, re, sys


PARSE_DIR = "./ParseTest/"


def cleanPragmas(content):
	removeList = []

	for lineIndex in xrange(len(content)):
		line = content[lineIndex]
		if re.search(r"#pragma.*once", line):
			removeList.append(lineIndex)
		if re.search(r"#(ifdef.*_H|ifndef.*_H|define.*_H|endif)", line):
			removeList.append(lineIndex)

	newContent = ["#pragma once", ""]

	for lineIndex in xrange(len(content)):
		if lineIndex not in removeList:
			newContent.append(content[lineIndex])

	return newContent


def sortIncludes(content):
	includeCustom = []
	includeLib = []
	lineIndex = 0
	lastIncludeIndex = 0

	while lineIndex < len(content):
		line = content[lineIndex]
		if re.match(r"^#include.*\<", line):
			includeLib.append(line)
			lastIncludeIndex = lineIndex
		elif re.match(r"^#include.*\"", line):
			includeCustom.append(line)
			lastIncludeIndex = lineIndex
		elif re.match(r"^[A-Z]|[a-z]", line) or re.search(r"^/", line):
			break

		lineIndex += 1

	newIncludes = []

	for lineLib in sorted(includeLib):
		newIncludes.append(lineLib)

	if includeLib and includeCustom: newIncludes.append("")
	
	for lineCustom in sorted(includeCustom):
		newIncludes.append(lineCustom)

	return newIncludes + [""] + content[lineIndex:]


def trim(content):
	lineIndex = 0

	while lineIndex < len(content):
		line = content[lineIndex]
		if re.search(r"^(#.*|[A-Z]|[a-z])", line):
			return content[lineIndex:]
		lineIndex += 1

	return []


def addHeader(cppFile, content):
	if re.search(r"^/\*", content[0]):
		return content

	header = []
	header.append("/**")
	header.append(" * Rogue Reborn Project")
	header.append(" * Team Rogue++")
	header.append(" * ")
	header.append(" * File: %s" % cppFile[cppFile.rfind("/") + 1:])
	header.append(" */ ")
	header.append("")

	return header + content


def mutateContent(cppFile, content):
	newContent = trim(content)
	newContent = sortIncludes(newContent)
	if re.search(r"test.*cpp|\.h$", cppFile):
		print cppFile
		newContent = cleanPragmas(newContent)

	newContent = addHeader(cppFile, newContent)
	return newContent


def modifyFiles(cppFiles):
	#os.system("mkdir \"%s\"" % PARSE_DIR)

	for cppFile in cppFiles:
		content = []
		with open(cppFile, "r") as f_in:
			content = f_in.readlines()

		content = map(lambda s: s.rstrip(), content)
		newContent = mutateContent(cppFile, content)

		#for pathIndex in xrange(2, len(cppFile.split("/"))):
		#	os.system("mkdir \"%s\"" % (PARSE_DIR + "/".join(cppFile.split("/")[1:pathIndex])))			


		with open(cppFile, "w") as f_out:
			f_out.write("\n".join(newContent))


# Recursively finds all *.cpp and *.h files
def findFiles():
	cppFiles = []
	exploreDirs = ["."]

	while exploreDirs:
		currentDir = exploreDirs.pop()

		allFiles = os.listdir(currentDir)

		for nextDir in filter(lambda name: os.path.isdir(name), allFiles):
			if not re.search(r"libtcod|ParseTest|html", nextDir):
				exploreDirs.append(currentDir + "/" + nextDir)

		for nextFile in filter(lambda name: not os.path.isdir(name), allFiles):
			if re.match(r".*(cpp|h)", nextFile):
				cppFiles.append(currentDir + "/" + nextFile)

	return cppFiles


def main():
	cppFiles = findFiles()
	print "Found %d CPP files" % len(cppFiles)
	modifyFiles(cppFiles)

if __name__ == "__main__":
	main()
