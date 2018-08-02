.name "LD"
.comment "I'M LD"

l2:		ld 1, r2
		st r2, -75


		ld -1, r2
		st r2, -200
		ld -2, r3
		st r3, -200
		ld %-3, r3
		st r3, -200
		ld %-4, r4
		st r4, -200

		ld 512, r2
		st r2, -200
		ld -512, r3
		st r3, -200
		ld %512, r3
		st r3, -200
		ld %-512, r4
		st r4, -200
		ld -1, r3
		st r2, -100
		ld %2, r3
		st r3, -150
		ld %-2, r4
		st r4, -75
		ld 511, r2
		st r2, -30
		ld -511, r3
		st r3, -20
		ld %511, r3
		st r3, -10
		ld %-511, r4
		st r4, -50



		and r1, %0, r1

live:	live %1
		zjmp %:live
