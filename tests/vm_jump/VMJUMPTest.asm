// push constant 20 onto the stack
@20
D = A 
@SP
AM = M + 1
A = A - 1
M = D

// vm_if
@SP       
AM = M - 1
D = M     
@LOOP
D;JNE

(LOOP)
@55
M = 1
@END
0;JMP

(END)
@END
0;JMP