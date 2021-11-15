//4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
//čitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 128

struct Poly;
typedef struct Poly* position;
typedef struct Poly
{
	int coeff;
	int exp;
	position next;
}poly;

int num_of_el_in_string(char* buffer, int i);
int string_to_int(char* buffer, int i);
position create_el(int coeff, int exp);
int insert_after(position first, position second);
int add_el(position head, position new_el);
int switch_em_up(position head, position first, position second);
int free_el(position head, position p);
int read_from_file(position head1, position head2, char* file_name);
int add(position head1, position head2);
int multiply(position head1, position head2);
int print_list(position head);

int free(position head);


int main()
{
	poly head1;
	head1.next = NULL;
	poly head2;
	head2.next = NULL;
	read_from_file(&head1, &head2, "datoteka.txt");
	print_list(&head1);
	print_list(&head2);
	return 0;
}

int num_of_el_in_string(char* buffer, int i)
{
	int x = 0;
	while (buffer[i] != ' ' && buffer[i] != '\0')
	{
		i++;
		x++;
	}
	if (buffer[i] == ' ')
	{
		x++;
	}
	return x;
}

int string_to_int(char* buffer, int i){
	int x = 0;
	int j = i;
	int z = 0;
	int k = 0;
	while (buffer[j] != ' ' && buffer[j] != '\0' && buffer[j] != '\n')
	{
		j++;
		x++;
	}
	for (x; x > 0; x--)
	{
		j = 1;
		for (k = x; k > 1; k--)
		{
			j *= 10;
		}
		z += (buffer[i] - 48) * j;
		if (buffer[i] < 48 || buffer[i] > 57)//garbage collector
		{
			return -1;
		}
		i++;
	}
	return z;
}

position create_el(int coeff, int exp)
{
	position p = (position)malloc(sizeof(poly));
	if (p == NULL)
	{
		printf("Error! Malloc failed.");
		return NULL;
	}
	p->coeff = coeff;
	p->exp = exp;
	p->next = NULL;
	return p;
}

int insert_after(position first, position second)
{
	position temp = first->next;
	first->next = second;
	second->next = temp;
	return 0;
}

int add_el(position head, position new_el)
{
	position temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	insert_after(temp, new_el);
	return 0;
}

int switch_em_up(position head, position first, position second)
{
	position p = head;
	position temp = create_el(0, 0);
	while (p->next != NULL && p->next != first)
	{
		if (p->next == NULL)
		{
			printf("Ne postoji prvi clan.");
		}
	}
	temp->next = second->next;
	second->next = first;
	p->next = second;
	first->next = second->next;
	return 0;
}

int free_el(position head, position p)
{
	position temp = head->next;
	position t;
	while (temp->next != p && temp->next != NULL)
	{
		temp = temp->next;
	}
	if (temp->next == p)
	{
		temp->next = p->next;
	}
	free(p);
	return 0;
}

int read_from_file(position head1, position head2, char* file_name)
{
	int coeff_array[BUFFER_SIZE / 2] = { 0 };//svi koeficijenti
	int exp_array[BUFFER_SIZE / 2] = { 0 };//svi eksponenti
	int i = 0;
	int j = 0;
	int k = 0;
	int temp_int = 0;
	int row = 1;//imamo dva reda
	int second_row_starts_at_position = 0;
	char buffer[BUFFER_SIZE];
	int int_buffer[BUFFER_SIZE];
	position p, q, temp;
	FILE* fp;
	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		printf("Error! Empty file.");
		return -1;
	}
	while (!feof(fp))//dok ne dodemo do kraja datoteke
	{
		fgets(buffer, sizeof(buffer), fp);//ucitava red po red
		printf("Prvi i drugi red, STRING BUFFER:%s\n", buffer);//ispis prvog pa drugog reda
		while (buffer[i] != '\0')//\0 je kraj reda, ulazimo u prvi i kasnije u drugi red
		{
			int_buffer[j] = string_to_int(buffer, i);//string niz pritvaran u int niz
			i += num_of_el_in_string(buffer, i);//micemo se na misto di pocinje broj
			if (j % 2 == 0)
			{
				coeff_array[j / 2] = int_buffer[j];
			}
			if (j % 2 != 0)
			{
				exp_array[j / 2] = int_buffer[j];
			}
			j++;
		}
		if (row == 1)
		{
			second_row_starts_at_position = j;//kad pocinje drugi red za buffer, za coeff_array i za exp_array je duplo manja vrijednost
			k = 0;
			p = create_el(coeff_array[0], exp_array[0]);
			head1->next = p;
			while (k < second_row_starts_at_position / 2 - 1)//od pocetka do drugog reda
			{
				k++;


				/*if (coeff_array[k] == -1 || exp_array[k] == -1)
				{
					if (coeff_array[k] == -1 && exp_array[k] == -1)
					{
						k++;
					}
					else if (coeff_array[k] == -1)
					{
						temp_int = k;
						while (temp_int < second_row_starts_at_position / 2)
						{
							coeff_array[temp_int] = exp_array[temp_int];
							exp_array[temp_int] = coeff_array[temp_int + 1];
							temp_int++;
						}
						second_row_starts_at_position++;
					}
				}*/


				//garbage collector


				temp = create_el(coeff_array[k], exp_array[k]);
				insert_after(p, temp);
				p = temp;
			}
		}
		else if (row == 2)
		{
			k = second_row_starts_at_position / 2;
			q = create_el(coeff_array[k], exp_array[k]);
			head2->next = q;
			while (k < j / 2 - 1)//od pocetka drugog reda do kraja
			{
				k++;
				temp = create_el(coeff_array[k], exp_array[k]);
				insert_after(q, temp);
				q = temp;
			}
		}
		i = 0;
		row = 2;
	}
	p = head1->next;
	q = head2->next;
	while (p->next != NULL)
	{
		temp = p->next;
		while (temp != NULL)
		{
			if (p->exp == temp->exp)
			{
				p->coeff += temp->coeff;
				free_el(head1, temp);
			}
			printf("\nProvjeravam: %d sa %d sad je temp->next=%x", p->exp, temp->exp, temp);
			temp = temp->next;
		}
		p = p->next;
	}
	while (q->next != NULL)
	{
		temp = q->next;
		while (temp->next != NULL)
		{
			if (q->exp == temp->exp)
			{
				q->coeff += temp->coeff;
				free_el(head2, temp);
			}
			temp = temp->next;
		}
		q = q->next;
	}
	return 0;
}

int add(position head1, position head2)
{
	return 0;
}

int multiply(position head1, position head2)
{
	return 0;
}

int print_list(position head)
{
	position p = head->next;
	if (p == NULL)
	{
		printf("Error! Empty list.\n");
		return -1;
	}
	printf("Pocetak:\n");
	while (p != NULL)
	{
		printf("%d %d\n", p->coeff, p->exp);
		p = p->next;
	}
	printf("Kraj.\n");
	return 0;
}

int free(position head)
{
	return 0;
}
