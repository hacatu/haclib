from statistics import median
from random import shuffle

def amax(v, i, j):
	max(enumerate(v[i:j]), key = lambda p: p[1])[0] + i

def sstep(v, i, j):
	mi = amax(v, i, j)
	(v[i], v[mi]) = (v[mi], v[i])

def ssort(v, i, j):
	while i < j:
		sstep(v, i, j)
		i += 1

def pivot(v, i, j):
	mi = (i + j)//2
	return median([v[i], v[mi], v[j]])

def partition(v, i, j):
	j -= 1
	p = pivot(v, i, j)
	while j > i:
		if v[i] >= p:
			(v[i], v[j]) = (v[j], v[i])
			if v[i] > p:
				j -= 1
		else:
			i += 1
	return i

def qstep(v, tps):
	(a, b) = tps.pop()
	while b - a > 1:
		p = partition(v, a, b)
		tps.append((p, b))
		b = p
	#ssort(v, a, b)

def qsort(v, i, j):
	tps = [(i, j)]
	while len(tps):
		qstep(v, tps)

def sort(v):
	qsort(v, 0, len(v))

x = list(range(1, 10))
shuffle(x)
print(x)
sort(x)
print(x)

