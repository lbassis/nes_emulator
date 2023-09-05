#include "cpu.h"

using namespace std;
using std::vector;

uint16_t wraparound_sum(uint16_t x, uint16_t y) { return (x + y > 0xFF) ? y - x : x + y; }
uint16_t wraparound_sum_u16(uint16_t x, uint16_t y) { return (x + y > 0xFFFF) ? y - x : x + y; }

uint16_t cpu::get_operand_address(AdressingMode mode) {

  switch (mode) {
  case Immediate: /* the memory address are the 2 bytes from the program counter */
    return this->pc;
  case ZeroPage: /* the memory address is the byte right after the instruction */
    return mem_read(this->pc);
  case ZeroPage_X: /* adds the content from reg X to the byte right after the instruction */
    return mem_read(wraparound_sum(this->pc, this->reg_x));
  case ZeroPage_Y: /* adds the content from reg Y to the byte right after the instruction */
    return mem_read(wraparound_sum(this->pc, this->reg_y));
  case Absolute: /* like ZeroPage but with 2 bytes */
    return mem_read_u16(this->pc);
  case Absolute_X: /* like ZeroPage_X with 2 bytes */ 
    return mem_read_u16(wraparound_sum_u16(this->pc, this->reg_x));
  case Absolute_Y: /* like ZeroPage_Y with 2 bytes */
    return mem_read_u16(wraparound_sum_u16(this->pc, this->reg_y));
  case Indirect_X: /* sums the given value with reg_x to get the lsb of a 2-byte address to be read */ {
    uint8_t address_location = wraparound_sum(this->pc, this->reg_x);
    uint8_t lsb = mem_read(address_location);
    uint8_t msb = mem_read(wraparound_sum_u16(address_location, 1));
    uint16_t data_location = msb << 8 | (uint16_t) lsb;
    return mem_read_u16(data_location);
  }
  case Indirect_Y: /* reads the lsb of a 2-byte address and add the reg Y to the address it points to */ {
    uint8_t lsb = mem_read(this->pc);
    uint8_t msb = mem_read(wraparound_sum_u16(this->pc, 1));
    uint16_t data_location = msb << 8 | (uint16_t) lsb;
    return mem_read_u16(wraparound_sum_u16(data_location, this->reg_y));
  }
  default:
    return 0;
  }
}


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
