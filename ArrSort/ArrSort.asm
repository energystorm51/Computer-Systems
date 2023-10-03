// Sorts the array of length R2 whose first element is at RAM[R1] in ascending order in place. Sets R0 to True (-1) when complete.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.
// Implementing insertion sort 

// Base cases: Jump to END if array is empty or has 1 element
@2
D = M // If length = 0, END
@END
D;JEQ
D = D - 1 // If length = 1, END
@END
D;JEQ

// Initialise index i to RAM[1] + 1
@1
D = M
@i 
M = D + 1

// Initialise last index of array
@2
D = M
D = D - 1
@1
D = M + D
@last
M = D

(OUTER)
@i // Load index i onto D-register
D = M
@last // Load last index
D = D - M
@END // Jump to END if index is greater than length of array
D;JGT
@i // Load index i onto D register
D = M 
@j // Calculate inner index
M = D - 1
A = D // Load contents of D-register onto A-register
D = M // Load RAM[A] onto D register
@key
M = D // Store key of current loop

(INNER)
@j
D = M
@1
D = D - M // j - RAM[1]
@STORE
D;JLT // Jump to STORE if j < RAM[1]
@j
A = M
D = M // Load RAM[j] onto D-register
@key
D = D - M // RAM[j] = RAM[j] - key
@STORE
D;JLE // Jump to STORE if RAM[j] <= key
@REPLACE
0;JMP 

// Replace RAM[j + 1] with RAM[j]
(REPLACE)
@j
A = M
D = M // Loads RAM[j] onto D-register
@j
A = M + 1 // Calculate j + 1 and load onto A-register
M = D // Stores RAM[j] into RAM[j + 1]
@j
M = M - 1 // Decrement j to j - 1
@INNER
0;JMP // Return to INNER loop

// Commands RAM[j + 1] = key
(STORE)
@key
D = M // Loads key onto D-register
@j
A = M + 1 // Calculate j + 1 and load onto A-register
M = D // Stores key into RAM[j + 1]
@i
M = M + 1
@OUTER
0;JMP // Return to OUTER loop

(END)
@END
@0
D = A - 1
M = D
0;JMP


