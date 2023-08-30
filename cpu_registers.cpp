#include "cpu.h"

/* private */
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


/* public */
uint8_t cpu::get_acc() { return this->accumulator; }
uint8_t cpu::get_reg_x() { return this->reg_x; }

uint8_t cpu::get_status() { return this->status; }
bool cpu::get_zero() { return (this->get_status() & STATUS_ZERO); }
bool cpu::get_negative() { return (this->get_status() & STATUS_NEGATIVE); }

void cpu::set_acc(uint8_t val) { this->accumulator = val; }
void cpu::set_reg_x(uint8_t val) { this->reg_x = val; }

void cpu::print_status() { std::cout << bitset<8>(this->status) << std::endl; }
