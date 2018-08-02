.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and %1, %1, r1

live:
