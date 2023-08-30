#include <stdint.h>

#include "instructions.h"

/*
** OP: 00E0
** Description: clear the display
*/
void clear_display(Chip8 *chip) {
  for (int i = 0; i < DISPLAY_HEIGHT; i++)
    for (int j = 0; j < DISPLAY_WIDTH; j++)
      chip->display[i][j] = 0;

  chip->draw_flag = TRUE;
  chip->pc_register += 2;
}

/*
** OP: 00EE
** Description: set the program counter to address at top of stack and decrement
*stack pointer.
*/
void return_from_subroutine(Chip8 *chip) {
  chip->stack_pointer_register--;
  chip->pc_register = chip->stack[chip->stack_pointer_register];
  chip->pc_register += 2;
}

/*
** OP: 1nnn
** Description: set program counter to nnn
*/
void jump_to(Chip8 *chip) {
  uint16_t nnn = chip->current_op & 0x0FFF;

  chip->stack[chip->stack_pointer_register] = chip->pc_register;
  chip->stack_pointer_register++;
  chip->pc_register = nnn;
}

void call_subroutine(Chip8 *chip) {}

void skip_if_Vx_equals_next(CHIP_PARAM){};     // 3xkk
void skip_if_Vx_not_equals_next(CHIP_PARAM){}; // 4xkk
void skip_if_Vx_equal_Vy(CHIP_PARAM){};        // 5xy0

/*
** OP: 6xkk
** Description: put the value kk into register x
*/
void set_Vx_to(Chip8 *chip) {
  uint16_t x = (chip->current_op & 0x0F00) >> 8;
  uint16_t kk = chip->current_op & 0x00FF;

  chip->V_registers[x] = kk;
  chip->pc_register += 2;
}

/*
** OP: 7xkk
** Description: add the value kk to the register x
*/
void add_to_Vx(Chip8 *chip) {
  uint16_t x = (chip->current_op & 0x0F00) >> 8;
  uint16_t kk = chip->current_op & 0x00FF;

  chip->V_registers[x] += kk;
  chip->pc_register += 2;
}

void set_Vx_to_Vy(CHIP_PARAM){};         // 8xy0
void set_Vx_to_Vy_OR(CHIP_PARAM){};      // 8xy1
void set_Vx_to_Vy_AND(CHIP_PARAM){};     // 8xy2
void set_Vx_to_Vy_XOR(CHIP_PARAM){};     // 8xy3
void add_Vy_to_Vx(CHIP_PARAM){};         // 8xy4
void substract_Vy_to_Vx(CHIP_PARAM){};   // 8xy5
void perform_right_shift(CHIP_PARAM){};  // 8xy6
void substract_Vx_from_Vy(CHIP_PARAM){}; // 8xy7
void perform_left_shift(CHIP_PARAM){};   // 8xyE
void skip_if_not_equal(CHIP_PARAM){};    // 9xy0

/*
** OP: Annn
** Description: set the value of the I register to nnn
*/
void set_I_to(Chip8 *chip) {
  uint16_t nnn = chip->current_op & 0x0FFF;

  chip->I_register = nnn;
}

void jump_to_with_offset(CHIP_PARAM){}; // Bnnn
void set_Vx_random(CHIP_PARAM){};       // Cxkk

/*
** OP: Dxyn
** Description: Display n-byte sprite starting at memory localtion I at (Vx, Vy)
*/
void display_sprite(Chip8 *chip) {
  uint8_t x = (chip->current_op & 0x0F00) >> 8;
  uint8_t y = (chip->current_op & 0x00F0) >> 4;
  uint8_t n = chip->current_op & 0x000F;

  uint8_t Vx = chip->V_registers[x];
  uint8_t Vy = chip->V_registers[y];

  uint8_t sprite;

  chip->V_registers[0xF] = FALSE;
  for (int y_coord = 0; y < n; y++) {
    sprite = chip->ram[chip->I_register + y_coord];
    for (int x_coord = 0; x < 8; x++) {
      if ((sprite & (0x80 >> x_coord)) != 0) {
        if (chip->display[Vy + y_coord][Vx + x_coord] == 1)
          chip->V_registers[0xF] = TRUE;

        chip->display[Vy + y_coord][Vx + x_coord] ^= 1;
      }
    }
  }

  chip->draw_flag = TRUE;
  chip->pc_register += 2;
}

void skip_if_pressed(CHIP_PARAM){};          // Ex9E
void skip_if_not_pressed(CHIP_PARAM){};      // ExA1
void set_Vx_to_delay(CHIP_PARAM){};          // Fx07
void wait_for_keypress(CHIP_PARAM){};        // Fx0A
void set_delay_to_Vx(CHIP_PARAM){};          // Fx15
void set_sound_to_Vx(CHIP_PARAM){};          // Fx18
void add_Vx_to_I(CHIP_PARAM){};              // Fx1E
void set_I_to_sprite(CHIP_PARAM){};          // Fx29
void store_BCD_representation(CHIP_PARAM){}; // Fx33
void store_registers_in_I(CHIP_PARAM){};     // Fx55
void read_registers_from_I(CHIP_PARAM){};    // Fx65
