// Follows the Test Scripting Language format described in 
// Appendix B of the book "The Elements of Computing Systems"

load Mult.asm,
output-file Mult05.out,
compare-to Mult05.cmp,
output-list RAM[0]%D2.6.2 RAM[1]%D2.6.2 RAM[2]%D2.6.2;

set PC 0,
set RAM[0] 0,  // Set R0
set RAM[1] 72,  // Set R1
set RAM[2] -27;  // Set R2
repeat 450 {
  ticktock;    // Run for 450 clock cycles
}
set RAM[1] 72,  // Restore arguments in case program used them
set RAM[2] -27,
set RAM[16] 0,
set RAM[17] 0,
set RAM[18] 0,
output;        // Output to file

