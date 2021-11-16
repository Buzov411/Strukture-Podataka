#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct stack* pozicija;
struct stack {
	int element;
	pozicija next;
};

int push(pozicija, int);
int pop(pozicija);

int main()
{
	struct stack head;
	char* buffer = NULL;
	int x = 0, y = 0, rezultat = 0;
	int n = 0, broj = 0, brojac = 0;
	int duljina = 0;
	int velicina = 0;

	char fileName[50];
	char znak;

	printf("Ime datoteke: ");
	scanf(" %s", fileName);

	FILE* dat = fopen(fileName, "r");
	if (!dat)
	{
		printf("Ne moze otvoriti datoteku!\n");
		return 1;
	}

	buffer = (char*)malloc(1024);
	fgets(buffer, 1024, dat);

	velicina = strlen(buffer);

	while (brojac <= duljina)
	{
		if (sscanf(buffer, "%d %n", &broj, &n) == 1)
			push(&head, broj);

		else if (sscanf(buffer, "%c %n", &znak, &n) == 1)
		{
			if (znak == 1)
			{
				y = pop(&head);
				x = pop(&head);
				rezultat = x + y;
				push(&head, rezultat);
			}

			else if (znak == '-')
			{
				y = pop(&head);
				x = pop(&head);
				rezultat = x - y;
				push(&head, rezultat);
			}
			else if (znak == '*')
			{
				y = pop(&head);
				x = pop(&head);
				rezultat = x * y;
				push(&head, rezultat);
			}
		}

		brojac += n;
		buffer += n;
	}
	
	printf("Rezultat: %d\n", pop(&head));

	return 0;

}

int pop(pozicija p)
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(struct stack));

	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		return q->element;
		free(q);
	}

	return 0;
}

int push(pozicija p, int z)
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(struct stack));

	q->element = z;
	q->next = p->next;
	p->next = q;

	return 0;
}
