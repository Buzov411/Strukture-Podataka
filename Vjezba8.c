//Napisati program koji omogucava rad s binarnim stablom pretrazivanja.Treba
//omoguciti unosenje novog elementa u stablo, ispis elemenata(inorder, preorder, postorder i
//level order), brisanje i pronalazenje nekog elementa.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128

struct Node;
typedef struct Node* position;
typedef struct Node
{
	int el;
	position left;
	position right;
}node;

position insert(position current, position p);
int print_inorder(position current);
int print_preoder(position current);
int print_postorder(position current);
int main_loop(int a, int b, position root);

int main()
{
	position root = NULL;
	int a = 4;
	int b = 0;
	main_loop(a, b, root);
	return 0;
}

position make_node(int el)
{
	position p = (position)malloc(sizeof(node));
	if (p == NULL)
	{
		printf("Error! Malloc failed.");
		return NULL;
	}
	p->el = el;
	p->left = NULL;
	p->right = NULL;
	return p;
}

position insert(position current, position p)
{
	if (current == NULL) return p;
	if (current->el > p->el)
	{
		current->left = insert(current->left, p);
	}
	else if (current->el < p->el)
	{
		current->right = insert(current->right, p);
	}
	else free(p);
	return current;
}

int print_inorder(position current)
{
	if (current == NULL) return 0;
	print_inorder(current->left);
	printf("%d", current->el);
	print_inorder(current->right);
	return 0;
}

int print_preorder(position current)
{
	if (current == NULL) return 0;
	printf("%d", current->el);
	print_preorder(current->left);
	print_preorder(current->right);
	return 0;
}

int print_postorder(position current)
{
	if (current == NULL) return 0;
	print_postorder(current->left);
	print_postorder(current->right);
	printf("%d", current->el);
	return 0;
}

int main_loop(int a, int b, position root)
{
	position current;
	printf("Za unos novog elementa u binarno stablo upisite 0, a za ispis elemenata unesite brojeve od 1 do 3:\ninorder - 1\npreorder - 2\npostorder - 3\n");
	scanf_s("%d", &a);
	if (a == 0)
	{
		printf("Unesite broj u binarno stablo.\n");
		scanf_s("%d", &b);
		current = insert(root, make_node(b));
		main_loop(a, b, root);
	}
	else if (a == 1)
	{
		print_inorder(root);
	}
	else if (a == 2)
	{
		print_preorder(root);
	}
	else if (a == 3)
	{
		print_postorder(root);
	}
	else printf("Neispravan unos.\n");
	return 0;
}
