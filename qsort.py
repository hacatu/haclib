from statistics import median
from random import shuffle, randint

def snd(t):
	return t[1]

def mid(i, j):
	return (i + j)//2

def amax(v, i, j):
	max(enumerate(v[i:j]), key = snd)[0] + i

def swap(v, i, j):
	#print("swapping", i, j)
	(v[i], v[j]) = (v[j], v[i])
	#print(v)

def sstep(v, i, j):
	mi = amax(v, i, j)
	swap(v, i, mi)

def ssort(v, i, j):
	while i < j:
		sstep(v, i, j)
		i += 1

def pivot_first(v, i, j):
	return i

def pivot_random(v, i, j):
	return randint(i, j)

def pivot_median3(v, i, j):
	mi = mid(i, j)
	return median([(v[i], i), (v[mi], mi), (v[j], j)])[1]

def partition(v, i, j):
	j -= 1
	p = pivot_random(v, i, j)
	while 1:
		#print("poop", i, p, j)
		while v[i] < v[p]:
			i += 1
			#print("i", i, p, j)
		while v[p] <= v[j]:
			if p == j:
				p = mid(i, j)
				swap(v, p, j)
				if i == j:
					break
				continue
			j -= 1
			#print("j", i, p, j)
		if i >= j:
			break
		if p == j:
			p = i
		elif i == p:
			p = j
		swap(v, i, j)
	return p

def qstep(v, tps):
	(a, b) = tps.pop()
	while b - a > 1:
		p = partition(v, a, b)
		tps.append((p + 1, b))
		b = p
	#ssort(v, a, b)

def qsort(v, i, j):
	tps = [(i, j)]
	while len(tps):
		qstep(v, tps)

def sort(v):
	qsort(v, 0, len(v))

x = list(range(1, 100))
shuffle(x)
print(x)
sort(x)
print(x)

