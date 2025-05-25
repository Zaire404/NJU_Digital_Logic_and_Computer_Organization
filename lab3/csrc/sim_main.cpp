// #include "Valu.h"
// #include "verilated.h"
// #include "verilated_vcd_c.h"

// VerilatedContext* contextp = NULL;
// VerilatedVcdC* tfp = NULL;

// static Valu* top;

// void step_and_dump_wave() {
//   top->eval();
//   contextp->timeInc(1);
//   tfp->dump(contextp->time());
// }
// void sim_init() {
//   contextp = new VerilatedContext;
//   tfp = new VerilatedVcdC;
//   top = new Valu;
//   contextp->traceEverOn(true);
//   top->trace(tfp, 0);
//   tfp->open("dump.vcd");
// }

// void sim_exit() {
//   step_and_dump_wave();
//   tfp->close();
// }

// // Helper function to convert a 4-bit unsigned char to its signed integer
// // representation
// int to_signed_4bit(unsigned char val4bit) {
//   // Mask to ensure it's only 4 bits, though Verilator handles port widths
//   val4bit &= 0x0F;
//   if (val4bit & 0x08) {  // If sign bit (MSB of 4 bits, which is bit 3) is
//   set
//     // Convert to signed int (e.g., 0xF -> -1, 0x8 -> -8)
//     return static_cast<int>(val4bit) - 16;
//   } else {
//     return static_cast<int>(val4bit);
//   }
// }

// // Function to run a single test case
// void run_test(unsigned char a_val, unsigned char b_val, unsigned char op_val,
//               const std::string& test_name) {
//   top->a = a_val;
//   top->b = b_val;
//   top->op = op_val;

//   step_and_dump_wave();

//   // Print inputs and results, showing both hex and interpreted signed
//   decimal
//   // values
//   printf(
//       "Test: %-30s | A=0x%x (%2d), B=0x%x (%2d), OP=0x%x | Result=0x%x (%2d),
//       " "CF=%d, ZF=%d, OF=%d\n", test_name.c_str(), a_val,
//       to_signed_4bit(a_val), b_val, to_signed_4bit(b_val), op_val,
//       top->result, to_signed_4bit(top->result), top->cf, top->zf, top->of);
// }

// int main(int argc, char** argv) {
//   // Initialize Verilators variables
//   Verilated::commandArgs(argc, argv);
//   sim_init();

//   printf("Starting ALU Simulation...\n");
//   // Note on 4-bit signed numbers: Range is -8 to +7.
//   // Hex: 0x0=0, 0x1=1, ..., 0x7=7
//   // Hex: 0x8=-8, 0x9=-7, ..., 0xE=-2, 0xF=-1

//   // --- Addition Tests (op=0x0) ---
//   printf("\n--- Addition (op=0x0) ---\n");
//   run_test(0x0, 0x0, 0x0, "0 + 0");  // Expected: R=0x0 (0), CF=0, ZF=1, OF=0
//   run_test(0x1, 0x2, 0x0, "1 + 2");  // Expected: R=0x3 (3), CF=0, ZF=0, OF=0
//   run_test(0x5, 0x2, 0x0, "5 + 2");  // Expected: R=0x7 (7), CF=0, ZF=0, OF=0
//   run_test(0x5, 0x5, 0x0,
//            "5 + 5 (Overflow)");  // Expected: R=0xA (-6), CF=0, ZF=0, OF=1
//   run_test(0xF, 0x1, 0x0, "(-1) + 1");  // Expected: R=0x0 (0), CF=1, ZF=1,
//   OF=0 run_test(0xE, 0xD, 0x0,
//            "(-2) + (-3)");  // Expected: R=0xB (-5), CF=1, ZF=0, OF=0
//   run_test(0xB, 0xB, 0x0,
//            "(-5) + (-5) (Overflow)");  // Expected: R=0x6 (6), CF=1, ZF=0,
//            OF=1
//   run_test(0x7, 0x1, 0x0,
//            "7 + 1 (Overflow)");  // Expected: R=0x8 (-8), CF=0, ZF=0, OF=1
//   run_test(0x9, 0xE, 0x0,
//            "(-7) + (-2) (Overflow)");  // Expected: R=0x7 (7), CF=1, ZF=0,
//            OF=1

