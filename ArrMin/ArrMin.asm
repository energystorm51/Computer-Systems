// Finds the smallest element in the array of length R2 whose first element is at RAM[R1] and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// Read length of array
@2
D = M

// Jump to END if R2 (counter) <= 0
@END
D;JLE

// Otherwise, set R0 to first element of array at RAM[R1]
@1
D = M
A = D // Store 20 into A-register
D = M // Store RAM[20] into D-register
@0
M = D // Store RAM[20] into RAM[0] 

// Initialise counter
@counter
M = 1

// Read array in a LOOP
@LOOP 
0;JMP // Jump to LOOP

(LOOP)
// If counter == R2, jump to END
@2
D = M
@counter
D = D - M
@END
D;JEQ

// Increament counter
@counter
D = M
D = D + 1
M = D

// Increment R1
@1
D = M
D = D + 1
M = D // R1 = R1 + 1

// Read RAM[R1+1]
D = M
A = D
D = M

//If RAM[R0] > RAM[R1+1], replace RAM[R0] with RAM[R1+1]
@0
D = D - M // RAM[R1+1] - RAM[R0]
@MIN
D;JLT
@LOOP
0;JMP

(MIN)
@1
D = M
A = D
D = M
@0
M = D
@LOOP
0;JMP

(END)
@END
0;JMP