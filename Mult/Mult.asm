// This file is based on part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: Mult.asm

// Multiplies R1 and R2 and stores the result in R0.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

// To implement a multiplication function,
// we can iteratively add R1 to R0 for R2 number of times
// E.g. for R1 = 2 and R2 = 3, 
// We add 2 to the sum variable for 3 times to obtain 6.

// Compare R1 and R2
@1
D = M
@2
D = D - M
@SWAP // If R2 is greater than R1, swap their values
D;JLT
@MAIN
0;JMP

(SWAP)
@1
D = M
@temp
M = D // temp = R1
@2
D = M
@1
M = D // R1 = R2
@temp
D = M
@2
M = D // R2 = temp = R1
@MAIN
0;JMP

(MAIN)
@2
D = M
@counter
M = D
@FLIP // If R2 is negative, flip the counter value
D;JLT
@LOOP
D;JGE // If R2 is positive, loop into school multiplication
@END
D;JEQ // If R2 is zero, exit function

(FLIP)
D = -D
@counter
M = D
@signR2
M = 1
@LOOP
0;JMP

(LOOP)
// If counter == 0, exit loop
@counter
D = M
@CHECKR2
D;JEQ

// Decrement counter by 1
D = D - 1
@counter
M = D

// Add R1 into R0
@1
D = M
@0
D = D + M
M = D

// Jump back to LOOP
@LOOP
0;JMP

// If R2 is negative, negate the sum in R0
(CHECKR2)
@signR2
D = M
@END
D;JEQ
@0
M = -M
@END
0;JMP

// End of Mult function
(END)
@END
0;JMP