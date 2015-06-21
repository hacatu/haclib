import os, subprocess, sys, random

class Test:
	def __init__(self, path, test, expected, seed, runs):
		self.path = path
		self.test = test
		self.expected = expected
		self.seed = seed
		self.runs = runs
	def __call__(self):
		test = ["./" + self.test]
		def getSeed():
			return [str(random.randint(0, 2**32 - 1))] if self.seed else []
		if self.seed:
			random.seed(self.seed)
		with open(self.path + "/test.output", "w+") as outfile:
			for _ in range(0, self.runs):
				print(self.path)
				status = subprocess.call(test + getSeed(), cwd=self.path, stdout=outfile)
				outfile.seek(0)
				if status:
					for line in outfile:
						print(line, end="")
					return False
				if self.expected:
					status = subprocess.call(["diff", "-q", self.expected, "test.output"], cwd=self.path)
					if status:
						for line in outfile:
							print(line, end="")
						return False
			for line in outfile:
				print(line, end="")
		return True

def hasTest(files):
	return any(filename.endswith((".test", ".c")) or filename == "makefile" for filename in files)

def makeTest(path, files):
	config = [filename for filename in files if filename.endswith(".conf")]
	config = config[0] if config else None
	options = dict()
	if config:
		for line in open(config):
			(key, _, val) = line.partition(" ")
			options[key] = val
	status = 0;
	if not any(filename.endswith(".test") for filename in files):
		if "makefile" in files:
			print("using makefile in " + path)
			status = subprocess.call(["make"], cwd=path)
		else:
			print("compiling c files in " + path)
			print("gcc -I" + os.path.dirname(os.path.abspath(__file__)) + "/../src ...")
			status = subprocess.call(["gcc", "-std=c99", "-I" + os.path.dirname(os.path.abspath(__file__)) + "/../src", "-o", "test.test"] + [srcfile for srcfile in files if srcfile.endswith(".c")], cwd=path)
			files.append("test.test")
	expected = [filename for filename in files if filename.endswith(".expected")]
	expected = expected[0] if expected else None
	seed = options["seed"] if "seed" in options else None
	runs = options["runs"] if "runs" in options else 1
	test = next(filename for filename in files if filename.endswith(".test"))
	return Test(path, test, expected, seed, runs)

testfiles = ((path, files) for (path, dirs, files) in os.walk(".") if not dirs and hasTest(files))

tests = (makeTest(path, files) for path, files in testfiles)

passed = 0
tested = 0
for test in tests:
	if test():
		print("PASSED")
		passed += 1
	else:
		print("FAILED")
	tested += 1

print(str(passed) + "/" + str(tested) + " tests passed.")

sys.exit(passed != tested)

