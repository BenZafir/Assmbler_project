; file ps.as
.entry LIST
.extern W
MAIN: add r3, LIST
LOOP: prn #48
 lea W, r6
 inc r6
 mov r3, K
 sub r1, r4
 bne END
 cmp K, #-6
 bne %END
 dec W
.entry MAIN
 jmp %LOOP
 add L3, L3
END: stop
STR: .string "abcd"
LIST: .data 60000, -9
LIST2: .data 63456456, -9
LIST3: .data 2048, -9
LIST4: .data -2048, -9
LIST5: .data -2049, -9
LIST6: .data -23434, -9
 .data -100
K: .data 31
.extern L3 
