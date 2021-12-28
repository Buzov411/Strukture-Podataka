/*
9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u cvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraca
pokazivac na korijen stabla.
b) Napisati funkciju replace koja ce svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu(tj.sumom svih potomaka prije zamjene
vrijednosti u tim potomcima).Npr.stablo sa slike Slika 1 transformirat ce se u stablo na
slici Slika 2.
c) Prepraviti program na nacin da umjesto predefiniranog cjelobrojnog polja koristenjem
funkcije rand() generira slucajne brojeve u rasponu <10, 90>.Takoder, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon koristenja funkcije iz a), zatim b)
dijela zadatka.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node;
typedef struct Node* position;
typedef struct Node
{
	int el;
	position left;
	position right;
}node;

position create_el(int a);
position insert(position root, position p);//vraca root
int ab(int a, int b, position root);
int replace(position root);

int main()
{
	position root = NULL;
	int i = 0;
	int a[10] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
	for (i; i < 10; i++)
	{
		root = insert(root, create_el(a[i]));
	}
	replace(root);
	return 0;
}

position create_el(int a)
{
	position p = (position)malloc(sizeof(node));
	p->left = p->right = NULL;
	p->el = a;
	return p;
}

position insert(position root, position p)
{
	if (root == NULL)
	{
		root = p;
		return root;
	}
	else if (root->el <= p->el)
	{
		root->left = insert(root->left, p);
	}
	else if (root->el > p->el)
	{
		root->right = insert(root->right, p);
	}
	return root;
}

int ab(int a, int b, position root)
{
	if (root->left != NULL)
	{
		a = root->left->el;
	}
	if (root->right != NULL)
	{
		b = root->right->el;
	}
	return 0;
}

int replace(position current)
{
	int l_before = 0;
	int d_before = 0;
	int l_now = 0;
	int d_now = 0;

	if (current != NULL)
	{
		if (current->left != NULL)
		{
			l_before = current->left->el;
		}
		if (current->right != NULL)
		{
			d_before = current->right->el;
		}

		replace(current->left);
		replace(current->right);

		if (current->left != NULL)
		{
			l_now = current->left->el;
		}

		if (current->right != NULL)
		{
			d_now = current->right->el;
		}

		return current->el = l_now + d_now + l_before + d_before;
	}
	return 0;
}
