#include "chip.h"

/*
** Starts the system by setting all the appropiate variables.
*/
void init(Chip8 *chip) {

  // Registers
  chip->I_register = 0;
  chip->pc_register = PC_START;
  chip->stack_pointer_register = 0;

  for (int i = 0; i < NUM_REGISTERS; i++)
    chip->V_registers[i] = 0;

  // Operations
  chip->current_op = 0;

  // Memory
  for (int i = 0; i < RAM_CAPACITY; i++) {
    if (i < FONTSET_SIZE)
      chip->ram[i] = FONTSET[i];
    else
      chip->ram[i] = 0;
  }

  for (int i = 0; i < STACK_CAPACITY; i++)
    chip->stack[i] = 0;

  // Timers
  chip->delay_timer = 0;
  chip->sound_timer = 0;

  // Keyboard
  for (int i = 0; i < NUM_KEYS; i++)
    chip->keyboard[i] = 0;

  chip->key_pressed = FALSE;

  // Display
  for (int i = 0; i < DISPLAY_HEIGHT; i++)
    for (int j = 0; j < DISPLAY_WIDTH; j++)
      chip->display[i][j] = 0;

  // Flags
  chip->is_running_flag = TRUE;
  chip->is_paused_flag = FALSE;
  chip->draw_flag = FALSE;
}

void load_roam(Chip8 *chip, const char *path) {}

uint16_t get_opcode(Chip8 *chip) {
  return chip->ram[chip->pc_register] << 8 | chip->ram[chip->pc_register + 1];
}

void execute_instruction(Chip8 *chip) {
  uint16_t opcode = get_opcode(chip);

  switch (opcode & 0xF000) {
  case 0x0000:
    switch (opcode & 0x00FF) {
    case 0x00E0:
      clear_display(chip);
      break;
    case 0x00EE:
      return_from_subroutine(chip);
      break;
    default:
      printf("Error");
      exit(EXIT_FAILURE);
    }
    break;
  case 0x1000:
    jump_to(chip);
    break;
  case 0x2000:
    call_subroutine(chip);
    break;
  case 0x3000:
    skip_if_Vx_equals_next(chip);
    break;
  case 0x4000:
    skip_if_Vx_not_equals_next(chip);
    break;
  case 0x5000:
    skip_if_Vx_equal_Vy(chip);
    break;
  case 0x6000:
    set_Vx_to(chip);
    break;
  case 0x700:
    add_to_Vx(chip);
    break;
  case 0x8000:
    switch (opcode & 0x000F) {
    case 0x0000:
      set_Vx_to_Vy(chip);
      break;
    case 0x0001:
      set_Vx_to_Vy_OR(chip);
      break;
    case 0x0002:
      set_Vx_to_Vy_AND(chip);
      break;
    case 0x0003:
      set_Vx_to_Vy_XOR(chip);
      break;
    case 0x0004:
      add_Vy_to_Vx(chip);
      break;
    case 0x0005:
      substract_Vy_to_Vx(chip);
      break;
    case 0x0006:
      perform_right_shift(chip);
      break;
    case 0x0007:
      substract_Vx_from_Vy(chip);
      break;
    case 0x000E:
      perform_left_shift(chip);
      break;
    default:
      printf("Error");
      exit(EXIT_FAILURE);
    }
  case 0x9000:
    skip_if_not_equal(chip);
    break;
  case 0xA000:
    set_I_to(chip);
    break;
  case 0xB000:
    jump_to_with_offset(chip);
    break;
  case 0xC000:
    set_Vx_random(chip);
    break;
  case 0xD000:
    display_sprite(chip);
    break;
  case 0xE000:
    switch (opcode & 0x00FF) {
    case 0x009E:
      skip_if_pressed(chip);
      break;
    case 0x00A1:
      skip_if_not_pressed(chip);
      break;
    default:
      printf("Error");
      exit(EXIT_FAILURE);
    }
  case 0xF000:
    switch (opcode & 0x00FF) {
    case 0x0007:
      set_Vx_to_delay(chip);
      break;
    case 0x000A:
      wait_for_keypress(chip);
      break;
    case 0x0015:
      set_delay_to_Vx(chip);
      break;
    case 0x0018:
      set_sound_to_Vx(chip);
      break;
    case 0x001E:
      add_Vx_to_I(chip);
      break;
    case 0x0029:
      set_I_to_sprite(chip);
      break;
    case 0x0033:
      store_BCD_representation(chip);
      break;
    case 0x0055:
      store_registers_in_I(chip);
      break;
    case 0x0065:
      read_registers_from_I(chip);
      break;
    default:
      printf("Error");
      exit(EXIT_FAILURE);
    }
  default:
    printf("Error");
    exit(EXIT_FAILURE);
  }
}

void handle_user_input(Chip8 *chip) {}

void update_timers(Chip8 *chip) {
  if (chip->delay_timer > 0)
    chip->delay_timer--;
  if (chip->sound_timer > 0)
    chip->sound_timer--;
}
