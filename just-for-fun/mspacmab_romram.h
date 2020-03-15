typedef unsigned char   undefined;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
typedef unsigned long long    qword;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned short    ushort;
typedef unsigned short    word;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void

typedef struct hardware_floating_sprite_t hardware_floating_sprite_t, *Phardware_floating_sprite_t;

typedef enum color_e {
    NONE=255,
    _flashing=2,
    color_maze_level_14_15_16_17_and_ghosts_door=24,
    color_maze_level_1_2_18_19_20_21=29,
    color_maze_level_3_4_5=22,
    color_maze_level_6_7_8_9=20,
    color_pacman_and_ghost_initial_map_positions=26,
    color_reset_maybe_black=15,
    color_tunnel_area=27,
    fruit=0,
    inky=5,
    mspac=9,
    orange_and_color_maze_level_10_11_12_13=7,
    pink=3,
    red=1,
    white=31
} color_e;

struct hardware_floating_sprite_t {
    byte x_flip:1;
    byte y_flip:1;
    byte sprite_image_number:6;
    enum color_e color;
};

typedef enum tile_coord_changes_x_e {
    left=1,
    right=255,
    up_down=0
} tile_coord_changes_x_e;

typedef struct cmd_8_clearact_t cmd_8_clearact_t, *Pcmd_8_clearact_t;

struct cmd_8_clearact_t { // clear the act # from the screen
    byte cmd_F8;
};

typedef struct wave_t wave_t, *Pwave_t;

struct wave_t {
    byte num;
    undefined field_0x1;
    byte cur_bit;
    byte sel;
    undefined field_0x4;
    undefined field_0x5;
    pointer next_byte;
    undefined field_0x8;
    undefined field_0x9;
    undefined field_0xa;
    byte type;
    byte duration;
    byte dir;
    byte base_freq;
    byte vol;
};

typedef enum tile_coord_changes_y_e {
    down=1,
    left_right=0,
    up=255
} tile_coord_changes_y_e;

typedef struct sprite_coord_yx_t sprite_coord_yx_t, *Psprite_coord_yx_t;

struct sprite_coord_yx_t { // 0x1d == wraparound -> 0x3d. 0x3e == wraparound -> 0x1e.
    byte y; // bottom to top = decreases (0x22..0x3e)
    byte x; // left to right = decreases (0x1e..0x3d)
};

typedef struct difficulty1_6_bytes_t difficulty1_6_bytes_t, *Pdifficulty1_6_bytes_t;

struct difficulty1_6_bytes_t {
    byte speed_and_orientation_index; // byte 0: (0..6) speed bit patterns and orientation changes (table at #330F)
    byte field_0x1; // byte 1: (00, 01, 02) stored at #4DB0 - seems to be unused
    byte ghost_counter_table; // byte 2: (0..3) ghost counter table to exit home (table at #0843)
    byte remaining_number_of_pills_table; // byte 3: (0..7) remaining number of pills to set difficulty flags (table at #084F)
    byte ghost_blue_time_table; // byte 4: (0..8) ghost time to stay blue when pacman eats the big pill (table at #0861)
    byte ghost_out_of_home_number_of_units_table; // byte 5: (0..2) number of units before a ghost goes out of home (table at #0873)
};

typedef struct fruit_t fruit_t, *Pfruit_t;

struct fruit_t {
    byte sprit_number;
    byte color;
};

typedef enum character_orientation_e { // stored middle of movement
    down=1,
    left=2,
    right=0,
    up=3
} character_orientation_e;

typedef struct difficulty2_t difficulty2_t, *Pdifficulty2_t;

struct difficulty2_t {
    byte field_0x0[16];
    byte field_0x10[12];
    word field_0x1c[7];
};

typedef struct difficulty5_fruit_release_t difficulty5_fruit_release_t, *Pdifficulty5_fruit_release_t;

struct difficulty5_fruit_release_t {
    byte sprite;
    byte color;
    byte point;
};

typedef struct floating_sprite_coord_t floating_sprite_coord_t, *Pfloating_sprite_coord_t;

struct floating_sprite_coord_t { // 224x256
    byte x; // 31 to 239
    byte y; // 16 to 256
};

typedef struct dereference_word_t dereference_word_t, *Pdereference_word_t;

struct dereference_word_t { // Because DE init
    word data;
    word * table_current_ptr;
    byte index;
};

