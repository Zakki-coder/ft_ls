#include "includes/ft_ls.h"

void print_lst(t_file_node *head)
{
	int i = 0;
	while(head)
	{
		printf("FILENAME: %d: %s\n", ++i, head->file_name);
		head = head->next;
	}
	printf("\n");
}

int lst_iter(t_file_node **head, int (*f)(const char *s1, const char *s2))
{
	t_file_node *temp;
	t_file_node *previous;
	t_file_node *head_local;
	int i;

	i = 0;
	previous = NULL;
	head_local = *head;
	/* Swap the first without previous */
	if (head_local->next && f(head_local->file_name, head_local->next->file_name) > 0 && ++i)
	{
		temp = head_local->next;
		head_local->next = head_local->next->next;
		temp->next = head_local;
		previous = head_local;
		(*head) = temp;
		head_local = head_local->next;	
	}
	else
	{
		previous = head_local->next;
		head_local = head_local->next->next;
	}
//	debug(*head);
	while (head_local)
	{
		if (head_local->next && f(head_local->file_name, head_local->next->file_name) > 0 && ++i)
		{
//			printf("%s and %s\n", head_local->file_name, head_local->next->file_name);
//			fflush(stdout);
			temp = head_local->next;
			previous->next = head_local->next;
			head_local->next = head_local->next->next;
			temp->next = head_local;
		}
		previous = head_local;
		head_local = head_local->next;
	}
	return (i);
}

void lst_iter_loop(t_file_node **head, int (*f)(const char *, const char *))
{
	int i;
	
	i = lst_iter(head, f);
	while (i)
	{
		i = lst_iter(head, f);
	}
}