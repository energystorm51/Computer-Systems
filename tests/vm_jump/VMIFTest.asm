//Pop a value from the stack. If that value is not FALSE (not 0), jump to the location marked by the provided label.

// pop top value off stack
@SP
AM = M - 1
D = M       // D-register stores top value

// jump to END if D = FALSE (0)
@END
D;JEQ
 
// otherwise jump to label
@label
0;JMP

(END)
@END
0;JMP