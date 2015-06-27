import os, subprocess, sys, random, shlex

def printFile(f):
	for line in f:
		print(line, end="")

class Test:
	def __init__(self, path, test, expected, seed, runs):
		self.path = path
		self.test = test
		self.expected = expected
		self.seed = seed
		self.runs = runs
	def __call__(self):
		def getSeed():
			return [str(random.randint(0, 2**32 - 1))] if self.seed else []
		if self.test is False:
			print("Test.fail")
			return False
		test = ["./" + self.test]
		if self.seed:
			random.seed(self.seed)
		with open(self.path + "/test.output", "w+") as outfile:
			for _ in range(0, self.runs):
				print(self.path)
				status = subprocess.call(test + getSeed(), cwd=self.path, stdout=outfile)
				outfile.seek(0)
				if status:
					printFile(outfile)
					return False
				if self.expected:
					status = subprocess.call(["diff", "-q", self.expected, "test.output"], cwd=self.path)
					if status:
						printFile(outfile)
						return False
			printFile(outfile)
		return True
		
Test.fail = Test(".", False, None, None, 1)

def hasTest(files):
	return any(filename.endswith((".test", ".c")) or filename == "makefile" for filename in files)

def loadConfig(path, files, defaults):
	options = defaults.copy()
	config = [filename for filename in files if filename.endswith("test.conf")]
	config = config[0] if config else None
	if config:
		print("loading configuration file " + path + "/" + config)
		with open(path + "/" + config) as conffile:
			for line in conffile:
				(key, _, val) = line.rstrip().partition(" ")
				options[key] = val.replace("~", os.getcwd())
	return options

def buildTest(path, files, options):
	status = 0
	if "makefile" in files:
		print("using makefile in " + path)
		status = subprocess.call(["make"], cwd=path)
	else:
		print("compiling c files in " + path)
		command = [options["cc"]] + shlex.split(options["cflags"]) + ["-o", "test.test"] + [srcfile for srcfile in files if srcfile.endswith(".c")] + shlex.split(options["ldflags"])
		print(" ".join(command))
		status = subprocess.call(command, cwd=path)
		if not status:
			files.append("test.test")
	return status

def makeTest(path, files, defaults):
	options = loadConfig(path, files, defaults)
	status = 0;
	if not any(filename.endswith(".test") for filename in files):
		status = buildTest(path, files, options)
	if status:
		return Test.fail
	expected = [filename for filename in files if filename.endswith(".expected")]
	expected = expected[0] if expected else None
	seed = options["seed"]
	runs = options["runs"]
	test = next(filename for filename in files if filename.endswith(".test"))
	return Test(path, test, expected, seed, runs)

defaults = loadConfig(".", os.listdir("."), {"seed": None, "runs": 1, "cc": "gcc", "cflags": "-Wall -c -std=c99", "ldflags": "-lm"})
testfiles = ((path, files) for (path, dirs, files) in os.walk(".") if not dirs and hasTest(files))
tests = (makeTest(path, files, defaults) for path, files in testfiles)
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

