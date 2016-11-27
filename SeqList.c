#define  _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;
typedef struct Node
{
	datatype id;		//数据域
	struct Node *next;	//指针域
}SLIST;

/*
功能：	创建链表，并赋值当输入id为-1，退出循环
返回值：成功：返回链表的头结点地址
		失败返回NULL
*/
SLIST *SListCreat() 
{
	/*
	SLIST *pCur = NULL;		//当前节点
	SLIST *pNew = NULL;		//新节点
	*/
	SLIST *pHead = NULL;	//头结点
	//头结点，只是作为标志使用，不保存有效数据
	pHead = (SLIST *)malloc(sizeof(SLIST));
	if (pHead == NULL)
	{
		return NULL;
	}
	pHead->id = -1;
	pHead->next = NULL;
/*
	//pHead成员变量赋值，数据域任意即可，后面用不上
	
	

	//保存当前节点
	//指针指向谁，就把谁的地址赋值给指针
	pCur = pHead;

	datatype data;

	//循环创建结点，结点数据域中的数值从键盘输入，以-1作为输入结束标志
	while (1)
	{
		printf("请输入数据：");
		scanf("%d", &data); 

		if (data == -1)
		{//输入-1，退出循环
			break;
		}

		//新节点分配空间
		pNew = (SLIST *)malloc(sizeof(SLIST));
		if (pNew == NULL)
		{//如果没有分配成功，跳出本次循环
			continue;
		}

		//pNew成员变量赋值
		pNew->id = data;

		//当前节点next指向新节点
		pCur->next = pNew;

		//新节点的next指向NULL
		pNew->next = NULL;

		//当前节点的位置移动到新节点的位置（pCur指向pNew）
		pCur = pNew;
	}
*/
	
	//链表的头结点地址由函数值返回。
	return pHead;
}


/*
功能：	遍历节点，输出单链表中的内容
参数：	传入一个链表头节点
返回值：成功0，失败-1
*/
int SListPrint(SLIST *pHead)
{
	if (pHead == NULL)
	{
		return -1;
	}

	//保存头结点的下一个节点
	//因为头结点不是有效数据节点，下一个节点才是有效数据的结点
	SLIST *pCur = pHead->next;

	printf("head -> ");
	while (pCur != NULL)
	{
		printf("%d -> ", pCur->id);

		//节点往后移动，当前节点指向下一个节点
		pCur = pCur->next;
	}
	printf("NULL\n");

	return 0;
}


/*
功能：	链表节点排序
参数：	传入一个链表头节点pHead
返回值：成功0，失败-1
*/
int SListSort(const SLIST *pHead)
{
	if (pHead == NULL || pHead->next == NULL)
	{
		return -1;
	}

	SLIST *pPre = NULL;
	SLIST *pCur = NULL; 
	SLIST tmp; //临时交换变量
	
	//选择法排序
	for (pPre = pHead->next; pPre->next != NULL; pPre = pPre->next)
	{
		for (pCur = pPre->next; pCur != NULL; pCur = pCur->next)
		{
			if (pPre->id > pCur->id) //升序
			{
				//交换数据域
				tmp = *pCur;
				*pCur = *pPre;
				*pPre = tmp;

				//交换指针域（重要）
				tmp.next = pCur->next;
				pCur->next = pPre->next;
				pPre->next = tmp.next;
			}
		}
	}
	
	return 0;
}

