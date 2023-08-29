#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chip_8_struct.h"

#define CHIP_PARAM Chip8 *chip

/*
** Chip instructions.
** - Multiple 'n' substitute for an address
** - Multiple 'k' substitute for a value
** - 'x' and 'y' substitute for an address (in V)
*/
void clear_display(CHIP_PARAM);              // 00E0
void return_from_subroutine(CHIP_PARAM);     // 00EE
void jump_to(CHIP_PARAM);                    // 1nnn
void call_subroutine(CHIP_PARAM);            // 2nnn
void skip_if_Vx_equals_next(CHIP_PARAM);     // 3xkk
void skip_if_Vx_not_equals_next(CHIP_PARAM); // 4xkk
void skip_if_Vx_equal_Vy(CHIP_PARAM);        // 5xy0
void set_Vx_to(CHIP_PARAM);                  // 6xkk
void add_to_Vx(CHIP_PARAM);                  // 7xkk
void set_Vx_to_Vy(CHIP_PARAM);               // 8xy0
void set_Vx_to_Vy_OR(CHIP_PARAM);            // 8xy1
void set_Vx_to_Vy_AND(CHIP_PARAM);           // 8xy2
void set_Vx_to_Vy_XOR(CHIP_PARAM);           // 8xy3
void add_Vy_to_Vx(CHIP_PARAM);               // 8xy4
void substract_Vy_to_Vx(CHIP_PARAM);         // 8xy5
void perform_right_shift(CHIP_PARAM);        // 8xy6
void substract_Vx_from_Vy(CHIP_PARAM);       // 8xy7
void perform_left_shift(CHIP_PARAM);         // 8xyE
void skip_if_not_equal(CHIP_PARAM);          // 9xy0
void set_I_to(CHIP_PARAM);                   // Annn
void jump_to_with_offset(CHIP_PARAM);        // Bnnn
void set_Vx_random(CHIP_PARAM);              // Cxkk
void display_sprite(CHIP_PARAM);             // Dxyn
void skip_if_pressed(CHIP_PARAM);            // Ex9E
void skip_if_not_pressed(CHIP_PARAM);        // ExA1
void set_Vx_to_delay(CHIP_PARAM);            // Fx07
void wait_for_keypress(CHIP_PARAM);          // Fx0A
void set_delay_to_Vx(CHIP_PARAM);            // Fx15
void set_sound_to_Vx(CHIP_PARAM);            // Fx18
void add_Vx_to_I(CHIP_PARAM);                // Fx1E
void set_I_to_sprite(CHIP_PARAM);            // Fx29
void store_BCD_representation(CHIP_PARAM);   // Fx33
void store_registers_in_I(CHIP_PARAM);       // Fx55
void read_registers_from_I(CHIP_PARAM);      // Fx65

#endif // INSTRUCTIONS_H_
