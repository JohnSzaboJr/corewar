
.name "roukiloop"
.comment "prepare the pomade"

first:		sti r1, %100, %1
            sti r1, %:ok

ok:         live %36346
            st  r1, 40
            zjmp %:first
fork1:
	live	%4
	fork	%:fork2
	ld 		%0, r16

fork2:
	live	%4
	zjmp	%:fork1
