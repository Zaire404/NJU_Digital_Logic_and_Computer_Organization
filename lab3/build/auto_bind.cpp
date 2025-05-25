#include <nvboard.h>
#include "Valu.h"

void nvboard_bind_all_pins(Valu* top) {
	nvboard_bind_pin( &top->a, 4, SW3, SW2, SW1, SW0);
	nvboard_bind_pin( &top->b, 4, SW7, SW6, SW5, SW4);
	nvboard_bind_pin( &top->op, 3, SW15, SW14, SW13);
	nvboard_bind_pin( &top->result, 4, LD3, LD2, LD1, LD0);
	nvboard_bind_pin( &top->cf, 1, LD15);
	nvboard_bind_pin( &top->of, 1, LD14);
	nvboard_bind_pin( &top->zf, 1, LD13);
}
