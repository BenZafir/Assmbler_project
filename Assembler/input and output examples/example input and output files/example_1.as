main:	mov 	r1,r2
	mov 	#5,data
	mov 	#10,r7
	cmp 	#80,r2
	cmp 	data,data
label:	cmp 	r1,#500
	add 	r6,r3
	add 	#5,data
	add 	#10,r7
	sub  	r6,r3
	sub  	#5,data
	sub  	#10,r7

    ;

data:	.data 4,5,2,4,1,5,555,0 
string: .string "abc%d- efg"

	lea 	string,r2
	lea 	data,string
	clr 	r3
	clr 	label
	not 	r4
	not 	string
	inc 	r5
	inc 	data
	dec 	r6
	dec 	data
po:	jmp 	sham
sham:	jmp 	%po
	bne 	po
	jsr 	%sham
	red 	r7
	red 	main
	prn 	#5
	prn 	main
	prn 	r1
	rts 	
	stop