/*
功能：	在值为x的结点前，插入值为y的结点,若值为x的结点不存在，则插在表尾
参数：	传入一个链表头节点pHead,传入x值，传入y值
返回值：成功0，失败非0
*/
int SListInsert(SLIST *pHead, const datatype x, const datatype y)
{
	if (pHead == NULL)
	{
		return -1;
	}

	SLIST *pPre = pHead;		//上一个节点
	SLIST *pCur = pHead->next;	//当前节点
	SLIST *pNew = NULL;         //新节点

	while (pCur != NULL)
	{
		//如果当前节点数据域等于x，跳出循环
		if (pCur->id == x)
		{
			break;
		}

		//保存当前节点
		//pPre = pCur;
		pPre = pPre->next;

		//当前节点往后移动，当前节点指向下一个节点
		//pPre和pCur相差一个节点，pPre为上一个节点，pCur为当前节点
		pCur = pCur->next;
	}
	
	//新节点分配空间
	pNew = (SLIST *)malloc(sizeof(SLIST));
	if (pNew == NULL)
	{
		return -2;
	}

	//pNew成员变量赋值
	pNew->id = y;

	//pPre的next指向pNew
	pPre->next = pNew;

	//pNew的next指向pCur
	pNew->next = pCur;

	return 0;
}

/*
功能：	在第一个有效节点的前面增加一个节点
参数：	传入一个链表头节点pHead,传入x值
返回值：成功0，失败非0
*/
int  SListInsertTop(SLIST *pHead, const datatype x)
{
	if (pHead == NULL)
	{
		return -1;
	}

	//保存第一个有效节点
	SLIST *cur = pHead->next;

	//创建新节点
	SLIST *pNew = (SLIST *)malloc(sizeof(SLIST));
	pNew->id = x;

	//建立关系
	//头结点的next指向新节点
	pHead->next = pNew;

	//新节点的next指向cur
	pNew->next = cur;
	
	return 0;

}

/*
功能：	在第一个有效节点的前面增加一个节点
参数：	传入一个链表头节点pHead,传入x值
返回值：成功0，失败-1
*/
int  SListInsertTail(SLIST *head, const datatype x)
{
	if (head == NULL)
	{
		return -1;
	}
	
	SLIST *cur = head;
	
	//先找最后一个有效节点
	while (cur->next != NULL)
	{
		//节点往后移动
		cur = cur->next;
	}

	//创建新节点
	SLIST *pNew = (SLIST *)malloc(sizeof(SLIST));
	pNew->id = x;

	//尾结点的next指向新节点
	cur->next = pNew;

	//新节点的next指向NULL
	pNew->next = NULL;
	
	return 0;
}

/*
功能：	假如原来链表是升序的,升序插入新节点
参数：	传入一个链表头节点pHead，x值
返回值：成功0，失败非0
*/
int SListInsertPro(SLIST *pHead, const datatype x)
{
	//先排序，保证原来链表是升序的
	int ret = SListSort(pHead);
	if (ret != 0)
	{
		return ret;
	}

	SLIST *pPre = pHead;		//上一个节点
	SLIST *pCur = pHead->next;	//当前节点

	while (pCur != NULL)
	{
		//找插入点
		if (pCur->id >= x)
		{
			break;
		}

		//保存当前节点
		pPre = pCur;

		//当前节点往后移动，当前节点指向下一个节点
		//pPre和pCur相差一个节点，pPre为上一个节点，pCur为当前节点
		pCur = pCur->next;
	}

	//新节点分配空间
	SLIST *pNew = (SLIST *)malloc(sizeof(SLIST));
	if (pNew == NULL)
	{
		return -2;
	}

	//pNew成员变量赋值
	pNew->id = x;

	//pPre的next指向pNew
	pPre->next = pNew;

	//pNew的next指向pCur
	pNew->next = pCur;

	return 0;
}

