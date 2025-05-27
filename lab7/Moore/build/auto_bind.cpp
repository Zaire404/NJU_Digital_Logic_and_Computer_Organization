#include <nvboard.h>
#include "VFSM_bin.h"

void nvboard_bind_all_pins(VFSM_bin* top) {
	nvboard_bind_pin( &top->in, 1, SW1);
	nvboard_bind_pin( &top->clk, 1, BTNC);
	nvboard_bind_pin( &top->out, 1, LD0);
	nvboard_bind_pin( &top->reset, 1, SW0);
	nvboard_bind_pin( &top->state_dout, 4, LD7, LD6, LD5, LD4);
}
