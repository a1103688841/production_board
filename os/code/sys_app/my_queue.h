/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-27 17:38:19
 * @LastEditTime: 2022-02-27 20:14:05
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_app\my_queue.h
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#ifndef _MY_QUEUE_H
#define _MY_QUEUE_H

#ifdef __cplusplus
extern "C"
{
#endif

struct queue_s {
    char *  buff;
    unsigned int front;
    unsigned int rear;
    unsigned int max;
};

extern void init_queue(struct queue_s *queue_name);
extern void init_queue(struct queue_s *q);
extern void clear_queue(struct queue_s *q);
extern char is_queue_empty(struct queue_s *q);
extern char is_queue_full(struct queue_s *q);
extern char deQueue(struct queue_s *q, char *data);
extern char enQueue(struct queue_s *q, char data);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
