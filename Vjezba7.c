//Napisati program koji pomocu vezanih listi(stabala) predstavlja strukturu direktorija.
//Omoguciti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
//povratak u prethodni direktorij. Tocnije program treba preko menija simulirati
//koristenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <string.h>

#define LINE 1024

struct _element;
typedef struct _element* position;

typedef struct _element
{
	char ime[LINE];
	position sibling;
	position child;
}element;

typedef struct _element_stoga
{
	position p;
	position next;
}element_stoga;

int push(element_stoga* head, element_stoga* stvoreni, position ulazni);
int pop(element_stoga* head);
element_stoga* stvori_novog_stog();
int printaj(element_stoga* head);
element_stoga* trazi_element(element_stoga* head);
position stvori_novog();
position insert(position current, position ne);
int meni();

int main()
{
	char naredba[LINE] = { 0 };
	element majka = { 'C',NULL,NULL };
	position ne = NULL;
	position parent = NULL;
	element_stoga* roditelj = NULL;
	element_stoga* temp = NULL;
	element_stoga head = { NULL,NULL };

	meni();

	do
	{
		if (strcmp(naredba, "md") == 0)
		{
			if (majka.child == NULL)
			{
				*parent = majka;
			}
			parent->child = insert(parent->child, stvori_novog());
		}
		if (strcmp(naredba, "cd..") == 0)
		{
			pop(&head);
		}
		if (strcmp(naredba, "cd_dir") == 0)
		{
			temp = trazi_element(&head);
			if (temp == EXIT_SUCCESS)
			{
				printf("\nNazalost taj direktorij ne postoji ili je naziv krivo unesen\n");
			}
			else
			{
				roditelj = trazi_element(&head);
			}
		}
		if (strcmp(naredba, "dir") == 0)
		{
			printaj(&head);
		}
	} while (strcmp(naredba, "izlaz") != 0);
	return 0;
}

int meni()
{
	printf("\nZa sada su realizirane naredbe\n");
	printf("0-meni");
	printf("1-md\n");
	printf("2-cd dir\n");
	printf("3-cd..\n");
	printf("4-dir\n");
	printf("5-izlaz\n");
	return EXIT_SUCCESS;
}

position stvori_novog()
{
	position novi;
	novi = (position)malloc(sizeof(element));
	char naziv[LINE] = { 0 };
	printf("\nUnesite ime structure: ");
	scanf_s(" %s", naziv);
	strcpy_s(novi->ime, LINE, naziv);
	novi->child = NULL;
	novi->sibling = NULL;
	return novi;
}

position insert(position current, position ne)
{
	if (!current)
	{
		return ne;
	}
	if (strcmp(current->ime, ne->ime) > 0)
	{
		current->sibling = insert(current->sibling, ne);
	}
	else if (strcmp(current->ime, ne->ime) < 0)
	{
		ne->sibling = current;
		return ne;
	}
	return current;
}

element_stoga* stvori_novog_stog()
{
	element_stoga* novi = NULL;
	novi = (element_stoga*)malloc(sizeof(element_stoga));
	novi->p = NULL;
	novi->next = NULL;
	return novi;
}

int push(element_stoga* head, element_stoga* stvoreni, position ulazni)
{
	stvoreni->next = head->next;
	stvoreni->p = ulazni;
	head->next = stvoreni;				

	return EXIT_SUCCESS;
}

int pop(element_stoga* head)
{
	element_stoga* temp1 = NULL;
	element_stoga* temp2 = NULL;
	temp1 = head;
	temp2 = head->next;

	if (temp1 == NULL)
	{
		printf("\nNe postoji bas nista unutra nema što brisati\n");
		return EXIT_SUCCESS;
	}

	if (temp2 == NULL)
	{
		printf("\nUnutar pocetnog direktorija ste i sve je obrisano\n");
	}
	else
	{
		temp1->next = temp2->next;
		free(temp2);
	}
	return EXIT_SUCCESS;
}

int printaj(element_stoga* head)
{
	element_stoga* temp = NULL;
	temp = head->next;

	if (!temp)
	{
		printf("\nNema elemenata!!\n");
	}

	while (temp != NULL)
	{
		printf("/%s", temp->p->ime);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

element_stoga* trazi_element(element_stoga* head)
{
	element_stoga* temp = NULL;
	char ime[LINE] = { 0 };
	printf("\nU koji direktorij idemo: ");
	scanf_s("%s", &ime);
	temp = head->next;

	if (!temp)
		return EXIT_SUCCESS;

	while (temp != NULL)
	{
		if (strcmp(temp->p->ime, ime))
			return temp;
	}
	return EXIT_SUCCESS;
}
