#include <VFSM_bin.h>
#include <nvboard.h>

static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* top);

int main() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();

  while (1) {
    dut.eval();
    nvboard_update();
  }
}