typedef struct task_core_t task_core_t, *Ptask_core_t;

typedef enum task_core_e {
    blue_ghost_AI=10,
    blue_ghost_movement_when_power_pill=14,
    clear_fruit_and_pacman_position=30,
    clear_full_data_game=17,
    clear_whole_screen_or_maze=0,
    clears_color_RAM=6,
    clears_pills_and_power_pills=18,
    clears_sprites=19,
    draw_draw_credit_qty=29,
    draw_extra_life_points=31,
    draw_fruits_right_screen=27,
    draw_maze=2,
    draw_pellets=3,
    draw_remaining_lives_bottom_screen=26,
    draw_text_or_graphics=28,
    increase_main_subroutine_number=22,
    orange_ghost_AI=11,
    orange_ghost_movement_when_power_pill=15,
    pacman_AI_movement_when_demo=23,
    pink_ghost_AI=9,
    pink_ghost_movement_when_power_pill=13,
    print_high_score_text_then_players_score=24,
    red_ghost_AI=8,
    red_ghost_movement_when_power_pill=12,
    reset_ghost_home_counter=5,
    reset_sprites_to_default_values=4,
    select_maze_color=1,
    set_game_to_demo_mode=7,
    setup_config_from_dip_switches=20,
    setup_difficulty=16,
    update_score_then_draw=25,
    update_screen_pill_config_to_video_ram=21
} task_core_e;

typedef union task_core_u task_core_u, *Ptask_core_u;

typedef enum text_e {
    ACT_III=54,
    BAD_R_M=36,
    BLINKY=13,
    BONUS=43,
    BONUS_NONE=42,
    BONUS__NONE=48,
    CREDIT=1,
    C_MIDWAY_MFG_CO=19,
    FIVTY_POINTS=18,
    FREE_PLAY_2=2,
    FREE_PLAY_25=37,
    GAME_OVER=5,
    HIGH_SCORE=0,
    INKY=47,
    JUNIOR=21,
    KILLER=22,
    MAD_DOG=20,
    MEMORY_OK=35,
    MS_PACMAN=12,
    MS_PAC_MAN=51,
    MS_PAC_MEN=41,
    ONE_OR_TWO_PLAYERS=9,
    ONE_PLAYER_ONLY=8,
    PINKY=15,
    PLAYER_ONE=3,
    PLAYER_TWO=4,
    PUSH_START_BUTTON=7,
    SPACE=48,
    STARRING=16,
    SUE=49,
    SUPER_PAC_MAN=28,
    TABLE=44,
    TEN_POINTS=17,
    THEY_MEET=50,
    THE_CHASE=23,
    TILE_MIDWAY_LOGO_AND_COPYRIGHT_TEXT=11,
    TILE_MSPACMAN=10,
    TILE_READY=6,
    T_000=46,
    T_1980_1981=53,
    T_1_COIN_1_CREDIT=38,
    T_1_COIN_2_CREDITS=39,
    T_2_COINS_1_CREDIT=40,
    UNKNOW1=27,
    UPRIGHT=45,
    WITH=14
} text_e;

union task_core_u {
    byte param;
    enum text_e text_number;
    enum color_e color;
};

struct task_core_t {
    enum task_core_e value;
    union task_core_u param;
};

typedef enum tile_e { // PACMAN tile codes
    A=65,
    B=66,
    C=67,
    D=68,
    E=69,
    F=70,
    G=71,
    H=72,
    I=73,
    J=74,
    K=75,
    L=76,
    M=77,
    N=78,
    O=79,
    P=80,
    PTS_1=93,
    PTS_2=94,
    PTS_3=95,
    Q=81,
    R=82,
    S=83,
    T=84,
    U=85,
    V=86,
    W=87,
    X=88,
    Y=89,
    Z=90,
    _tofind=91,
    copyright=92,
    hex_digit_0=0,
    hex_digit_1=1,
    hex_digit_2=2,
    hex_digit_3=3,
    hex_digit_4=4,
    hex_digit_5=5,
    hex_digit_6=6,
    hex_digit_7=7,
    hex_digit_8=8,
    hex_digit_9=9,
    hex_digit_A=10,
    hex_digit_B=11,
    hex_digit_C=12,
    hex_digit_D=13,
    hex_digit_E=14,
    hex_digit_F=15,
    map_obstacle_1=192,
    map_obstacle_2=193,
    mspac0=32,
    mspac1=33,
    mspac2=34,
    mspac3=35,
    pills_0=16,
    pills_1=17,
    pills_2=18,
    pills_3=19,
    pills_4=20,
    pills_5=21,
    space=64
} tile_e;

