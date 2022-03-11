/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-02 14:07:30
 * @LastEditTime: 2022-03-04 21:45:53
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_bsp\bsp_rtc.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "gd32f30x.h"
#include "my_print.h"
#include "disp.h"
#define	STARTOFTIME		1970				//元年
#define FEBRUARY		2
#define SECDAY			86400L           /*  一天有多少s */
#define SECYR			(SECDAY * 365)
#define	leapyear(year)		((year) % 4 == 0)
#define	days_in_year(a) 	(leapyear(a) ? 366 : 365)
static int month_days[12] = {	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
#define	days_in_month(a) 	(month_days[(a) - 1])
struct rtc_s
{
    int sec;
    int min;
    int hour;
    int day;
    int mon;
    int year;
};
struct rtc_s rtc;
int64_t decode_rtc_cnt(uint32_t cnt)
{
    register uint32_t   i;
    register long       s, day;

    day = cnt / SECDAY;			/* 有多少天 */
    s   = cnt % SECDAY;			/* 今天的时间，单位s */

    /* Hours, minutes, seconds are easy */
    rtc.hour = s / 3600;
    rtc.min = (s % 3600) / 60;
    rtc.sec = (s % 3600) % 60;

    /* Number of years in days */ /*算出当前年份，起始的计数年份为1970年*/
    for (i = STARTOFTIME; day >= days_in_year(i); i++)
    {
        day -= days_in_year(i);
    }
    rtc.year = i;

    /* Number of months in days left */ /*计算当前的月份*/
    if (leapyear(rtc.year))
    {
        days_in_month(FEBRUARY) = 29;
    }
    for (i = 1; day >= days_in_month(i); i++)
    {
        day -= days_in_month(i);
    }
    days_in_month(FEBRUARY) = 28;
    rtc.mon = i;

    /* Days are what is left over (+1) from all that. *//*计算当前日期*/
    rtc.day = day + 1;
    return rtc.sec+rtc.min*100+rtc.hour*10000+rtc.day*1000000+rtc.mon*100000000+rtc.year*10000000000;
}

/* Converts Gregorian date to seconds since 1970-01-01 00:00:00.
 * Assumes input in normal date format, i.e. 1980-12-31 23:59:59
 * => year=1980, mon=12, day=31, hour=23, min=59, sec=59.
 *
 * [For the Julian calendar (which was used in Russia before 1917,
 * Britain & colonies before 1752, anywhere else before 1582,
 * and is still in use by some communities) leave out the
 * -year/100+year/400 terms, and add 10.]
 *
 * This algorithm was first published by Gauss (I think).
 *
 * WARNING: this function will overflow on 2106-02-07 06:28:16 on
 * machines were long is 32-bit! (However, as time_t is signed, we
 * will already get problems at other places on 2038-01-19 03:14:08)
 *
 */
uint32_t encoding_rtc(int64_t time)
{
    register uint32_t   i;
    register long       s;
    register long       day = 0;
    rtc.sec = time%100;
    rtc.min = time/100%100;
    rtc.hour = time/10000%100;
    rtc.day = time/1000000%100;
    rtc.mon = time/100000000%100;
    rtc.year = time/10000000000;

    /* Number of years in days */ /*算出当前年份，起始的计数年份为1970年*/
    for (i = STARTOFTIME; i<rtc.year; i++)
    {
        day += days_in_year(i);
    }
    if (leapyear(rtc.year))
    {
        days_in_month(FEBRUARY) = 29;
    }
    for (i = 1; i<rtc.mon; i++)
    {
        day += days_in_month(i);
    }
    days_in_month(FEBRUARY) = 28;
		day += rtc.day-1;
    /* Days are what is left over (+1) from all that. *//*计算当前日期*/
    return rtc.sec+rtc.min*60+rtc.hour*60*60+day*SECDAY;
}    

void rtc_configuration(void)
{
    /* enable PMU and BKPI clocks */
    rcu_periph_clock_enable(RCU_BKPI);
    rcu_periph_clock_enable(RCU_PMU);
    /* allow access to BKP domain */
    pmu_backup_write_enable();

    /* reset backup domain */
    bkp_deinit();

    /* enable LXTAL */
    rcu_osci_on(RCU_LXTAL);
    /* wait till LXTAL is ready */
    rcu_osci_stab_wait(RCU_LXTAL);
    
    /* select RCU_LXTAL as RTC clock source */
    rcu_rtc_clock_config(RCU_RTCSRC_LXTAL);

    /* enable RTC Clock */
    rcu_periph_clock_enable(RCU_RTC);

    /* wait for RTC registers synchronization */
    rtc_register_sync_wait();

    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();

    // /* enable the RTC second interrupt*/
    rtc_interrupt_enable(RTC_INT_SECOND);
    // rtc_interrupt_enable(RTC_INT_ALARM);
    // /* wait until last write operation on RTC registers has finished */
    // rtc_lwoff_wait();

    /* set RTC prescaler: set RTC period to 1s */
    rtc_prescaler_set(32767);

    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();
}
void time_adjust(void)
{
    uint32_t temp = 0;
    /* wait until last write operation on RTC registers has finished */
    rtc_lwoff_wait();
    temp = encoding_rtc(20220304000000);
    /* change the current time */
    rtc_counter_set(temp);
    rtc_lwoff_wait();
    /* set the alarm time = currenttime + 10 second*/
    //rtc_alarm_config((temp+10)%0x00015180);
    //printf("\r\n Set Alarm");
    //time_display((temp+10)%0x00015180);
    /* wait until last write operation on RTC registers has finished */
    //rtc_lwoff_wait();
}
void rtc_init()
{
    if (bkp_read_data(BKP_DATA_0) != 0xA5A5){
        /* backup data register value is not correct or not yet programmed
        (when the first time the program is executed) */
        //printf("\r\nThis is a RTC demo!\r\n");
        //printf("\r\n\n RTC not yet configured....");

        /* RTC configuration */
        rtc_configuration();

        PRINT("\r\n RTC configured....");

        /* adjust time by values entred by the user on the hyperterminal */
        time_adjust();

        bkp_write_data(BKP_DATA_0, 0xA5A5);
    }else{
        /* check if the power on reset flag is set */
        if (rcu_flag_get(RCU_FLAG_PORRST) != RESET){
            PRINT("\r\n\n Power On Reset occurred....");
        }else if (rcu_flag_get(RCU_FLAG_SWRST) != RESET){
            /* check if the pin reset flag is set */
            PRINT("\r\n\n External Reset occurred....");
        }

        /* allow access to BKP domain */
        rcu_periph_clock_enable(RCU_PMU);
        pmu_backup_write_enable();

        PRINT("\r\n No need to configure RTC....");
        /* wait for RTC registers synchronization */
        rtc_register_sync_wait();
        rtc_lwoff_wait();
        /* enable the RTC second */
        rtc_interrupt_enable(RTC_INT_SECOND);
        //rtc_interrupt_enable(RTC_INT_ALARM);
        /* wait until last write operation on RTC registers has finished */
        rtc_lwoff_wait();
    }
    nvic_irq_enable(RTC_IRQn,1,0);
}


void RTC_IRQHandler(void)
{
    if (rtc_flag_get(RTC_FLAG_SECOND) != RESET){
        /* clear the RTC second interrupt flag*/
        rtc_flag_clear(RTC_FLAG_SECOND);    
        /* enable time update */
        time.data = decode_rtc_cnt(rtc_counter_get());
    }
}
