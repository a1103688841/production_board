/************************************************** 
 * @Author: shuren
 * @Date: 2022-03-03 10:15:08
 * @LastEditTime: 2022-03-03 10:41:05
 * @LastEditors: shuren
 * @Description: 
 * @FilePath: \code\sys_app\my_link.c
 * @桃之夭夭，灼灼其华。之子于归， 宜其室家。
 **************************************************/
#include "base_typle.h"
#include "my_link.h"
#include "my_print.h"
#ifndef PRINT
    #define PRINT (void)0
#endif
/**************************************************************************************************
*	 汇总
* 1）打印函数
* 2）内部操作函数（都含头结点）
* 3）高级函数	（都含头结点）
* 4) 使用示例（20200601版本未更新）
**************************************************************************************************
*1） 打印函数
**************************************************************************************************/
linkStatus LinkPoint_Visit(ElemType c)
{
	PRINT("%s(%d):this data is:%f\n",__MODULE__,__LINE__,c);
	return TRUE;
}
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
linkStatus LinkPoint_PrintTraverse(LinkPoint L)
{
	LinkPoint p = L->next;
	while (p)
	{
		LinkPointVisit(p->data);
		p = p->next;
	}
	return TRUE;
}
void LinkPoint_PrintInversion(LinkPoint *L)
{
	if (L == NULL)
	{
		return;
	}
	LinkPointReverse((*L)->next);
	LinkPointVisit((*L)->data);
}

