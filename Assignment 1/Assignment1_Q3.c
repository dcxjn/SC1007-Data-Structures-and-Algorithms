#include <stdio.h>
#include <stdlib.h>

struct _listNode
{
	float item;
	struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);
ListNode *reverse(ListNode *head);
ListNode *reverseSegment(ListNode *head, int start, int end);

int main()
{
	ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d", &S, &E);

	while (scanf("%f", &f))
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
		temp->item = f;
	}
	temp->next = NULL;

	head = reverseSegment(head, S, E);
	printList(head);
	deleteList(&head);
	return 0;
}

void printList(ListNode *head)
{
	while (head != NULL)
	{
		printf("%.2f ", head->item);
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

ListNode *reverse(ListNode *head)
{
	ListNode *prev = NULL, *current = head, *foll;
	while (current != NULL)
	{
		foll = current->next;
		current->next = prev;
		prev = current;
		current = foll;
	}
	return prev;
}

ListNode *reverseSegment(ListNode *head, int start, int end)
{
	ListNode *rev_head = NULL, *rev_end = NULL;
	ListNode *front = NULL, *back = NULL;
	ListNode *current = head, *headcopy = head;
	int i = 0;

	if (start >= end)
	{
		return head;
	}

	while (current != NULL && i < end + 1)
	{
		if (i < start)
			front = current;
		else if (i == start)
			rev_head = current;
		else if (i == end)
		{
			rev_end = current;
			back = current->next;
			rev_end->next = NULL;
		}
		current = current->next;
		i++;
	}

	if (rev_end == NULL)
		head = headcopy;
	else
	{
		rev_end = reverse(rev_head);

		if (front == NULL)
		{
			head = rev_end;
		}
		else
		{
			front->next = rev_end;
		}
		rev_head->next = back;
	}
	return head;
}