#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <vector>
#include <bitset>

#define STATUS_ZERO 1<<1 // 0b00000010
#define STATUS_N_ZERO 255-(1<<1) //0b11111101

#define STATUS_NEGATIVE 1<<7
#define STATUS_N_NEGATIVE 255-(1<<7)

#define PC_INITIAL_VALUE_ADDRESS 0xFFFC
#define PC_INITIAL_VALUE 0x8000

using namespace std;
using std::vector;

class cpu {
private:

  enum AdressingMode {
    Immediate,
    ZeroPage,
    ZeroPage_X,
    ZeroPage_Y,
    Absolute,
    Absolute_X,
    Absolute_Y,
    Indirect_X,
    Indirect_Y,
    None
  };

  uint8_t accumulator;
  uint8_t reg_x;
  uint8_t status;
  uint16_t pc;
  uint8_t memory[0xFFFF];

  void set_zero_flag(bool flag);
  void set_negative_flag(bool flag);
  void update_zero_and_negative(uint8_t val);
  uint8_t mem_read(uint16_t address);
  void mem_write(uint16_t address, uint8_t data);
  
public:

  cpu();
  void print_status();
  uint8_t get_acc();
  uint8_t get_reg_x();

  uint8_t get_status();
  bool get_zero();
  bool get_negative();

  void set_acc(uint8_t val);
  void set_reg_x(uint8_t val);

  void reset();    
  void run();
  void load(vector<uint8_t> program);
  void load_and_run(vector<uint8_t> program);
  uint16_t mem_read_u16(uint16_t address);
  void mem_write_u16(uint16_t address, uint16_t data);

};

#endif
