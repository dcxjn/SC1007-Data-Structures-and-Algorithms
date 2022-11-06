#include <stdio.h>
#include <stdlib.h>

struct _listNode
{
	int item;
	struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode **head, int pivot);

int main()
{
	ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d", &pivot);

	while (scanf("%d", &i))
	{
		if (head == NULL)
		{
			head = (ListNode *)malloc(sizeof(ListNode));
			temp = head;
		}
		else
		{
			temp->next = (ListNode *)malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;

	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head)
{
	while (head != NULL)
	{
		printf("%d ", head->item);
		head = head->next;
	}
	printf("\n");
}

void deleteList(ListNode **ptrHead)
{
	ListNode *cur = *ptrHead;
	ListNode *temp;
	while (cur != NULL)
	{
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	*ptrHead = NULL;
}

void triPartition(ListNode **head, int pivot)
{
	ListNode *lessthan_head = NULL, *lessthan_end = NULL;
	ListNode *sameas_head = NULL, *sameas_end = NULL;
	ListNode *greaterthan_head = NULL, *greaterthan_end = NULL;
	ListNode *move = *head;

	while (move != NULL)
	{

		if (move->item == pivot)
		{
			if (sameas_head == NULL)
			{
				sameas_head = sameas_end = move;
			}
			else
			{
				sameas_end->next = move;
				sameas_end = sameas_end->next;
			}
		}

		else if (move->item < pivot)
		{
			if (lessthan_head == NULL)
			{
				lessthan_end = lessthan_head = move;
			}
			else
			{
				lessthan_end->next = move;
				lessthan_end = move;
			}
		}

		else
		{
			if (greaterthan_head == NULL)
			{
				greaterthan_head = greaterthan_end = move;
			}
			else
			{
				greaterthan_end->next = move;
				greaterthan_end = move;
			}
		}

		move = move->next;
	}

	if (greaterthan_end != NULL)
	{
		greaterthan_end->next = NULL;
	}

	if (lessthan_head == NULL && sameas_head == NULL)
	{
		*head = greaterthan_head;
	}
	else if (lessthan_head == NULL && sameas_head != NULL)
	{
		sameas_end->next = greaterthan_head;
		*head = sameas_head;
	}

	else if (lessthan_head != NULL && sameas_head == NULL)
	{
		lessthan_end->next = greaterthan_head;
		*head = lessthan_head;
	}
	else
	{
		lessthan_end->next = sameas_head;
		sameas_end->next = greaterthan_head;
		*head = lessthan_head;
	}
}