#include <stdio.h>
#include <stdlib.h>

struct _listNode
{
	int item;
	struct _listNode *next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList
{
	ListNode *head;
	int size;
} LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList *llptr);

LinkedList rearrange(LinkedList ll);

int main()
{
	LinkedList ll;

	ll.head = NULL;
	ll.size = 0;
	ListNode *temp;

	int i = 0;

	while (scanf("%d", &i))
	{
		if (ll.head == NULL)
		{
			ll.head = (ListNode *)malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else
		{
			temp->next = (ListNode *)malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++;
	}
	temp->next = NULL;

	ll = rearrange(ll);

	printList(ll);
	deleteList(&ll);
	return 0;
}

void printList(LinkedList ll)
{
	ListNode *temp = ll.head;

	while (temp != NULL)
	{
		printf("%d ", temp->item);
		temp = temp->next;
	}
	printf("\n");
}
void deleteList(LinkedList *llptr)
{
	ListNode *cur = llptr->head;
	ListNode *temp;
	while (cur != NULL)
	{
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	llptr->head = NULL;
	llptr->size = 0;
}

LinkedList rearrange(LinkedList ll)
{
	if (ll.size < 2)
	{
		return ll;
	}

	LinkedList dup = ll;
	int count = 0;

	while (count < 2)
	{
		LinkedList new;
		ListNode *current = dup.head;
		ListNode *left, *right;

		for (int i = 0; i < (ll.size / 2) - 1; i++)
		{
			current = current->next;
		}

		left = dup.head;
		right = current->next;
		current->next = NULL;

		count += 1;

		if (count == 1) // 1st iteration
		{
			// split R L R L
			new.head = right;

			while (right != NULL && left != NULL)
			{
				ListNode *temp = right->next; // store temp as R2

				right->next = left; // connect R1 to L1
				right = temp;		// shift right to R2
				temp = left->next;	// shift temp to L2
				left->next = right; // connect L1 to R2
				left = temp;		// shift left to L2
			}
		}

		else if (count == 2) // 2nd iteration
		{
			// split L R L R
			new.head = left;

			while (right != NULL)
			{
				ListNode *temp = left->next; // store temp as L2

				left->next = right; // connect L1 to R1
				left = temp;		// shift left to L2
				if (left == NULL)
				{
					break;
				}
				temp = right->next; // shift temp to R2
				right->next = left; // connect R1 to L2
				right = temp;		// shift right to R2
			}
		}

		dup.head = new.head; // update dup to new
	}

	return dup;
}
