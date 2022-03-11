/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-01 11:56:02
 * @LastEditTime: 2022-03-01 11:56:03
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_app\Version.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef _VERSION_H
#define _VERSION_H

//#define _80C51_MCU

#ifdef __cplusplus
extern "C"
{
#endif

extern char *GetAuther(void);
extern char *GetSystem(void);
extern char *GetCompany(void);
extern char *GetProName(void);
extern char *GetProModel(void);
extern char *GetVersionNum(void);
extern char *GetVersionTime(void);
extern char *GetBoardFeature(void);
extern char *GetBuildedDate(void);
extern char *GetBuildedTime(void);

extern  void version_init(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