//   // --- Subtraction Tests (op=0x1) ---
//   // For your ALU's subtraction A-B (as A + ~B + 1):
//   // CF=1 means (A + ~B + 1) had a carry-out, which implies No Borrow was
//   needed
//   // for A-B. CF=0 means (A + ~B + 1) had no carry-out, which implies a
//   Borrow
//   // was needed for A-B.
//   printf("\n--- Subtraction (op=0x1) ---\n");
//   run_test(0x0, 0x0, 0x1, "0 - 0");  // Expected: R=0x0 (0), CF=1, ZF=1, OF=0
//   run_test(0x5, 0x2, 0x1, "5 - 2");  // Expected: R=0x3 (3), CF=1, ZF=0, OF=0
//   run_test(0x2, 0x5, 0x1, "2 - 5");  // Expected: R=0xD (-3), CF=0, ZF=0,
//   OF=0 run_test(0xF, 0x1, 0x1,
//            "(-1) - 1");  // Expected: R=0xE (-2), CF=0, ZF=0, OF=0
//   run_test(0x1, 0xF, 0x1, "1 - (-1)");  // Expected: R=0x2 (2), CF=1, ZF=0,
//   OF=0 run_test(
//       0x5, 0xB, 0x1,
//       "5 - (-5) (Overflow)");  // 5-(0xB) = 0101 + ~(1011) + 1 = 0101+0100+1
//       =
//                                // 1010. Exp: R=0xA (-6), CF=0, ZF=0, OF=1
//   run_test(
//       0xB, 0x5, 0x1,
//       "(-5) - 5 (Overflow)");  // (0xB)-5 = 1011 + ~(0101) + 1 = 1011+1010+1
//       =
//                                // 10110. Exp: R=0x6 (6), CF=1, ZF=0, OF=1
//   run_test(
//       0x7, 0x9, 0x1,
//       "7 - (-7) (Overflow)");  // 7-(0x9) = 0111 + ~(1001) + 1 = 0111+0110+1
//       =
//                                // 1110. Exp: R=0xE (-2), CF=0, ZF=0, OF=1
//   run_test(
//       0x8, 0x1, 0x1,
//       "(-8) - 1 (Overflow)");  // (0x8)-1 = 1000 + ~(0001) + 1 = 1000+1110+1
//       =
//                                // 10111. Exp: R=0x7 (7), CF=1, ZF=0, OF=1

//   // --- NOT A Tests (op=0x2) ---
//   printf("\n--- NOT A (op=0x2) ---\n");
//   run_test(0x0, 0x0, 0x2, "NOT 0x0");  // Expected: R=0xF (-1), CF=0, ZF=0,
//   OF=0 run_test(0xF, 0x0, 0x2,
//            "NOT 0xF (-1)");  // Expected: R=0x0 (0), CF=0, ZF=1, OF=0
//   run_test(0x5, 0x0, 0x2,
//            "NOT 0x5 (5)");  // Expected: R=0xA (-6), CF=0, ZF=0, OF=0
//   run_test(0xA, 0x0, 0x2,
//            "NOT 0xA (-6)");  // Expected: R=0x5 (5), CF=0, ZF=0, OF=0

//   // --- AND Tests (op=0x3) ---
//   printf("\n--- AND (op=0x3) ---\n");
//   run_test(0x0, 0xF, 0x3,
//            "0x0 AND 0xF");  // Expected: R=0x0 (0), CF=0, ZF=1, OF=0
//   run_test(0xF, 0x1, 0x3,
//            "0xF AND 0x1");  // Expected: R=0x1 (1), CF=0, ZF=0, OF=0
//   run_test(
//       0xA, 0x5, 0x3,
//       "0xA AND 0x5");  // 1010 & 0101 = 0000. Exp: R=0x0 (0), CF=0, ZF=1,
//       OF=0
//   run_test(
//       0xC, 0x6, 0x3,
//       "0xC AND 0x6");  // 1100 & 0110 = 0100. Exp: R=0x4 (4), CF=0, ZF=0,
//       OF=0

//   // --- OR Tests (op=0x4) ---
//   printf("\n--- OR (op=0x4) ---\n");
//   run_test(0x0, 0x0, 0x4,
//            "0x0 OR 0x0");  // Expected: R=0x0 (0), CF=0, ZF=1, OF=0
//   run_test(0x1, 0x2, 0x4,
//            "0x1 OR 0x2");  // Expected: R=0x3 (3), CF=0, ZF=0, OF=0
//   run_test(
//       0xA, 0x5, 0x4,
//       "0xA OR 0x5");  // 1010 | 0101 = 1111. Exp: R=0xF (-1), CF=0, ZF=0,
//       OF=0
//   run_test(
//       0xC, 0x3, 0x4,
//       "0xC OR 0x3");  // 1100 | 0011 = 1111. Exp: R=0xF (-1), CF=0, ZF=0,
//       OF=0

