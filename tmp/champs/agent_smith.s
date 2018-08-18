.name "Agent Smith"
.comment "Surprised to see me Mr. Anderson?"

reloaded:	  sti r1, %:oracle, %1
	    ldi %:oracle, %0, r2
	    ldi %:oracle, %4, r3
	    ldi %:oracle, %8, r4
	    ldi %:oracle, %12, r5
	    ldi %:oracle, %16, r6
	    ldi %:oracle, %20, r7
	    ldi %:oracle, %24, r8
	    ldi %:oracle, %28, r9
	    ldi %:oracle, %32, r10
revolutions:
	    st r2, 512
	    st r3, 511
	    st r4, 510
	    st r5, 509
	    st r6, 508
	    st r7, 507
	    st r8, 506
	    st r9, 505
	    st r10, 504
morpheus:	 fork %:reloaded
	    zjmp %:oracle
cypher:	 sti r1, %:oracle, %1
	    ldi %:oracle, %0, r2
	    ldi %:oracle, %4, r3
	    ldi %:oracle, %8, r4
	    ldi %:oracle, %12, r5
oracle:	 live  %42
	    st r2, 512
	    st r3, 511
	    st r4, 510
	    st r5, 509
	    st r6, 508
	    st r7, 507
	    st r8, 506
	    st r9, 505
	    st r10, 504
