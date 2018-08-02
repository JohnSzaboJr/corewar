
.name "ST"
.comment "I'M ST"

l2:		sti r1, %:live, %1
		st r1, r2
		st r2, 100
		st r2, -100
		st r2, 511
		st r2, -511
		st r2, 512
		st r2, -512
		add r1, r2, r1
		and r3, %0, r3

live:	live %1
		zjmp %:l2
