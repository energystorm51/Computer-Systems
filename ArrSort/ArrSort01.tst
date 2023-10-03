// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load ArrSort.asm,
output-file ArrSort01.out,
compare-to ArrSort01.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0]  0,  // Set R0
set RAM[1]  20, // Set R1
set RAM[2]  0,  // Set R2
repeat 100 {
  ticktock;    // Run for 100 clock cycles
}
set RAM[1] 20,  // Restore arguments in case program used them
set RAM[2] 0,
output;        // Output to file

