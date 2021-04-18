S%TR: .string "abcd"
DATA: .data 4,6 ,5  ,7
add r3, LIST
MAIN: add r3, LIST
SEC: sub r1, X
jmp r4
mov %DATA,%MAIN
DATA: .data 4,6 ,5 , 7
DATA_E: .data 4,-34 ,5  ,7
STR: .string "abcd"
STR_E: .string "hello"
STR_E2: .data 6 ,5 ,, 7
r2: .data 1,2,3
mov: mov mov,mov
.entry
stop #5
