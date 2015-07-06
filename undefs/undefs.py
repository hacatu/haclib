import os, sys

folder = sys.argv[1]
file_prefix = sys.argv[2]

files = (path + "/" + filename for (path, _, files) in os.walk(folder) for filename in files if file_prefix in filename)
for filename in files:
	with open(filename) as defs:
		for line in defs:
			if line.startswith("#define "):
				start = 8
				if line[start] == '/':
					start = line.find("/", start + 3) + 1
				end = line.find(" ", start + 1)
				if end == -1:
					end = len(line)
				print("#undef", line[start:end])