/**************************************************************************************************
*2） 内部操作函数，这个头结点是哨兵
**************************************************************************************************/
/* 初始化顺序线性表 */
//用链表的头结点指针过来就可以了，初始化帮忙申请一个实体的变量
linkStatus LinkPoint_Init(LinkPoint* L)
{
	//申请空间
	*L = (LinkPoint)malloc(sizeof(LinkPointLinkNode)); /* 产生头结点,并使L指向此头结点 */
	if (!(*L)) 							/* 存储分配失败 */
	{	
		return FALSE;
	}
	//初始化
	(*L)->next = NULL; /* 指针域为空 */

	return TRUE;
}
linkStatus LinkPoint_InitManu(LinkPoint* L)
{
	(*L)->next = NULL; /* 指针域为空 */
	return TRUE;
}
/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void linkLis_RandInit_Head(LinkPoint* L, int n)
{
	LinkPoint p;
	int i;
	srand(time(0));                         	/* 初始化随机数种子 */
	*L = (LinkPoint)malloc(sizeof(LinkNode));
	(*L)->next = NULL;                     	 	/*  先建立一个带头结点的单链表 */
	for (i = 0; i < n; i++)
	{
		p = (LinkPoint)malloc(sizeof(LinkNode)); 	/*  生成新结点 */
		p->data = rand() % 100 + 1;             /*  随机生成100以内的数字 */
		p->next = (*L)->next;
		(*L)->next = p;							/*  插入到表头 */
	}
}
/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void LinkPoint_RandomInit_Tail(LinkPoint* L, int n)
{
	LinkPoint p, r;
	int i;
	srand(time(0));                      /* 初始化随机数种子 */
	*L = (LinkPoint)malloc(sizeof(LinkNode)); /* L为整个线性表 */
	r = *L;                                /* r为指向尾部的结点 */
	for (i = 0; i < n; i++)
	{
		p = (LinkNode*)malloc(sizeof(LinkNode)); /*  生成新结点 */
		p->data = rand() % 100 + 1;           /*  随机生成100以内的数字 */
		r->next = p;                        /* 将表尾终端结点的指针指向新结点 */
		r = p;                            /* 将当前的新结点定义为表尾终端结点 */
	}
	r->next = NULL;                       /* 表示当前链表结束 */
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
linkStatus LinkPointEmpty(LinkPoint L)
{
	if (L->next)
		return FALSE;
	else
		return TRUE;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
//输入的是链表头节点
linkStatus LinkPointClear(LinkPoint* L)
{
	LinkPoint p, q;
	//p指向第一个结点 
	p = (*L)->next; 
	//没到表尾         
	while (p)                
	{
		//释放后面链表的空间
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;        /* 头结点指针域为空 */
	return TRUE;
}
linkStatus LinkPointClearManu(LinkPoint* L)
{
	(*L)->next = NULL;
	return TRUE;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int16_t LinkPointLength(LinkPoint L)
{
	int i = 0;
	LinkPoint p = L->next; /* p指向第一个结点 */
	while (p)
	{
		i++;
		p = p->next;
	}
	return i;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
linkStatus LinkPointGetElem(LinkPoint L, int i, ElemType* e)
{
	int j;
	LinkPoint p;			/* 声明一结点p */
	p = L->next;		/* 让p指向链表L的第一个结点 */
	j = 1;				/*  j为计数器 */
	while (p && j < i)  /* p不为空或者计数器j还没有等于i时，循环继续 */
	{
		p = p->next;  	/* 让p指向下一个结点 */
		++j;
	}
	if (!p || j > i)
	{
		return FALSE;  /*  第i个元素不存在 */
	}
	*e = p->data;   	/*  取第i个元素的数据 */
	return TRUE;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int16_t LinkPointLocateElem(LinkPoint L, ElemType e)
{
	int i = 0;
	//扫描
	LinkPoint p = L->next;
	while (p)
	{
		i++;
		if (p->data == e) /* 找到这样的数据元素 */
			return i;
		p = p->next;
	}

	return 0;
}


/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
linkStatus LinkPointInsert(LinkPoint* L, int i, ElemType e)
{
	int j;
	//p是扫描指针，S是操作指针
	LinkPoint p, s;
	//扫描
	p = *L;
	j = 1;
	while (p && j < i)    	 			/* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return FALSE;   				/* 第i个元素不存在 */
	//插入
	s = (LinkPoint)malloc(sizeof(LinkNode));  /*  生成新结点(C语言标准函数) */
	s->data = e;
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
	return TRUE;
}
linkStatus LinkPointInsertManu(LinkPoint* L, LinkPoint* node,int i, ElemType e)
{
	int j;
	LinkPoint p, s;
	p = *L;
	//防止新加的节点已经是链表中的一个节点
	while (p)						
	{
		if (p == *node)
		{
			return FALSE;
		}
		p = p->next;
	}
	p = *L;
	j = 1;
	while (p && j < i)    	 			/* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
	{
		return FALSE;   				/* 第i个元素不存在 */

	}
	s = *node;  			/*  生成新结点(用已经申请好的节点) */
	s->data = e;
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          	/* 将s赋值给p的后继 */
	return TRUE;
}


/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
linkStatus LinkPointDelete(LinkPoint* L, int i, ElemType* e)
{
	int j;
	//p是遍历指针，q是操作指针既删除指针
	LinkPoint p, q;
	//遍历
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)
		return FALSE;           /* 第i个元素不存在 */
	//删除
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	return TRUE;
}
linkStatus LinkPointDeleteManu(LinkPoint* L, int i, ElemType* e)
{
	int j;
	//p是遍历指针，q是操作指针既删除指针
	LinkPoint p, q;
	//遍历
	p = *L;
	j = 1;
	while (p->next && j < i)	/* 遍历寻找第i个元素 */
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i)
		return FALSE;           /* 第i个元素不存在 */
	//删除
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */
	*e = q->data;               /* 将q结点中的数据给e */
	q->next = NULL;             /* 手动申请的节点系统不回收 */
	return TRUE;
}
/**************************************************************************************************
*3） 高级操作函数，默认使用free和malloc来操作变量
**************************************************************************************************
* 函数:                                   LinkPointDelx
* 说明:  	删除拥有头结点的单链表中所有的等于x的结点
* 输入:  
*		   LinkPoint *L		
*		int x		
* 关联变量: 
* 返回:  
* 作者:  日南方  6/20/2020
**************************************************************************************************/
void LinkPointDelx(LinkPoint* L, int x)
{
	//头结点后的第一个节点
	LinkPoint p = (*L)->next;
	LinkPointDelxRecursion(p,x);
}
void LinkPointDelxRecursion(LinkPoint* L, int x)
{
	LinkPoint temp;
	if (L == NULL)
	{
		return;
	}
	if(L->data == x)
	{
		temp = L->next;
		*L = *(L->next);
		free(temp);
		//temp->next = NULL;  //手动申请变量不回收
		LinkPointDelxRecursion(L, x);
	}else{
	 	LinkPointDelxRecursion(L->next, x);
	}
}	
void LinkPointDelx1(LinkPoint *L, int x)
{
	//now是扫描节点
	//prev是now的前驱节点
	//temp辅助删除操作
	LinkPoint prev, now, temp;
	prev = (*L);
	now  = prev->next;
	
	while (now != NULL)
	{
		if (now->data == x)
		{
			//删除，并切下一个节点
			temp = now;
			now = now->next;
			prev->next = now;
			free(temp);
			//temp->next = NULL; 	//手动申请变量不回收
		}else{
			//下一个节点
			prev = now;
			now  = now->next;
		}
	}
}

/**************************************************************************************************
* 函数:                                   del_minx_slList
* 说明:  	删除单链表中最小值，只删除一个，含头结点
* 输入:  
*		   LinkPoint *L		
* 关联变量: 
* 返回:  
* 作者:  日南方  6/20/2020
**************************************************************************************************/
LinkPoint LinkPointDelMin(LinkPoint *L)
{
	//now是扫描节点,temp是最小的保存节点
	//prev是now的前驱节点,temp_prev是temp的前驱节点
	LinkPoint *prev, *now, *temp, *temp_prev;
	//含头结点的初始化
	prev = temp_prev = L; 
	now = temp =(*L)->next;
	while(now != NULL)
	{
		//保存最小值的节点
		if((*now)->data <= (*temp)->data)
		{
			temp = now;
			temp_prev = prev;
		}
		//扫描
		prev = now;
		now = (*now)->next;
	}
	//删除
	(*temp_prev)->next = (*temp)->next;
	free(temp);
	//temp->next = NULL;
	return L;
}
/**************************************************************************************************
* 函数:                                   LinkPointInversion
* 说明:  	逆序单链表，使用头插法改变顺序
* 输入:  
*		   LinkPoint * L		
* 关联变量: 
* 返回:  
* 作者:  日南方  6/20/2020
**************************************************************************************************/
LinkPoint LinkPointInversion(LinkPoint * L)
{
	//head是头结点,now是扫描节点,temp是取扫描过的节点
	LinkPoint *head, *now, *temp;
	//把头结点空出来
	head = L;
	(*head)->next = NULL;
	//now是扫描指针，temp是取出扫描过的节点
	now  = (*L)->next;
	while (now != NULL)
	{	
		temp = now;
		now = (*now)->next;
		//头插法，来进行逆序
		(*temp)->next = (*head)->next;
		(*head)->next = temp;
	}
	return head;
}
/**************************************************************************************************
* 函数:                                   LinkPointDelMin2Max
* 说明:  
* 输入:  
*		   LinkPoint *L		
*		int min		
*		int max		
* 关联变量: 
* 返回:  
* 作者:  日南方  10/20/2020
**************************************************************************************************/
void LinkPointDelMin2Max(LinkPoint *L, int min, int max)
{
	//now是扫描指针，prev是now的前驱
	LinkPoint *prev, *now;
	//含头结点，now指向第一个节点
	prev = L;
	now = (*L)->next;
	//扫描
	while (now != NULL)
	{
		//满足条件，删除，并切下一个节点
		if(min<(*now)->data && (*now)->data<max)
		{
			(*prev)->next = (*now)->next;
			free(now);
			//now->next =NULL;
			now = (*prev)->next;
		}else{
		//不满足,切下一个节点
			prev = now;
			now = (*now)->next;
		}
	}
}