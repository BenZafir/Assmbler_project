STR: lea r1, %g
   ;
STR: .string "abcd"
DATA: .data 4,6 ,5  ,7
add r3, LIST
MAIN: add r3, LIST
SEC: sub r1, X
DATA: .data 4,6 ,5  7
DATA_E: .data 4,LIST ,5  ,7
STR: .string "abcd"
STR_E: .string abcd
lolo: extern X
toto: entry Y
  label: code v1,v2   
label2: code2 v1_2 , v2_2   