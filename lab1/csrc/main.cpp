#include <Vmux41.h>
#include <nvboard.h>
#include <verilated.h>
#include <verilated_vcd_c.h>

static TOP_NAME dut;

void nvboard_bind_all_pins(TOP_NAME* top);

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vmux41* top;

void step_and_dump_wave() {
  top->eval();
  contextp->timeInc(1);
  tfp->dump(contextp->time());
}
void sim_init() {
  contextp = new VerilatedContext;
  tfp = new VerilatedVcdC;
  top = new Vmux41;
  contextp->traceEverOn(true);
  top->trace(tfp, 0);
  tfp->open("dump.vcd");
}

void sim_exit() {
  step_and_dump_wave();
  tfp->close();
}

void sim_test() {
  sim_init();

  top->y = 0;
  top->x[0] = 0;
  top->x[1] = 0;
  top->x[2] = 0;
  top->x[3] = 0;
  step_and_dump_wave();
  top->x[0] = 1;
  step_and_dump_wave();
  top->x[0] = 2;
  step_and_dump_wave();
  top->x[0] = 3;
  step_and_dump_wave();

  top->y = 1;
  top->x[0] = 0;
  top->x[1] = 0;
  top->x[2] = 0;
  top->x[3] = 0;
  step_and_dump_wave();
  top->x[1] = 1;
  step_and_dump_wave();
  top->x[1] = 2;
  step_and_dump_wave();
  top->x[1] = 3;
  step_and_dump_wave();

  top->y = 2;
  top->x[0] = 0;
  top->x[1] = 0;
  top->x[2] = 0;
  top->x[3] = 0;
  step_and_dump_wave();
  top->x[2] = 1;
  step_and_dump_wave();
  top->x[2] = 2;
  step_and_dump_wave();
  top->x[2] = 3;
  step_and_dump_wave();

  top->y = 3;
  top->x[0] = 0;
  top->x[1] = 0;
  top->x[2] = 0;
  top->x[3] = 0;
  step_and_dump_wave();
  top->x[3] = 1;
  step_and_dump_wave();
  top->x[3] = 2;
  step_and_dump_wave();
  top->x[3] = 3;
  step_and_dump_wave();

  sim_exit();
}

void nvboard_test() {
  nvboard_bind_all_pins(&dut);
  nvboard_init();

  while (1) {
    dut.eval();
    nvboard_update();
  }
}

int main() {
  sim_test();
  nvboard_test();
}
