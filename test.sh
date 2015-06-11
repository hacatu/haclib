#!/bin/bash
runtest ()
{
	echo ./$1
	./$1 | tee ${1%.test}".output"
	diff -q ${1%.test}".output" ${1%.test}".expected"
}

rm *.output
tests = 0
passed = 0
for testprog in $@; do
	if runtest $testprog
	then
		echo PASSED
		((++passed))
	else
		exit 1
	fi
	((++tests))
done
rm *.output
echo "$passed/$tests tests passed"
if ((passed != tests))
then
	exit 1
fi

