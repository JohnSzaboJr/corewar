.name   ";ignore this! 
zo

rk"


.comment "
I'M ALIIIIVE"

l2:		ldi %1, %:live, r1
		and 1, 4984, r1

live:	live %1
		zjmp %:live
