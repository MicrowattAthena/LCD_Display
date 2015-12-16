#ifndef __COMMAND_GENERATOR_H
#define __COMMAND_GENERATOR_H

int generate_header(int screennumber, int effect_type, int screen_speed, int stay_time, int border_type, int length);
int generate_content(char *content, int length, int effect_type);
int write_content();
int write_header(int usbdev);
int write_footer(int usbdev);


//Screen Numbers (Screen to Change)
#define SCREEN_ONE 0x01
#define SCREEN_TWO 0x02
#define SCREEN_THREE 0x03
#define SCREEN_FOUR 0x04
#define SCREEN_FIVE 0x05
#define SCREEN_SIX 0x06
#define SCREEN_SEVEN 0x07
#define SCREEN_EIGHT 0x08
#define SCREEN_NINE 0x09
#define SCREEN_TEN 0x10

//Effect Types (Effect to Display)
#define EFFECT_AUTO 0x00
#define EFFECT_NONE 0x01

#define EFFECT_MOVE_LEFT_FULL 0x02
#define EFFECT_MOVE_RIGHT_FULL 0x03
#define EFFECT_MOVE_LEFT_SCREEN 0x04
#define EFFECT_MOVE_RIGHT_SCREEN 0x05
#define EFFECT_MOVE_UP 0x08
#define EFFECT_MOVE_DOWN 0x09

#define EFFECT_EXPAND_H_OPEN 0x0A
#define EFFECT_EXPAND_V_OPEN 0x0B
#define EFFECT_EXPAND_H_CLOSE 0x0C
#define EFFECT_EXPAND_V_CLOSE 0x0D

#define EFFECT_FLOAT_BL 0x0E
#define EFFECT_FLOAT_BR 0x0F
#define EFFECT_FLOAT_TL 0x10
#define EFFECT_FLOAT_TR 0x11

#define EFFECT_BLIND_RIGHT 0x12
#define EFFECT_BLIND_LEFT 0x13
#define EFFECT_BLIND_CLOSE 0x14
#define EFFECT_BLIND_UP 0x15
#define EFFECT_BLIND_H_UP 0x16
#define EFFECT_BLIND_h_DOWN 0x17

#define EFFECT_PRINT_FOLLOW 0x1A
#define EFFECT_PRINT_T 0x1B
#define EFFECT_PRINT_B 0x1C
#define EFFECT_PRINT_TL 0x1D
#define EFFECT_PRINT_TR 0x1F
#define EFFECT_PRINT_BR 0x20
#define EFFECT_PRINT_BL 0x21

#define EFFECT_FLASH_SNOW 0x22
#define EFFECT_FLASH_REVERSE 0x23
#define EFFECT_FLASH_ONOFF 0x24
#define EFFECT_FLASH_SHAKE 0x25
#define EFFECT_FLASH_UPSIDEDOWN 0x26
#define EFFECT_FLASH_GRAND 0x27

//SCREEN SPEED (Transition Speed (Higher Numbers Move Slower)
#define SPEED_SIX 0x00 
#define SPEED_FIVE 0x01 
#define SPEED_FOUR 0x02 
#define SPEED_THREE 0x03
#define SPEED_TWO 0x04
#define SPEED_ONE 0x05

//STAY TIME (Time Message stays on screen)
#define STAY_ONE 0x01
#define STAY_TWO 0x02
#define STAY_THREE 0x03
#define STAY_FOUR 0x04
#define STAY_FIVE 0x05
#define STAY_SIX 0x06

//Border Type (Border that appears with message)

#define BORDER_NONE 0x00
#define BORDER_STATIC 0x01
#define BORDER_ROTATE 0x02
#define BORDER_BLINK 0x03
#endif // __COMMAND_GENERATOR_H
