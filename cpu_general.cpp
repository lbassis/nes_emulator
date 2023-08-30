#include "cpu.h"

using namespace std;
using std::vector;

void cpu::reset() {
  accumulator = 0;
  reg_x = 0;
  status = 0;
  pc = mem_read_u16(PC_INITIAL_VALUE_ADDRESS);
}

void cpu::load(vector<uint8_t> program) {
  uint16_t program_offset = PC_INITIAL_VALUE;
  mem_write_u16(PC_INITIAL_VALUE_ADDRESS, PC_INITIAL_VALUE);

  for (int i = 0; i < program.size(); i++) {
    memory[program_offset + i] = program[i];
  }
}

void cpu::run() {
    
  while (true) {
    auto opcode = mem_read(pc);
    pc++;

    switch (opcode) {
    case 0x00:
      return;

    case 0xA9: { /* LDA */
      auto param = mem_read(pc);
      pc++;

      accumulator = param;

      update_zero_and_negative(accumulator);
      break;
    }

    case 0xAA: { /* TAX */	
      reg_x = accumulator;

      update_zero_and_negative(reg_x);
      break;
    }

    case 0xE8: { /* INX */
      reg_x++;

      update_zero_and_negative(reg_x);
      break;
    }
    }
  }
}

void cpu::load_and_run(vector<uint8_t> program) {
  load(program);
  reset();
  run();
}
