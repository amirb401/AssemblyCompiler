.entry LIST
.extern W
MAIN: add r3, LIST
LOOP: prn #48
;lea STR, r6
inc r6
mov r3, W
sub r1, r4
bne END
cmp val1, #-6
bne END[7]
dec K
.entry MAIN
sub LOOP[4] ,r6
;END: stop
STR: .string “abcd”
LIST: .data 6
.data -100
;.entry K
;K: .data 31
.extern val1
