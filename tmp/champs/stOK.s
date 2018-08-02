
.name "STOK"
.comment "I'M ST"

l2:		ld %3149642683, r3
		st r3, r2
		st r2, -511
		st r2, 511
		st r2, -512
		st r2, 512
		st r2, -513
		st r2, 513
		st r2, -256
		st r2, 256
		st r2, 3000
		st r2, -3000
		and r1, %0, r1

live:	live %1
		zjmp %:live
