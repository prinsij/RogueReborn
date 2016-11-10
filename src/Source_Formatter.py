##
# @file Source_Formatter.py
# @author     Mikhail Andrenkov
# 
# @brief      Performs several formatting operations over the C++ header and source files.
#

import datetime, os, re, sys

## Ignored paths
RE_PATH_IGNORE = re.compile(r"libtcod|ParseTest|html")
## C++ file extensions
RE_EXTENSION = re.compile(r"\.(cpp|h)")
## C++ header file
RE_HEADER_EXTENSION = re.compile(r"\.h$") 
## C++ header class declaration
RE_HEADER_CLASS = re.compile(r"class\s+(?P<className>[a-zA-Z]+)\s+(:|{)")
## C++ source class declaration 
RE_SRC_CLASS = re.compile(r"^(?P<className>[a-zA-Z]+)::\1")

##
#  @brief      Removes all current 'pragma once' lines and define guards of the given C++ file; inserts a 'pragma once' into the file
#
#  @param      content  The content of the C++ file
# 
#  @return     A list denoting the formatted contents of the C++ file
#
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

##
#  @brief      Sorts the 'include' statements of the given C++ file
#
#  @param      content  The content of the C++ file
# 
#  @return     A list denoting the formatted contents of the C++ file
#
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


##
#  @brief      Trims the given C++ file
#
#  @param      content  The content of the C++ file
# 
#  @return     A list denoting the formatted contents of the C++ file
#
def trim(content):
	lineIndex = 0

	while lineIndex < len(content):
		line = content[lineIndex]
		if re.search(r"^(#.*|[A-Z]|[a-z])", line):
			return content[lineIndex:]
		lineIndex += 1

	return []

##
#  @brief      Adds a header to the given C++ file
#
#  @param      cppFile  The name of the C++ file
#  @param      content  The content of the C++ file
# 
#  @return     A list denoting the formatted contents of the C++ file
#
def addHeader(cppFile, content):
	if re.search(r"^/(\*|/)", content[0]):
		return content

	isHeader = RE_HEADER_EXTENSION.search(cppFile)

	cppName = cppFile[cppFile.rfind("/") + 1:]

	classNames = set()
	RE_CLASS_SEARCH = RE_HEADER_CLASS if isHeader else RE_SRC_CLASS
	for line in content:
		classResult = RE_CLASS_SEARCH.search(line)
		if classResult:
			classNames.add(classResult.group("className").strip())
	classNames = sorted(list(classNames))

	header = []
	header.append("/**")
	header.append(" * @file %s" % cppName)
	header.append(" * @author Team Rogue++")
	header.append(" * @date %s" % datetime.datetime.today().strftime('%B %d, %Y'))
	header.append(" *")
	if classNames:
		filePurpose = "declarations" if isHeader else "definitions"
		header.append(" * @brief Member %s for the %s class%s" % (filePurpose, ", ".join(classNames), "es" if len(classNames) > 1 else ""))
	else:
		header.append(" * @brief Global members")
	header.append(" */ ")
	header.append("")

	return header + content


##
#  @brief      Formats the content of the given C++ source file
#
#  @param      cppFile  The name of the C++ file
#  @param      content  The content of the C++ file
#
#  @return     A list denoting the formatted contents of the C++ file
#
def formatContent(cppFile, content):
	newContent = trim(content)
	newContent = sortIncludes(newContent)
	if re.search(r"test.*cpp|\.h$", cppFile):
		newContent = cleanPragmas(newContent)

	newContent = addHeader(cppFile, newContent)
	return newContent


##
#  @brief      Formats all of the given C++ source files
# 
#  @param      cppFiles  The C++ source files
#
def formatFiles(cppFiles):
	for cppFile in cppFiles:
		content = []
		with open(cppFile, "r") as f_in:
			content = map(lambda s: s.rstrip(), f_in.readlines())

		newContent = formatContent(cppFile, content)

		with open(cppFile, "w") as f_out:
			f_out.write("\n".join(newContent))


##
#  @brief      Recursively finds all C++ source files
#
def findFiles():
	cppFiles = []
	exploreDirs = ["."]

	while exploreDirs:
		currentDir = exploreDirs.pop()

		allFiles = os.listdir(currentDir)

		for nextDir in filter(lambda name: os.path.isdir(name), allFiles):
			if not RE_PATH_IGNORE.search(nextDir):
				exploreDirs.append(currentDir + "/" + nextDir)

		for nextFile in filter(lambda name: not os.path.isdir(name), allFiles):
			if RE_EXTENSION.search(nextFile):
				cppFiles.append(currentDir + "/" + nextFile)

	return cppFiles

##
#  @brief      Execution entry point
#
def main():
	cppFiles = findFiles()
	print "Formatting %d C++ files ..." % len(cppFiles),
	formatFiles(cppFiles)
	print "Done."

if __name__ == "__main__":
	main()
