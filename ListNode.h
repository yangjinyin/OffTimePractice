#include <iostream>

using namespace std;
#pragma once;
struct ListNode
{
	int m_nKey;
	ListNode* m_pNext;
};

void Insert(ListNode*& head,int x)
{
	ListNode* p = new ListNode();
	p->m_nKey = x;
	p->m_pNext = NULL;
	if(head==NULL)
	{
		head = p;
	}
	else
	{
		ListNode* tmp = head;
		while(tmp->m_pNext!=NULL)
			tmp = tmp->m_pNext;
		tmp->m_pNext = p;
	}
}

void deleteList(ListNode*& head,int x)
{
	
}

ListNode* ReverseList(ListNode* phead)
{
	//way 1
	//ListNode* p1=phead;
	//if(p1->m_pNext == NULL || p1 == NULL)
	//	return p1;
	//p1 = p1->m_pNext;
	//while(p1->m_pNext)
	//{
	//	ListNode* p2 = p1->m_pNext;
	//	p1->m_pNext = p2->m_pNext;
	//	p2->m_pNext = phead->m_pNext;
	//	phead->m_pNext = p2;		
	//}
	//p1->m_pNext = phead;
	//phead = p1->m_pNext->m_pNext;
	//p1->m_pNext->m_pNext=NULL;     //断掉环   
	//return phead;  

	// way 2
	//ListNode * p1;
	//ListNode*  p2;
	//ListNode* p3;
	//if(phead == NULL ||phead->m_pNext == NULL)
	//	return phead;
	//p1 = phead;
	//p2 = p1->m_pNext;
	//while(p2)
	//{
	//	p3 = p2->m_pNext; //保存下一个节点防止断了；
	//	
	//	p2->m_pNext = p1;

	//	p1= p2;
	//	p2 = p3;

	//}
	//phead = p1;
	//return phead;

	//way3 recursive
	if(phead == NULL || phead->m_pNext == NULL)
		return phead;
	ListNode *p = ReverseList(phead->m_pNext);
	ListNode *pnext = phead->m_pNext;
	pnext->m_pNext = phead;
	phead->m_pNext = NULL;
	
	return p;
}

ListNode* merge(ListNode* pHead1,ListNode*pHead2)
{
	if(pHead1==NULL)
		return pHead2;
	if(pHead2==NULL)
		return pHead1;

	ListNode* pNew = NULL;
	
	if(pHead1->m_nKey < pHead2->m_nKey)
	{
		pNew = pHead1;
		pHead1 = pHead1->m_pNext;
	}
	else
	{
		pNew = pHead2;
		pHead2 = pHead2->m_pNext;
		
	}
	ListNode* tmp = pNew;
	while(pHead1 && pHead2)
	{
		if(pHead1->m_nKey < pHead2->m_nKey)
		{
			tmp->m_pNext = pHead1;
			pHead1 = pHead1->m_pNext;
		}
		else
		{
			tmp->m_pNext = pHead2;
			pHead2 = pHead2->m_pNext;

		}
		tmp = tmp->m_pNext;
	}

	while(pHead1)
	{
		tmp->m_pNext = pHead1;
		tmp = tmp->m_pNext;
		pHead1 = pHead1->m_pNext;
	}
	while(pHead1)
	{
		tmp->m_pNext = pHead2;
		tmp = tmp->m_pNext;
		pHead2 = pHead2->m_pNext;
	}
	return pNew;
}