//   // --- XOR Tests (op=0x5) ---
//   printf("\n--- XOR (op=0x5) ---\n");
//   run_test(0x0, 0x0, 0x5,
//            "0x0 XOR 0x0");  // Expected: R=0x0 (0), CF=0, ZF=1, OF=0
//   run_test(0xF, 0xF, 0x5,
//            "0xF XOR 0xF");  // Expected: R=0x0 (0), CF=0, ZF=1, OF=0
//   run_test(
//       0xA, 0x5, 0x5,
//       "0xA XOR 0x5");  // 1010 ^ 0101 = 1111. Exp: R=0xF (-1), CF=0, ZF=0,
//       OF=0
//   run_test(
//       0xC, 0x6, 0x5,
//       "0xC XOR 0x6");  // 1100 ^ 0110 = 1010. Exp: R=0xA (-6), CF=0, ZF=0,
//       OF=0

//   // --- Less Than Tests (op=0x6) ---
//   printf("\n--- Less Than (op=0x6) ---\n");
//   run_test(0x1, 0x2, 0x6, "A<B: 0x1 (1) < 0x2 (2)");
//   // Expected for true signed A < B: Result=1. Your Verilog op=0x6 output
//   will
//   // be 1. ZF=0. CF,OF from A-B.

//   // Test case 2: A=5 (0x5), B=2 (0x2). Signed: 5 < 2 is FALSE.
//   run_test(0x5, 0x2, 0x6, "A<B: 0x5 (5) < 0x2 (2)");
//   // Expected for true signed A < B: Result=0. Your Verilog op=0x6 output
//   will
//   // be 1. ZF=0. CF,OF from A-B. (Mismatch Highlighted)

//   // Test case 3: A=-1 (0xF), B=1 (0x1). Signed: -1 < 1 is TRUE.

//   run_test(0xF, 0x1, 0x6, "A<B: 0xF (-1) < 0x1 (1)");
//   // Expected for true signed A < B: Result=1. Your Verilog op=0x6 output
//   will
//   // be 1. ZF=0. CF,OF from A-B.

//   run_test(0x1, 0xF, 0x6, "A<B: 0x1 (1) < 0xF (-1)");
//   // Expected for true signed A < B: Result=0. Your Verilog op=0x6 output
//   will
//   // be 1. ZF=0. CF,OF from A-B. (Mismatch Highlighted)

//   run_test(0x8, 0x1, 0x6, "A<B: 0x8 (-8) < 0x1 (1)");
//   // Expected for true signed A < B: Result=1 (N=0,V=1 => N^V=1). Your
//   Verilog
//   // op=0x6 output will be 1. ZF=0. CF,OF from A-B.

//   run_test(0x7, 0x8, 0x6, "A<B: 0x7 (7) < 0x8 (-8)");
//   // Expected for true signed A < B: Result=0 (N=1,V=1 => N^V=0). Your
//   Verilog
//   // op=0x6 output will be 1. ZF=0. CF,OF from A-B. (Mismatch Highlighted)

//   run_test(0x2, 0x2, 0x6, "A<B: 0x2 (2) < 0x2 (2)");
//   // Expected for true signed A < B: Result=0. Your Verilog op=0x6 output
//   will
//   // be 0. ZF=1. CF,OF from A-B.

//   run_test(0xF, 0xF, 0x6, "A<B: 0xF (-1) < 0xF (-1)");
//   // Expected for true signed A < B: Result=0. Your Verilog op=0x6 output
//   will
//   // be 0. ZF=1. CF,OF from A-B.

//   run_test(0x7, 0x8, 0x6, "A<B: 0x7 (7) < 0x8 (-8) Rep");
//   // Expected for true signed A < B: Result=0. Your Verilog op=0x6 output
//   will
//   // be 1. ZF=0. (Mismatch)

//   run_test(0x8, 0x7, 0x6, "A<B: 0x8 (-8) < 0x7 (7)");
//   // Expected for true signed A < B: Result=1. Your Verilog op=0x6 output
//   will
//   // be 1. ZF=0.

//   // --- Equal Tests (op=0x7) ---
//   printf("\n--- Equal (op=0x7) ---\n");
//   run_test(0x5, 0x5, 0x7,
//            "0x5 == 0x5");  // Expected: R=0x1 (1), ZF=0 (result is 1)
//   run_test(0x5, 0x3, 0x7,
//            "0x5 == 0x3");  // Expected: R=0x0 (0), ZF=1 (result is 0)
//   run_test(0xF, 0xF, 0x7, "0xF == 0xF");  // Expected: R=0x1 (1), ZF=0
//   run_test(0x0, 0x0, 0x7, "0x0 == 0x0");  // Expected: R=0x1 (1), ZF=0

//   printf("\nSimulation Finished. Check dump.vcd for waveforms.\n");
//   sim_exit();  // Clean up
//   return 0;
// }