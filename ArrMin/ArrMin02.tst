// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load ArrMin.asm,
output-file ArrMin02.out,
compare-to ArrMin02.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2 RAM[20]%D2.6.2 RAM[21]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  20, // Set R1
set RAM[2]  2,  // Set R2
set RAM[20] 5,  // Set Arr[0]
set RAM[21] -5,  // Set Arr[1]
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 20,  // Restore arguments in case program used them
set RAM[2] 2,
set RAM[20] 5,
set RAM[21] -5,
output;        // Output to file

