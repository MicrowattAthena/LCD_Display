#ifndef __COMMAND_GENERATOR_H
#define __COMMAND_GENERATOR_H

int generate_header(char screennumber, char effect_type, char screen_speed, char stay_time, char border_type, int length);
int generate_content(char *content, int length);
int write_content();


#endif // __COMMAND_GENERATOR_H
