.name "LLDI FOIREUX"
.comment "I'M LLDI"


l2:		lldi	1401, %0, r3   ; fffe = 65534 + 1365 = 66899 % 4096 = 1363 = a8a90ee4
		sti r3, %100, %0    ; 1396 e4057400
		lldi	%2, %3, r2;3020ed4
		sti r2, %150, %0
		lldi	:live, r1, r4
		sti r4, %0, %0
		lldi	%:live, %1, r5
		sti r5, %200, %0
		and r1, %0, r1

live:	live %13421772
		zjmp %:live
