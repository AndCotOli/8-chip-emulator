#include "chip.h"

#define ERROR_OPCODE                                                           \
  fprintf(stderr, "ERROR: unrecognized opcode 0x%X\n", chip->current_op)

void (*instruction_table[16])(Chip8 *);
void (*arithmetic_table[16])(Chip8 *);
void (*skip_table[2])(Chip8 *);
void (*register_table[9])(Chip8 *);

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
    chip->keyboard[i] = FALSE;

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

void load_roam(Chip8 *chip, const char *path) {
  FILE *file = fopen(path, "rb");

  uint8_t *buffer;
  long rom_length;
  if (file != NULL) {
    fseek(file, 0, SEEK_END);
    rom_length = ftell(file);
    rewind(file);

    buffer = malloc(sizeof(uint8_t) * rom_length);
    if (buffer == NULL) {
      fprintf(stderr, "ERROR: Out of memory\n");
      exit(EXIT_FAILURE);
    }
    fread(buffer, sizeof(uint8_t), rom_length, file);

    if ((PROGRAM_END_ADDR - PROGRAM_START_ADDR) >= rom_length) {
      for (int i = 0; i < rom_length; i++) {
        chip->ram[i + PC_START] = buffer[i];
      }
    } else {
      fprintf(stderr, "ERROR: File too large\n");
      exit(EXIT_FAILURE);
    }
  } else {
    fprintf(stderr, "ERROR: file is null\n");
    exit(EXIT_FAILURE);
  }

  fclose(file);
  free(buffer);
}

uint16_t get_opcode(Chip8 *chip) {
  if (chip->pc_register + 1 < RAM_CAPACITY)
    return chip->ram[chip->pc_register] << 8 | chip->ram[chip->pc_register + 1];
  else {
    fprintf(stderr, "ERROR: Out of bounds.\n");
    exit(EXIT_FAILURE);
  }
}

void execute_instruction(Chip8 *chip) {
  uint16_t opcode = get_opcode(chip);
  chip->current_op = opcode;
  instruction_table[(opcode & 0xF000) >> 12](chip);
}

void zero_instruction(Chip8 *chip) {
  switch (N) {
  case 0x0:
    clear_display(chip);
    break;
  case 0xE:
    return_from_subroutine(chip);
    break;
  default:
    ERROR_OPCODE;
    exit(EXIT_FAILURE);
  }
}

void arithmetic_instruction(Chip8 *chip) {
  arithmetic_table[(chip->current_op & 0x000F)](chip);
}

void skip_instruction(Chip8 *chip) {
  switch (N) {
  case 0xE:
    skip_if_pressed(chip);
    break;
  case 0x1:
    skip_if_not_pressed(chip);
    break;
  default:
    ERROR_OPCODE;
    exit(EXIT_FAILURE);
  }
}

void register_instruction(Chip8 *chip) {
  // FIXME: Find a way to map the opcodes correctly (most likely will need to
  // use null_instruction)
  register_table[(chip->current_op & 0x00FF)](chip);
}

void (*instruction_table[16])(Chip8 *) = {zero_instruction,
                                          jump_to,
                                          call_subroutine,
                                          skip_if_Vx_equals_next,
                                          skip_if_Vx_not_equals_next,
                                          skip_if_Vx_equal_Vy,
                                          set_Vx_to,
                                          add_to_Vx,
                                          arithmetic_instruction,
                                          skip_if_not_equal,
                                          set_I_to,
                                          jump_to_with_offset,
                                          set_Vx_random,
                                          display_sprite,
                                          skip_instruction,
                                          register_instruction};

void (*arithmetic_table[16])(Chip8 *) = {
    set_Vx_to_Vy,        set_Vx_to_Vy_OR,      set_Vx_to_Vy_AND,
    set_Vx_to_Vy_XOR,    add_Vy_to_Vx,         substract_Vy_to_Vx,
    perform_right_shift, substract_Vx_from_Vy, perform_left_shift};

void (*register_table[9])(Chip8 *) = {
    set_Vx_to_delay,          wait_for_keypress,    set_delay_to_Vx,
    set_sound_to_Vx,          add_Vx_to_I,          set_I_to_sprite,
    store_BCD_representation, store_registers_in_I, read_registers_from_I};

void handle_user_input(Chip8 *chip) {}

void update_timers(Chip8 *chip) {
  if (chip->delay_timer > 0)
    chip->delay_timer--;
  if (chip->sound_timer > 0)
    chip->sound_timer--;
}
