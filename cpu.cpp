#include "cpu.h"

using namespace std;
using std::vector;

void cpu::set_zero_flag(bool flag) {
  flag ? this->status |= STATUS_ZERO : this->status &= STATUS_N_ZERO;
}

void cpu::set_negative_flag(bool flag) {
  flag ? this->status |= STATUS_NEGATIVE : this->status &= STATUS_N_NEGATIVE;
}

void cpu::update_zero_and_negative(uint8_t val) {
  (val == 0) ? set_zero_flag(true) : set_zero_flag(false);
  (val & STATUS_NEGATIVE) ? set_negative_flag(true) : set_negative_flag(false);
}

uint8_t cpu::mem_read(uint16_t address) { return memory[address]; }
void cpu::mem_write(uint16_t address, uint8_t data) { memory[address] = data; }
  
cpu::cpu() : accumulator(0), status(0), pc(PC_INITIAL_VALUE) {}
void cpu::print_status() { cout << bitset<8>(this->status) << endl; }
uint8_t cpu::get_acc() { return this->accumulator; }
uint8_t cpu::get_reg_x() { return this->reg_x; }

uint8_t cpu::get_status() { return this->status; }
bool cpu::get_zero() { return (this->get_status() & STATUS_ZERO); }
bool cpu::get_negative() { return (this->get_status() & STATUS_NEGATIVE); }

void cpu::set_acc(uint8_t val) { this->accumulator = val; }
void cpu::set_reg_x(uint8_t val) { this->reg_x = val; }

void cpu::reset() {
  accumulator = 0;
  reg_x = 0;
  status = 0;
  pc = mem_read_u16(PC_INITIAL_VALUE_ADDRESS);
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

void cpu::load(vector<uint8_t> program) {
  uint16_t program_offset = PC_INITIAL_VALUE;
  mem_write_u16(PC_INITIAL_VALUE_ADDRESS, PC_INITIAL_VALUE);

  for (int i = 0; i < program.size(); i++) {
    memory[program_offset + i] = program[i];
  }
}

void cpu::load_and_run(vector<uint8_t> program) {
  load(program);
  reset();
  run();
}

uint16_t cpu::mem_read_u16(uint16_t address) {
  uint8_t low = mem_read(address);
  uint8_t high = mem_read(address+1);

  return high << 8 | (uint16_t) low;
}

void cpu::mem_write_u16(uint16_t address, uint16_t data) {
  uint8_t low = data & 0xff;
  uint8_t high = (data >> 8) & 0xff;

  mem_write(address, low);
  mem_write(address+1, high);
}
