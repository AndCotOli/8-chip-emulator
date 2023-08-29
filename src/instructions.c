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

/*
** OP: Annn
** Description: set the value of the I register to nnn
*/
void set_I_to(Chip8 *chip) {
  uint16_t nnn = chip->current_op & 0x0FFF;

  chip->I_register = nnn;
}

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
