/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-17 16:09:53
 * @LastEditTime: 2022-02-27 19:56:56
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_debug\myprint.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "my_print.h"

#ifdef PRINTF_INFO_EN

typedef bool (*print_func)(char);

struct my_print_cfg_s {
    char  print_buf[PRINT_BUF_SIZE];       //格式打印缓存地址
    print_func print_out;
};
struct my_print_cfg_s my_print_cfg;

void my_print_init(PUT_FUNC_T print_out_func)
{
    my_print_cfg.print_out = (print_func)print_out_func;
}

void my_print_string(const char str[])
{
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        my_print_cfg.print_out(str[i]);
    }
}

int my_print_format(const char *format, ...)
{
    int str_len;
    va_list arg_ptr;
    va_start (arg_ptr, format);           /* format string */
    str_len = vsnprintf (my_print_cfg.print_buf, PRINT_BUF_SIZE, format, arg_ptr);
    va_end (arg_ptr);
    my_print_string(my_print_cfg.print_buf);
    if (str_len > PRINT_BUF_SIZE) {
        my_print_string("\r\nstr len > print buf size\r\n");
    }
    return str_len;
}

void my_print_array(char array[], int len)
{
    my_print_string("\r\n");
    my_print_string("     00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
    for (int i = 0; i < len; i ++) {
        if ( i % 16 == 0 ) {
            my_print_format("\r\n0x%0.2X:", i);
        }
        my_print_format("%0.2X ",(unsigned char)array[i]);
    }
    my_print_string("\r\n");
}

void my_print_level(int set_print_level, const int print_level, const char *format, ...)
{
    if (print_level <= set_print_level) {
        int str_len;
        va_list arg_ptr;
        va_start (arg_ptr, format);
        str_len = vsnprintf(my_print_cfg.print_buf, PRINT_BUF_SIZE, format, arg_ptr);
        va_end (arg_ptr);
        my_print_string(my_print_cfg.print_buf);
        if (str_len > PRINT_BUF_SIZE) {
            my_print_string("\r\nstr len > print buf size\r\n");
        }
    }
}

#endif
