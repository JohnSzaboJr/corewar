
.name "TEST FORK"
.comment "I'M A TEST FORK"


l2:		sti r1, %:modif, %1
		sti r1, %:l4, %1
l4:		live %01
		ld %851946, r6
		fork %:l3

modif:	live %01      ;lldi	:live, r7, r1
		zjmp %:modif
l3:		st r6, -9
