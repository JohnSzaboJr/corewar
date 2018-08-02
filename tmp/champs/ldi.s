.name "LDI"
.comment "I'M LDI"


l2:		ldi	1401, %2, r2
		sti r2, %-200, %0
		ldi	-20, %-2, r2
		sti r2, %-200, %0
		ldi	-10, %2, r2
		sti r2, %-200, %0
		ldi 0, %-2, r2
		sti r2, %-200, %0
		ldi	%2, %1, r2 ;ok
		sti r2, %-200, %0
		ldi	:live, r2, r2
		sti r2, %-200, %0
		ldi	%:live, %1, r2
		sti r2, %-200, %0
		ldi	%2, %3, r2;
		sti r2, %-200, %0
		ldi	r1, %3, r2;
		sti r2, %-200, %0

		ldi	-20, %0, r2
		sti r2, %-500, %0
		ldi	-10, %0, r2
		sti r2, %-500, %0
		ldi 0, %0, r2
		sti r2, %-500, %0
		ldi	2, %1, r2 ;ok
		sti r2, %-500, %0
		ldi	:live, r2, r2
		sti r2, %-500, %0
		ldi	%:live, %1, r2
		sti r2, %-500, %0
		ldi	%2, %3, r2;
		sti r2, %-500, %0
		and r1, %0, r1


		ldi	1401, %0, r2
		sti r2, %-200, %0
		ldi	%2, %3, r2
		sti r2, %200, %0
		ldi	:live, r2, r2
		sti r2, %200, %0
		ldi	%:live, %1, r2
		sti r2, %200, %0
		and r1, %0, r1

		ldi	-511, %3000, r2
		sti r2, %200, %0
		ldi	2, %2, r2
		sti r2, %200, %0
		ldi	:live, r2, r2
		sti r2, %200, %0
		ldi	%:live, %1, r2
		sti r2, %200, %0
		ldi	%2, %3, r2
		sti r2, %200, %0
		and r1, %0, r1

live:	live %13421772
		zjmp %:live