typedef struct sound_channel_16bits_t sound_channel_16bits_t, *Psound_channel_16bits_t;

struct sound_channel_16bits_t {
    byte freq0;
    byte freq1;
    byte freq2;
    byte freq3;
    byte vol;
};

typedef struct in0_t in0_t, *Pin0_t;

struct in0_t {
    byte joystick_up:1;
    byte joystick_left:1;
    byte joystick_right:1;
    byte joystick_down:1;
    byte rack_test:1;
    byte coin_1_inserted:1;
    byte service_1_pressed:1;
};

typedef enum enum {
    AT_HOME=0,
    CROSSING_THE_DOOR=2,
    GOING_FOR_PACMAN=1,
    GOING_TO_THE_DOOR=3
} enum;

typedef struct in1_t in1_t, *Pin1_t;

struct in1_t {
    byte joystick2_up:1;
    byte joystick2_left:1;
    byte joystick2_right:1;
    byte joystick2_down:1;
    byte service_mode_switch:1;
    byte player1_start_button:1;
    byte player2_start_button:1;
    byte cocktail_cabinet_DIP:1;
};

typedef struct difficulty4_ghost_out_of_home_t difficulty4_ghost_out_of_home_t, *Pdifficulty4_ghost_out_of_home_t;

struct difficulty4_ghost_out_of_home_t {
    byte counter_for_pink;
    byte counter_for_blue;
    byte coulter_for_orange;
};

typedef enum level_state_e {
    GHOST_MOVE=3,
    GHOST_WAIT_FOR_START=2
} level_state_e;

typedef struct pacman_speed_bit_patterns_t pacman_speed_bit_patterns_t, *Ppacman_speed_bit_patterns_t;

struct pacman_speed_bit_patterns_t {
    dword normal_state;
    dword big_pill_state;
    dword second_difficulty_flag;
    dword first_difficulty_flag;
};

typedef struct effect_t effect_t, *Peffect_t;

struct effect_t {
    byte num; // effects to play sequentially (bitmask) set bit 5 of BNOISE to make the bounce sound
    undefined field_0x1;
    byte cur_bit; // current effect
    byte table[8]; // table of parameters, initially copied from ROM
    byte type;
    byte duration;
    byte dir;
    byte base_freq;
    byte vol;
};

typedef struct task_timed_t task_timed_t, *Ptask_timed_t;

typedef enum task_timed_e {
    clear_fruit_points=4,
    clear_fruit_position=5,
    clear_ready_message=6,
    increase_killed_ghost_animation_state=3,
    increase_state_in_1st_cutescene=7,
    increase_state_in_2nd_cutescene=8,
    increase_state_in_3rd_cutescene=9,
    increase_subroutine_COIN_INSERTED_state=1,
    increase_subroutine_DEMO_state=2,
    increase_subroutine_PLAYING_state=0
} task_timed_e;

struct task_timed_t { // scheduled tasks list (run inside IRQ)
    byte counter:6; // number of time units to wait
    byte time_unit:2; // 01=10 hundredths, 10=1 second, 11=10 seconds
    enum task_timed_e index; // index for the jump table
    byte param; // parameter for b
};

typedef struct cmd_2_setn_t cmd_2_setn_t, *Pcmd_2_setn_t;

struct cmd_2_setn_t {
    byte cmd_F2;
    byte value;
};

typedef struct sound_channel_20bits_t sound_channel_20bits_t, *Psound_channel_20bits_t;

struct sound_channel_20bits_t {
    byte freq0;
    byte freq1;
    byte freq2;
    byte freq3;
    byte freq4;
    byte vol;
};

typedef struct cmd_7_showact_t cmd_7_showact_t, *Pcmd_7_showact_t;

struct cmd_7_showact_t {
    byte cmd_F7;
};

typedef struct cmd_5_playsound_t cmd_5_playsound_t, *Pcmd_5_playsound_t;

struct cmd_5_playsound_t { // sound code	play a sound (eg 10=ghost bump)
    byte cmd_F5;
    byte sound_code;
};

typedef enum sprite_e {
    BLUE=2,
    FRUIT=5,
    ORANGE=3,
    PACMAN=4,
    PINK=1,
    RED=0
} sprite_e;

