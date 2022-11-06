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

void reverseKNodes(ListNode **head, int K);

int main()
{
	ListNode *head = NULL, *temp;
	int i = 0;
	int K = 0;

	scanf("%d", &K);

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

	reverseKNodes(&head, K);
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

void reverseKNodes(ListNode **head, int K)
{

	if (*head == NULL || K < 2)
	{
		return;
	}

	ListNode *counter = *head;
	int count = 0;

	while (counter != NULL)
	{
		count++;
		counter = counter->next;
	}

	ListNode *newhead;
	newhead = (ListNode *)malloc(sizeof(ListNode));
	newhead->next = *head;
	ListNode *prev = newhead, *curr = *head;
	while (count >= K)
	{
		int i;
		for (i = 1; i < K; i++)
		{
			ListNode *curr_next = curr->next;
			ListNode *next = curr_next->next;
			curr_next->next = prev->next;
			prev->next = curr->next;
			curr->next = next;
		}

		prev = curr;
		curr = curr->next;
		count -= K;
	}
	*head = newhead->next;
}