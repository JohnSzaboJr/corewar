.name "ld_chp"
.comment "LD TEST MOTHER FUCKER"

audi: 	ld		256, r2
		sti r2, %-250, %0

    	ld		-256, r2
		sti r2, %-250, %0

        ld      1, r2
		sti r2, %-250, %0

        ld      -1, r2
		sti r2, %-250, %0

        ld      512, r2
		sti r2, %-250, %0

        ld      -512, r2
		sti r2, %-250, %0

    	ld		%1, r2
		sti r2, %-250, %0

    	ld		%-1, r2
		sti r2, %-250, %0

    	ld		%512, r2
		sti r2, %-250, %0

	    ld		%-512, r2
		sti r2, %-250, %0

    	ld		%-12, r2
		sti r2, %-250, %0

    	ld		901, r2
		sti r2, %-250, %0

    	ld		2049, r28
		sti r2, %-250, %0

    	ld		-4, r2
		sti r2, %-250, %0

    	ld		2047, r2
		sti r2, %-250, %0

    	ld		-4, r2
		sti r2, %-250, %0

    	ld		2046, r2
		sti r2, %-250, %0

    	ld		-4, r2
		sti r2, %-250, %0

    	ld		513, r2
		sti r2, %-250, %0

    	ld		-4, r2
		sti r2, %-250, %0

    	ld		512, r2
		sti r2, %-250, %0

    	ld		-0, r2
		sti r2, %-250, %0

    	ld		-4, r2
		sti r2, %-250, %0

    	ld		2048, r2
		sti r2, %-250, %0

    	ld		2048, r2
		sti r2, %-250, %0
