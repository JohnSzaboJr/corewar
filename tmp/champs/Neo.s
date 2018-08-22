.name "Neo"
.comment "I'm the chosen one"

prelude:	    zjmp %0
start:	      fork %:live
oracle:	     ldi %:oracle, %7, r16
	            st r1, 6
	            live %42
	            st r16, 437
	            ldi %:trap, %0, r10
	            sti r10, %:prelude, %-192
	            sti r10, %:prelude, %-176
	            sti r10, %:prelude, %-160
	            sti r10, %:prelude, %-144
	            sti r10, %:prelude, %-128
	            sti r10, %:prelude, %-112
	            sti r10, %:prelude, %-96
	            sti r10, %:prelude, %-80
	            sti r10, %:prelude, %-64
	            sti r10, %:prelude, %-48
	            sti r10, %:prelude, %-32
	            sti r10, %:prelude, %-16
	            st r1, 6
	            live %42
	            fork %:morpheus
	            st r1, 6
	            live %42
	            fork %:oracle
	            add r2, r3, r4
	            zjmp %400

live:	       ldi %:oracle, %11, r16
	            st r1, 6
	            live %42
	            st r16, 294
	            ldi %:trap, %5, r10
	            sti r10, %:prelude, %-188
	            sti r10, %:prelude, %-172
	            sti r10, %:prelude, %-156
	            sti r10, %:prelude, %-140
	            sti r10, %:prelude, %-124
	            sti r10, %:prelude, %-108
	            sti r10, %:prelude, %-92
	            sti r10, %:prelude, %-76
	            sti r10, %:prelude, %-60
	            sti r10, %:prelude, %-44
	            sti r10, %:prelude, %-28
	            sti r10, %:prelude, %-12
	            st r1, 6
	            live %42
	            fork %:trinity
	            st r1, 6
	            live %42
	            fork %:live
	            add r2, r3, r4
	            zjmp %250
morpheus:	   zjmp %0
	            ldi %:oracle, %15, r16
	            st r1, 6
	            live %42
	            st r16, 148
	            fork %:oracle
	            st r1, 6
	            live %42
	            add r2, r3, r4
	            zjmp %256
trinity:	    zjmp %0
	            ldi %:oracle, %19, r16
	            st r1, 6
	            live %42
	            st r16, 106
	            fork %:live
	            st r1, 6
	            live %42
	            add r2, r3, r4
	            zjmp %256
trap:	       add r2, r3, r4
	            zjmp %0
