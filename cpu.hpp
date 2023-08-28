#include <iostream>
#include <vector>
#include <bitset>

#define STATUS_ZERO 1<<1 // 0b00000010
#define STATUS_N_ZERO 255-(1<<1) //0b11111101

#define STATUS_NEGATIVE 1<<7
#define STATUS_N_NEGATIVE 255-(1<<7)

//#define 

using namespace std;
using std::vector;

class cpu {
private:
  uint8_t accumulator;
  uint8_t reg_x;
  uint8_t status;
  uint8_t pc;

  inline void zero_pc() { this->pc = 0; }
  void set_zero_flag(bool flag) { flag ? this->status |= STATUS_ZERO : this->status &= STATUS_N_ZERO; }
  void set_negative_flag(bool flag) { flag ? this->status |= STATUS_NEGATIVE : this->status &= STATUS_N_NEGATIVE; }


  void update_zero_and_negative(uint8_t val) {
    (val == 0) ? set_zero_flag(true) : set_zero_flag(false);
    (val & STATUS_NEGATIVE) ? set_negative_flag(true) : set_negative_flag(false);
  }

  
public:
  cpu() : accumulator(0), status(0), pc(0) {}
  void print_status() { cout << bitset<8>(this->status) << endl; }
  inline uint8_t get_acc() { return this->accumulator; }
  inline uint8_t get_reg_x() { return this->reg_x; }

  inline uint8_t get_status() { return this->status; }
  inline bool get_zero() { return (this->get_status() & STATUS_ZERO); }
  inline bool get_negative() { return (this->get_status() & STATUS_NEGATIVE); }

  void set_acc(uint8_t val) { this->accumulator = val; }
  void set_reg_x(uint8_t val) { this->reg_x = val; }

  void interpret(vector<uint8_t> program) {
    zero_pc();
    
    while (true) {
      auto opcode = program[pc];
      pc++;

      switch (opcode) {
      case 0x00:
	return;

      case 0xA9: { /* LDA */
	auto param = program[pc];
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

};
