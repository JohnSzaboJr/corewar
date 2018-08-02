.name "LLDI DAUBE"
.comment "I'M LLDI"


l2:		;lldi	1401, %0, r3	; fffe = 65534 + 1365 = 66899 % 4096 = 1363 = a8a90ee4 = -2
		;sti r3, %-100, %0    ; 1396 e4057400
		lldi	-20, %0, r1
		sti r1, %200, %0
		lldi	-10, %0, r1
		sti r1, %225, %0
		lldi 0, %0, r1  	;ok
		sti r1, %150, %0
		lldi	2, %1, r1 ;ok
		sti r1, %300, %0
		lldi	:live, r1, r4
		;sti r4, %0, %0
		lldi	%:live, %1, r5
		sti r5, %200, %0
		lldi	%2, %3, r6;
		sti r6, %250, %0
		and r1, %0, r1

live:	live %13421772
		zjmp %:live