typedef enum ghost_substate_e {
    AT_HOME=0,
    CROSSING_THE_DOOR=2,
    GOING_FOR_PACMAN=1,
    GOING_TO_THE_DOOR=3
} ghost_substate_e;

typedef struct difficulty3_t difficulty3_t, *Pdifficulty3_t;

struct difficulty3_t {
    byte numbre_of_pills_difficulty_flag1;
    byte numbre_of_pills_difficulty_flag2;
};

typedef enum killing_ghost_state_e {
    KILL_BLUE_GHOST=3,
    KILL_ORANGE_GHOST=4,
    KILL_PINK_GHOST=2,
    KILL_RED_GHOST=1,
    NOTHING=0
} killing_ghost_state_e;

typedef struct cmd_0_loop_t cmd_0_loop_t, *Pcmd_0_loop_t;

struct cmd_0_loop_t { // repeat this N times, perhaps?
    byte cmd_F0;
    undefined field_0x1;
    undefined field_0x2;
    byte color; // 0x09=yellow otto, 0x16=white
};

typedef enum pacman_movement_update_delay_e { // not 0xff - the game doesn't move pacman, but decrements instead
    PACMAN_EATING_BIG_PILL=6,
    PACMAN_EATING_PILL=1,
    PACMAN_NOT_EATING=255
} pacman_movement_update_delay_e;

typedef struct ghost_speed_bit_patterns_t ghost_speed_bit_patterns_t, *Pghost_speed_bit_patterns_t;

struct ghost_speed_bit_patterns_t { // difficulty dependant
    dword normal_state;
    dword speed_state; // eg. blue ghost
    dword specific_state; // eg. tunnel areas
};

typedef enum enum_1 {
    BLUE=2,
    FRUIT=5,
    ORANGE=3,
    PACMAN=4,
    PINK=1,
    RED=0
} enum_1;

typedef struct cmd_F_end_t cmd_F_end_t, *Pcmd_F_end_t;

struct cmd_F_end_t {
    byte cmd_FF;
};

typedef struct cmd_1_setpos_t cmd_1_setpos_t, *Pcmd_1_setpos_t;

struct cmd_1_setpos_t { // position
    byte cmd_F1;
    struct sprite_coord_yx_t coord;
};

typedef enum ghost_state_e { // LEFT for blue, RIGHT for orange
    ALIVE=0,
    DEAD=1,
    ENTERING_HOME_AFTER_BEING_KILLED=2,
    GO_LEFT_AFTER_ENTERING_HOME_AFTER_DEAD=3,
    GO_RIGHT_AFTER_ENTERING_HOME_AFTER_DEAD=3
} ghost_state_e;

typedef struct cmd_4_nop_t cmd_4_nop_t, *Pcmd_4_nop_t;

struct cmd_4_nop_t {
    byte cmd_F4;
};

typedef struct sprites_t sprites_t, *Psprites_t;

struct sprites_t {
    struct hardware_floating_sprite_t unknown;
    struct hardware_floating_sprite_t red_ghost;
    struct hardware_floating_sprite_t pink_ghost;
    struct hardware_floating_sprite_t inky_ghost;
    struct hardware_floating_sprite_t orange_ghost;
    struct hardware_floating_sprite_t mspac;
    struct hardware_floating_sprite_t fruit;
};

typedef struct cmd_6_pause_t cmd_6_pause_t, *Pcmd_6_pause_t;

struct cmd_6_pause_t {
    byte cmd_F6;
};

typedef struct mspac_graph_t mspac_graph_t, *Pmspac_graph_t;

struct mspac_graph_t {
    enum color_e color;
    enum tile_e graphic tile code;
    pointer ptr;
};

typedef struct dereference_byte_t dereference_byte_t, *Pdereference_byte_t;

struct dereference_byte_t { // because hl modified
    byte value;
    byte * table_current_ptr;
};

typedef struct tile_coord_changes_yx_t tile_coord_changes_yx_t, *Ptile_coord_changes_yx_t;

struct tile_coord_changes_yx_t {
    enum tile_coord_changes_y_e y;
    enum tile_coord_changes_x_e x;
};

typedef struct cmd_3_setchar_t cmd_3_setchar_t, *Pcmd_3_setchar_t;

struct cmd_3_setchar_t { // switch to the specified sprite code table
    byte cmd_F3;
    pointer p_sprite;
};

