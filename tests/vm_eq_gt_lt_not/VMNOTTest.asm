// push constant 20 onto the stack
@20
D = A 
@SP
AM = M + 1
A = A - 1
M = D

// pop a value off the stack and store in RAM[16]
@SP
A = M - 1
D = M
D = !D
M = D

(END)
@END
0;JMP