
#ifndef __BODY_GENERATOR_H
#define __BODY_GENERATOR_H

char convert_char(char* content, int contentlength);
int get_array(char input);
int converttobytearray();
int createmessage();
int prepare_body(char* content, int contentlength, int effect_type);
int write_main(int usbdev);
int generate_screen(int charpos, int charlength);
#endif // __BODY_GENERATOR_H