typedef enum main_state_e {
    COIN_INSERTED=2,
    DEMO=1,
    INIT=0,
    PLAYING=3
} main_state_e;

#define true 1




void reset(void);
void * memset(byte *s,byte c,byte n);
void RET(void);
void T10_setup_difficulty(undefined2 param_1);
byte dereference_pointer_to_byte(byte *lookup_table,byte index);
dereference_word_t dereference_pointer_to_word(word *lookup_table,byte index);
void jump_table_fn(undefined *lookup_table,byte index);
void insert_task(task_core_t *task);
void add_timed_task(task_timed_t *task);
void vblank(bool test_mode);
void add_to_task_list(task_core_e task_value,byte task_param);
byte * convert_xy_to_screen_position(sprite_coord_yx_t coord);
void interrupt_vector(void);
void update_timers_and_random_number(void);
void execute_TIMED_task(void);
void TT06_clear_ready_message(char *param_1);
byte rack_input__add_credits(void);
void debounce_coin_input__add_credits(void);
void coints_to_credits_routine(void);
void blink_coin_lights(void);
void draw_1UP(undefined *param_1);
void draw_2UP(undefined *param_1);
void clear_1UP(undefined *param_1);
void clear_2UP(undefined *param_1);
void check_for_double_size_pacman(void);
void change_game_mode(void);
void execute_INIT_task_state(void);
void I00_add_first_tasks(void);
void execute_DEMO_task_state(undefined param_1);
void demo_mode_prepare_screen(undefined2 param_1);
void pacman_draw_red_ghost(void);
void pacman_draw_-shadow(undefined param_1);
void pacman_draw_blinky(undefined param_1);
void pacman_draw_pink_ghost(void);
void pacman_draw_-speedy(undefined param_1);
void pacman_draw_pinky(undefined param_1);
void pacman_draw_blue_ghost(void);
void pacman_draw_-bashful(undefined param_1);
void pacman_draw_inky(undefined param_1);
void pacman_draw_orange_ghost(void);
void pacman_draw_-pokey(undefined param_1);
void pacman_draw_clyde(undefined2 param_1);
void pacman_draw_10pts(void);
void pacman_get_demo_ready(char *param_1,undefined2 param_2);
void pacman_3rd_intermission_end(void);
void pacman_draw_start_and_run_demo(void);
void pacman_check_to_release_pink(void);
void pacman_check_to_release_inky(void);
void pacman_check_to_release_orange_ghost(void);
void pacman_check_for_demo_completion(void);
void pacman_end_demo_and_return(void);
void add_task_to_print_text(text_e text);
void TT02_increase_subroutine_DEMO_state(void);
void pacman_used_in_demo_mode(char param_1);
undefined pacman_used_during_attract_mode(void);
void pacman_only_used_during_attract_mode(undefined param_1,undefined *param_2);
byte execute_COIN_INSERTED_task_state(void);
byte C00_init_screen(undefined param_1);
void C01_draw_credits_qty_and_check_1P_OR_2P_button_for_start(undefined param_1);
void C02_init_screen_ready_for_play(void);
void TT01_increase_subroutine_COIN_INSERTED_state(void);
void C04_draw_remaining_lives_and_reset_states(byte param_1,undefined *param_2);
void execute_PLAYING_task_state(void);
void setup_difficulty(undefined2 param_1);
void copy_difficulty_related_data(undefined *difficulty_table);
void set_pink_ghost_counter_to_go_out_of_home_limit(undefined *src);
void P00_reset_game_data(undefined param_1);
void TT00_increase_subroutine_PLAYING_state(void);
void P01_init_screen_then_goto_P09(void);
void P03_check_rack_test(void);
void goto_state_P0C(void);
void P04_player_is_died_game_over(void);
void P06_switch_player(undefined param_1);
void P08_end_of_demo(void);
void P09_prepare_screen_level(void);
void P0B_loop_state_P03(void);
void P0C_end_of_level_clear_sound(task_timed_t *task);
void P0E_flash_screen_on(void);
void change_maze_color(byte color);
void P10_flash_screen_off(void);
void P0E_flash_screen_on(void);
void P10_flash_screen_off(void);
void P0E_flash_screen_on(void);
void P10_flash_screen_off(void);
void P0E_flash_screen_on(void);
void P10_flash_screen_off(void);
void P1E_end_of_level_after_flash_screen(void);
void P20_end_of_level_clear_sounds_and_run_intermissions(void);
void state_for_start(void);
void P22_prepare_next_level(undefined param_1);
void P09_prepare_screen_level(void);
void P0B_goto_state_P03_loop(void);
void __maybe_player_change_backup_current_player_game_settings(void);
void handle_ghost_flashing_and_colors_when_power_pills_are_eaten(void);
void pacman_only_set_color_for_dead_ghost(void);
byte handle_power_pill_flashes(void);
void adjust_ghost_movement(undefined param_1);
void is_time_to_change_ghost_animation(void);
void is_time_to_reverse_ghost_direction(void);
void change_background(void);
void check_for_fruit_to_come_out(void);
void TT04_clear_fruit_points(void);
void TT05_clear_fruit_position(void);
void update_ghost_and_pacman_state(void);
void check_for_ghosts_being_eaten_and_set_ghost_states_accordingly(void);
void state_red_ghost_update(void);
void state_pink_ghost_update(void);
void state_blue_ghost_update(void);
void state_orange_ghost_update(void);
void state_red_ghost_eyes(void);
void state_red_ghost_eyes_above(void);
void state_pink_ghost_eyes(void);
void state_pink_ghost_eyes_above(void);
void state_blue_ghost_eyes(void);
void state_blue_ghost_eyes_above(void);
void state_blue_ghost_eyes_in_house(void);
void state_orange_ghost_eyes(void);
void state_orange_ghost_eyes_above(void);
void state_orange_ghost_eyes_in_house(void);
void ghost_stuff_after_eaten_or(void);
void ghost_stuff0(void);
void TT03_increase_killed_ghost_animation_state(void);
void is_pacman_dead(void);
void D01_dead_animation_state_1_2_3_4(void);
void D05_dead_animation_state(void);
void animate_dead_mspac(byte param_1,short param_2);
void D06_dead_animation_state(void);
void D07_dead_animation_state(void);
void D08_dead_animation_state(void);
void D09_dead_animation_state(void);
void D0A_dead_animation_state(void);
void D0B_dead_animation_state(void);
void D0C_dead_animation_state(void);
void D0D_dead_animation_state(void);
void D0E_dead_animation_state(void);
void D0F_dead_animation_state(void);
void D10_dead_animation_state(void);
void control_blue_ghost_timer(void);
void is_time_to_leave_house(void);
void cocktail_mode_update_sprites(void);
void no_cocktail_mode_update_sprites(void);
void update_pacman_orientation(undefined2 param_1,short param_2);
void pacman_only_check_for_and_handle_big_pac-man_sprites_in_1st_cutscene(short param_1);
void pacman_only_check_for_and_handle_big_pac-man_sprites_in_2nd_cutscene(short param_1);
void pacman_only_check_for_and_handle_big_pac-man_sprites_in_3rd_cutscene(short param_1);
void O00_moving_east(void);
void O01_moving_south(void);
void O02_moving_west(void);
void O03_moving_north(void);
void check_for_collision_with_regular_ghost(void);
void check_for_collision_with_blue_ghost(void);
void handles_pacman_movement(void);
void can_pacman_eat_big_pill(void);
void pacman_eat_big_pill(void);
void update_timers_for_ghosts_to_leave_ghost_house(void);
void control_movement_red_ghost(void);
void handles_red_ghost_movement(void);
void control_movement_pink_ghost(void);
void handles_pink_ghost_movement(void);
void control_movement_blue_ghost(void);
void handles_blue_ghost_movement(void);
void control_movement_orange_ghost(void);
void handles_orange_ghost_movement(void);
void is_sprite_using_tunnel(byte sprite_tile_coord_index);
void is_reverse_red_ghost_direction_time(void);
void reverse_red_ghost_direction(void);
void is_reverse_pink_ghost_direction_time(void);
void reverse_pink_ghost_direction(void);
void is_reverse_blue_ghost_direction_time(void);
void reverse_blue_ghost_direction(undefined param_1);
void is_reverse_orange_ghost_direction_time(void);
void reverse_orange_ghost_direction(undefined param_1);
void vblank_continuation(bool test_mode);
sprite_coord_yx_t update_coord(sprite_coord_yx_t *sprite_location,sprite_coord_yx_t *seek_location);
byte get_from_screen_position(sprite_coord_yx_t *sprite_location,sprite_coord_yx_t *seek_location);
sprite_coord_yx_t convert_sprite_position_to_tile_position(sprite_coord_yx_t sprite_position);
byte * convert_xy_to_screen_position(sprite_coord_yx_t coord);
sprite_coord_yx_t convert_xy_to_color_screen_position(sprite_coord_yx_t coord);
void check_ghost_entering_tunnel_slowdown(sprite_coord_yx_t coord,byte *delay);
void leave_house_check_pink_ghost(void);
void release_pink_ghost_from_the_ghost_house(void);
void leave_house_check_blue_ghost(void);
void release_blue_ghost_from_the_ghost_house(void);
void leave_house_check_orange_ghost(void);
void releases_orange_ghost_from_the_ghost_house(void);
void check_and_set_difficulty_flags(void);
void state_for_1st_intermission(void);
void pacman_junk0(void);
void TT07_increase_state_in_1st_cutescene(void);
void pacman_junk1(void);
void pacman_junk2(undefined2 param_1);
void pacman_junk4(void);
void pacman_junk5(void);
void pacman_junk6(void);
void state_for_2nd_intermission(void);
void pacman_2nd_intermission_junk0(undefined *param_1);
void pacman_2nd_intermission_junk2(void);
void TT08_increase_state_in_2nd_cutescene(void);
void pacman_2nd_intermission_junk3(void);
void pacman_2nd_intermission_junk4(undefined *param_1);
void pacman_2nd_intermission_junk5(undefined *param_1);
void pacman_2nd_intermission_junk6(undefined *param_1);
void pacman_2nd_intermission_junk7(void);
void pacman_2nd_intermission_junk9(undefined *param_1);
void pacman_2nd_intermission_junk11(void);
void pacman_2nd_intermission_junk13(void);
void state_for_3rd_intermission(void);
void TT09_increase_state_in_3rd_cutescene(void);
void pacman_3rd_intermission_junk0(void);
void pacman_3rd_intermission_junk2(void);
void pacman_3rd_intermission_junk3(void);
void pacman_3rd_intermission_junk4(void);
void startup_test(void);
void execute_CORE_task(void);
void T16_increase_main_subroutine_number(void);
void T00_clear_whole_screen_or_maze(byte param);
void clear_hardware_video_ram(void);
void clear_hardware_video_maze_only(void);
void T06_clears_color_RAM(void);
void T02_draw_maze(void);
void T03_draw_pellets(void);
void T15_update_screen_pill_config_to_video_ram(void);
void T12_clears_pills_and_power_pills_arrays(void);
void T01_select_maze_color(undefined2 param_1);
void T04_reset_sprites_to_default_values(undefined2 param_1);
void T1E_clear_fruit_and_pacman_position(void);
void clear_all_ghost_from_screen(undefined2 param_1);
void T05_reset_ghost_home_counter(undefined2 param_1);
void T07_set_game_to_demo_mode(void);
void T11_clear_full_data_game(void);
void T1F_draw_extra_life_points(void);
void T14_setup_config_from_dip_switches(void);
void T08_red_ghost_AI(void);
void T09_pink_ghost_AI(void);
void T0A_blue_ghost_AI(void);
void T0B_orange_ghost_AI(void);
void T0C_red_ghost_movement_when_power_pill(void);
void T0D_pink_ghost_movement_when_power_pill(void);
void T0E_blue_ghost_movement_when_power_pill(void);
void T0F_orange_ghost_movement_when_power_pill(void);
void T17_pacman_AI_movement_when_demo(void);
character_orientation_e get_best_orientation(character_orientation_e current_orientation,sprite_coord_yx_t ghost_position);
uint3 distance_check(sprite_coord_yx_t current_position_tile,sprite_coord_yx_t destination_tile,character_orientation_e orientation);
word get_distance(sprite_coord_yx_t *ghost_position,sprite_coord_yx_t *pacman_position);
word square(byte value);
byte random(void);
void T13_clears_sprites(void);
void T19_update_score_then_draw(undefined2 param_1);
void draw_player_score_on_screen(byte *param_1);
void draw_score_to_screen(short param_1,byte *param_2);
void draw_digit_to_screen(byte param_1,byte param_2,byte *param_3);
void T18_print_high_score_text_then_players_score(void);
void get_score_from_current_player(void);
void check_for_extra_life(short param_1);
void T1A_draw_remaining_lives_bottom_screen(byte param_1,ushort param_2,undefined *param_3);
void draw_blank_for_next_extra_life(undefined *param_1);
void draw_color_subroutine(undefined param_1,undefined *param_2);
void draw_extra_life(char param_1,char *param_2);
void T1D_draw_credit_qty(undefined param_1);
void colors_the_bottom_two_rows_of_10_the_color_9_yellow(undefined *args);
void T1B_draw_fruits_right_screen(void);
byte FUN_ram_2c44(byte param_1);
void DrawText(byte index);
void backup_sprites__then__check_cocktail_animation_end__then__mspacman_channel_1_song_table(void);
void process_effect_all_voices(void);
byte process_wave_one_voice(undefined ***song_table,sound_channel_16bits_t *sound_channel,wave_t *wave_table);
byte process_effect_one_voice(undefined *effects_table,sound_channel_16bits_t *sound_channel,effect_t *effect);
char wave_init_param(undefined *param_1,short param_2);
byte effect_TYPE0_get_volume(effect_t *effect);
void effect_TYPE1_volume_decrease(effect_t *effect);
void effect_TYPE2_volume_decrease_1_2(effect_t *effect);
void effect_TYPE3_volume_decrease_1_4(effect_t *effect);
void effect_TYPE4_volume_decrease_1_8(effect_t *effect);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void NOP(void);
void wave_cmd0_jmp_offset(wave_t *wave);
void wave_cmd1_wave_select(wave_t *wave);
void wave_cmd2_freq_incr(wave_t *wave);
void wave_cmd3_volume(wave_t *wave);
void wave_cmd4_type(wave_t *wave);
byte wave_cmdF_end_of_song(undefined *param_1,byte *param_2);
void interrupt_vector_pacman_only(void);
void sleep2800(byte watchdog);
void mspacman_state_for_1st_intermission_patch(void);
void mspacman_state_for_2nd_intermission_patch(void);
void mspacman_state_for_3rd_intermission_patch(void);
void demo_mode_move_Blinky_around(void);
void demo_mode_move_Pinky_across(void);
void demo_mode_move_Inky_across(void);
void demo_mode_move_Sue_across(void);
void demo_mode_move_mspacman_across(void);
void intermissions_and_attract_mode_animation_main_routine(byte word_intermission_index);
byte animation_code_f0_loop_sub_stuff(byte param_1);
void generate_animations(byte animation_seek_index);
word animation_code_f0_and_f1_sub_stuff(undefined2 param_1);
void mspacman_select_song(ushort param_1,word *param_2,byte *param_3,short param_4);
void clear_fruit_position(void);
void FUN_ram_367f(void);
void draw_easter_egg__Made_By_Namco(void);
void execute_DEMO_task_state_patch(void);
void demo_mode_display_MS_pacman(void);
void demo_mode_draw_the_midway_logo_and_copyright(void);
void demo_mode_display_Blinky(void);
void demo_mode_clear_with_display_Pinky(char param_1);
void demo_mode_display_Inky(void);
void demo_mode_display_Sue(void);
void demo_mode_display_Ms_pacman(void);
void demo_mode_display_with(void);
void demo_mode_display_Starring(undefined2 param_1);
void demo_mode_start_demo_mode_where_mspacman_plays_herself(void);
void flashing_bulbs_around_the_marquee(void);
void mspac_moving_east(void);
void O01_moving_south(void);
void mspacman_moving_north(void);
void check_for_fruit_to_come_out(void);
void setup_fruit_path(byte *param_1);
byte * get_current_maze_table(void);
void check_if_board_is_cleared(undefined param_1);
byte * get_maze_data_from_current_level(byte *maze_lookup_table);
void mspacman_died_pellet_routine_load(void);
void mspacman_died_pellet_routine_save(void);
void pick_quadrant_for_blue_ghost_direction(void);
undefined2 pick_quadrant_for_orange_ghost_direction(void);
undefined2 pick_quadrant(void);
void T1C_draw_text_or_graphics(byte param);
byte prepare_draw_midway_logo_and_copyright_text(byte param_1);
void prepare_draw_mspacman(void);
void draw_multiple_tile(mspac_graph_t *p_graph_tile);
void prepare_draw_READY(void);
void draw_the_midway_logo_and_copyright(void);
void backup_sprites__then__check_cocktail_animation_end__then__mspacman_channel_1_song_table(void);

