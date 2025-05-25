#include <nvboard.h>
#include "Vlfsr.h"

void nvboard_bind_all_pins(Vlfsr* top) {
	nvboard_bind_pin( &top->clk, 1, BTNC);
	nvboard_bind_pin( &top->reset, 1, BTNL);
	nvboard_bind_pin( &top->out, 8, LD7, LD6, LD5, LD4, LD3, LD2, LD1, LD0);
}