/*
功能：	删除第一个值为x的结点
参数：	传入一个链表头节点pHead,传入x值
返回值：成功0，没有值为x的节点返回-2，失败非-1
*/
int SListDel(SLIST *pHead, const datatype x)
{
	if (pHead == NULL)
	{
		return -1;
	}

	SLIST *pPre = pHead;		//上一个节点
	SLIST *pCur = pHead->next;	//当前节点
	int flag = 0; //标志位，0代表没有值为x的结点，1代表有

	while (pCur != NULL)
	{
		if (pCur->id == x)
		{
			//上一个节点指向当前节点的下一个节点
			pPre->next = pCur->next;

			//临时释放节点
			free(pCur);
			pCur = NULL;

			//标志位，0代表没有值为x的结点，1代表有
			flag = 1;

			//跳出循环
			break;
		}

		//保存当前节点
		pPre = pCur;

		//当前节点往后移动，当前节点指向下一个节点
		//pPre和pCur相差一个节点，pPre为上一个节点，pCur为当前节点
		pCur = pCur->next;
	}


	if (flag == 0)
	{ //标志位，0代表没有值为x的结点，1代表有
		return -2;
	}

	return 0;
}

/*
功能：	删除值为x的所有结点
参数：	传入一个链表头节点pHead,传入x值
返回值：成功0，失败-1
*/
int SListDelPro(SLIST *pHead, const datatype x)
{
	if (pHead == NULL)
	{
		return -1;
	}
	
	int ret = 0;
	while(1)
	{
		ret = SListDel(pHead, x);
		if(ret == -2)
			break;
	}
	
	return 0;
}

/*
功能：	翻转链表的节点（不是排序，是翻转）
参数：	传入一个链表头节点pHead
返回值：成功0，失败-1
*/
int SListReverse(SLIST *pHead)
{
	if (pHead == NULL || pHead->next == NULL || pHead->next->next == NULL)
	{
		return -1;
	}

	//上一个节点
	SLIST *pPre = pHead->next;

	//当前节点，pCur和pPre相差一个节点
	SLIST *pCur = pPre->next; //pHead->next->next

	SLIST *pTmp = NULL; //临时节点

	while (pCur != NULL)
	{
		//先保存pCur的下一个节点
		pTmp = pCur->next;

		//原来： pPre->next = pCur
		//翻转： pCur->next = pPre
		//pCur的next指向pPre
		pCur->next = pPre;

		//pPre往后移动一个节点，pPre指向pCur
		pPre = pCur;

		//pCur往后移动一个节点，pCur指向pTmp
		pCur = pTmp;
	}

	//确定头结点和尾结点
	//程序执行到这，说明pCur为NULL，pPre为最后一个有效节点
	//而翻转后，pPre为头结点指向的第一个有效节点

	//先确定翻转后的尾结点
	pHead->next->next = NULL;

	//在确定头结点
	pHead->next = pPre;

	return 0;
}

//释放所有节点
int SListDestroy(SLIST *pHead)
{
	if (pHead == NULL)
	{
		return -1;
	}

	SLIST *pTmp = NULL;	//临时释放节点

	while (pHead != NULL)
	{
		//临时释放节点
		pTmp = pHead;

		//头结点指向头结点next节点
		pHead = pHead->next;
		
		free(pTmp);
		pTmp = NULL;

	}

	return 0;
}

/*
int main()
{
	SLIST *pHead = NULL;

	pHead = SListCreat(); //创建头结点
	printf("\n创建头结点后\n");
	SListPrint(pHead); //遍历所有节点
	
	SListDelPro(pHead, 4);//删除所有值为4的结点
	printf("\n删除所有值为4的结点\n");
	SListPrint(pHead); //遍历所有节点
	
	SListInsertTail(pHead,9);
	SListInsertTop(pHead,8);

	SListSort(pHead);//链表节点排序
	printf("\n链表节点排序\n");
	SListPrint(pHead); //遍历所有节点

	SListInsertPro(pHead, 5);//升序插入5
	printf("\n升序插入5后\n");
	SListPrint(pHead); //遍历所有节点

	//翻转链表的节点（不是排序，是翻转）
	SListReverse(pHead);
	printf("\n翻转链表的节点\n");
	SListPrint(pHead); //遍历所有节点

	SListDestroy(pHead);//释放所有节点
	pHead = NULL;

	printf("\n");
	system("pause");
	return 0;
}
*/
