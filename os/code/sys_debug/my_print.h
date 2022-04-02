/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-17 16:09:53
 * @LastEditTime: 2022-03-04 20:52:18
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_debug\my_print.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef __MYPRINT_H
#define __MYPRINT_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define MODULE_PRINT_INFO_EN // 屏蔽不定义 关闭此模块打印信息
#define PRINTF_INFO_EN // 屏蔽关闭命令行及所以模块打印

#ifdef PRINTF_INFO_EN

enum print_level_e {
PRN_CRITICAL   = 0,
PRN_ERROR      = 1,
PRN_WARNING    = 2,
PRN_INFO       = 3,
PRN_DEBUG      = 4,
};

// mcu function address type
typedef	unsigned int PUT_FUNC_T;

#define PRINT_BUF_SIZE 512 // 打印缓存大小

extern void my_print_init(PUT_FUNC_T print_out_func);
extern int  my_print_format(const char *format, ...);
extern void my_print_array(char hex[], int len);
extern void my_print_level(int set_print_level, const int print_level, const char *format, ...);

#ifdef MODULE_PRINT_INFO_EN

#define PRINT(fmt, ...)                    my_print_format(fmt, ##__VA_ARGS__)
#define PRN_HEXS(a,b)                      my_print_array(a,b)

//#    define PRINT_DETAIL_MODE // global detail print message
#    ifdef  PRINT_DETAIL_MODE
#       define PRN_LEVEL(a,b,fmt, ...)     my_print_level(a,b,"%s(%d) %s(): level(%d) #"fmt,__FILE__, __LINE__, __FUNCTION__, b, ##__VA_ARGS__)
#    else
#       define PRN_LEVEL(a,b,fmt, ...)     my_print_level(a,b,fmt, ##__VA_ARGS__)
#    endif

#else

#    ifndef PRINT
#    define PRINT(fmt, ...)             ( (void)0 )
#    endif

#    ifndef PRN_HEXS
#    define PRN_HEXS(a,b)               ( (void)0 )
#    endif

#    ifndef PRN_LEVEL
#    define PRN_LEVEL(a,b,fmt, ...)     ( (void)0 )
#    endif

#endif

#else

#define my_print_init(a)                ( (void)0 )
#define my_print_format(fmt, ...)       ( (void)0 )
#define my_print_array(a,b)             ( (void)0 )
#define my_print_level(a,b,fmt, ...)    ( (void)0 )

#define PRINT(fmt, ...)                 ( (void)0 )
#define PRN_HEXS(a,b)                   ( (void)0 )
#define PRN_LEVEL(a,b,fmt, ...)         ( (void)0 )

#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
