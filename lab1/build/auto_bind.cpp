#include <nvboard.h>
#include "Vmux41.h"

void nvboard_bind_all_pins(Vmux41* top) {
	nvboard_bind_pin( &top->y, 2, SW1, SW0);
	nvboard_bind_pin( &top->x[0], 2, SW3, SW2);
	nvboard_bind_pin( &top->x[1], 2, SW5, SW4);
	nvboard_bind_pin( &top->x[2], 2, SW7, SW6);
	nvboard_bind_pin( &top->x[3], 2, SW9, SW8);
	nvboard_bind_pin( &top->f, 2, LD1, LD0);
}
