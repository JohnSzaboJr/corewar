.name "LLDI"
.comment "I'M LLDI"


l2:		lldi	-511, %3000, r1   ; fffe = 65534 + 1365 = 66899 % 4096 = 1363 = a8a90ee4 = -2
		;st r1, -5
		;st r1, -250
		sti r1, %-5, %0
		sti r1, %-250, %0

		lldi	2, %2, r1; KO
		;st r1, -5
		;st r1, -250
		sti r1, %-5, %0
		sti r1, %-250, %0

		lldi	:live, r7, r1
		;st r1, -5
		;st r1, -250
		sti r1, %-5, %0
		sti r1, %-250, %0

		lldi	%:live, %1, r1
		;st r1, -5
		;st r1, -250
		sti r1, %-5, %0
		sti r1, %-250, %0

		lldi	%2, %3, r1;
		;st r1, -5
		;st r1, -250
		sti r1, %-5, %0
		sti r1, %-250, %0

		and r1, %0, r1

live:	live %13421772
		zjmp %:live





		;live %196868
