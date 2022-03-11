/************************************************** 
 * @Author: shuren
 * @Date: 2022-02-27 17:38:19
 * @LastEditTime: 2022-03-03 10:28:06
 * @LastEditors: shuren
 * @Description: UTF8
 * @FilePath: \code\sys_app\my_queue.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "my_queue.h"

void init_queue(struct queue_s *q)
{
    q->front = 0;
    q->rear  = 0;
}
void clear_queue(struct queue_s *q)
{
    q->front=0;
    q->rear=0;
}
/* rear == front  is empty */
char is_queue_empty(struct queue_s *q)
{
    return (q->front == q->rear) ? (TRUE) : (FALSE);
}

/* (rear + 1) == front  is full*/
char is_queue_full(struct queue_s *q)
{
    //return ((q->rear+1)%q->max == q->front)? (TRUE) : (FALSE);
    unsigned int p;
    p = q->rear+1;
    if(p >= q->max) p=0;
    if(p == q->front){
        return TRUE;
    }else{
        return FALSE;
    }
}

char deQueue(struct queue_s *q, char *data)
{
    if (is_queue_empty(q) == TRUE) return FALSE;
    *data = q->buff[q->front];
    //q->front=(q->front+1)%q->max;
    q->front++;
    if(q->front >= q->max) q->front=0;
    return TRUE;
}
char enQueue(struct queue_s *q, char data)
{
    if (is_queue_full(q) == TRUE) return FALSE;
    q->buff[q->rear] = data;
    //q->rear=(q->rear+1)%q->max;
    q->rear++;
    if(q->rear >= q->max) q->rear=0;
    return TRUE;
}
