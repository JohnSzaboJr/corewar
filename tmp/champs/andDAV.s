.name "and_chp"
.comment "AND TEST MOTHER FUCKER"

adopi:	ld		%4294901760, r1
		ld 		%65535, r2
		ld 		%16776960, r3
		ld 		%4278190335, r4


		and		0,		r1, r5
		st		r5, -10
		and		511, 	1, r5
		st		r5, -10
		and		-511, 	%16776960,	 r5
		st		r5, -10
		and		1,		r1, r5
		st		r5, -10

		and		%4278190335, %16776960, r5
		st		r5, -10
    	and		%4278190335, -1,  r5
		st		r5, -10
    	and		%4278190335, r1  , r5
		st		r5, -10
    	and		%4278190335, r1 , r5
		st		r5, -10

    	and		r1, r3, r5
		st		r5, -250
    	and		r2, r3, r5
		st		r5, -250
    	and		r1, r4, r5
		st		r5, -250
    	and		r1, r2, r5
		st		r5, -250

		and		r1, 0 , r5
		st		r5, -250
		and		r2, 511 , r5
		st		r5, -250
		and		r1, -511 , r5
		st		r5, -250
		and		r1, 1, r5
		st		r5, -250

		and		r1, %16776960 , r5
		st		r5, -250
    	and		r2, %16776960 , r5
		st		r5, -250
    	and		r1, %4278190335 , r5
		st		r5, -250
    	and		r1, %4278190335, r5
		st		r5, -250

    	and		r1, r3, r5
		st		r5, -250
    	and		r2, r3, r5
		st		r5, -250
    	and		r1, r4, r5
		st		r5, -250
    	and		r1, r2, r5
		st		r5, -250
adopipi:ld		2049, r1
    	and		r1, r1, r1
    	and		r1, r1, r1
    	and		r1, r2, r3

adocaca:ld		4095, r1
    	and		r1, r1, r1
    	and		r1, r1, r1
    	and		r1, r1, r3
