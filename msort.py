from random import shuffle

NIL = 0

def fix(seq):
	n = seq[0]
	i = seq[1]
	while i > 1:
		n[2][0] = n
		n = n[2]
		i -= 1
	seq[2] = n
	seq[0][0] = seq[2][2] = NIL

def merge(na, nb, sa, sb):
	#print("merge")
	s = n = NIL
	if na[1] < nb[1]:
		s = n = na
		na = na[2]
		sa -= 1
	else:
		s = n = nb
		nb = nb[2]
		sb -= 1
	while sa > 0 and sb > 0:
		#print(sa, sb)
		if na[1] < nb[1]:
			n[2] = na
			n = n[2]
			na = na[2]
			sa -= 1
		else:
			n[2] = nb
			n = n[2]
			nb = nb[2]
			sb -= 1
	n[2] = na if sa else nb
	return s

def mstep(seq, heads, step):
	#print("mstep")
	i = 0
	j = step
	while j < seq[1]:
		#print(i, j)
		heads[i] = merge(heads[i], heads[j], step, min(step, seq[1] - j))
		i += 2*step
		j += 2*step

def msort(seq):
	#print("msort")
	if seq[1] <= 1:
		return
	heads = []
	head = seq[0]
	while head is not NIL:
		heads.append(head)
		head = head[2]
	step = 1
	while step < seq[1]:
		mstep(seq, heads, step)
		step *= 2
	fix(seq)

def empty():
	return [0, 0, 0]

def pushr(s, e):
	n = [NIL, e, NIL]
	if s == empty():
		s[0] = s[2] = n
		s[1] += 1
	else:
		s[2][2] = n
		n[0] = s[2]
		s[2] = n
		s[1] += 1

def seqr(i):
	s = empty()
	for e in i:
		pushr(s, e)
	return s

def sprint(s):
	n = s[0]
	while n is not NIL:
		print(n[1], end = ",")
		n = n[2]

l = list(range(1, 10))
shuffle(l)
s = seqr(l)
sprint(s)
print("")
msort(s)
sprint(s)

