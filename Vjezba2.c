//2. Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
//A.dinamički dodaje novi element na početak liste,
//B.ispisuje listu,
//C.dinamički dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše određeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 64

struct Osoba;
typedef struct Osoba* pozicija;

typedef struct Osoba
{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godina_rodenja;
	pozicija sljedeci;
} osoba;
//ode smo napravili osobu koja ce ic u vezanu listu

pozicija alociraj_memoriju_za_osobu(char ime[MAX_SIZE], char prezime[MAX_SIZE], int godina_rodenja)
{
	pozicija nova_osoba = NULL;//uvik postavit na NULL, siti se Sentine price kako je izgubija novce u firmi radi toga
	nova_osoba = (pozicija)malloc(sizeof(osoba));//(a*)malloc(sizeof(a))
	if (!nova_osoba)
	{
		perror("Ne moze se alocirat memorija!");
		return NULL;
	}
	strcpy(nova_osoba->ime, ime);//newPerson->name = name; nece radit
	strcpy(nova_osoba->prezime, prezime);//newPerson->surname = surname; isto nece radit
	nova_osoba->godina_rodenja = godina_rodenja;
	nova_osoba->sljedeci = NULL;
	return nova_osoba;
}
//ova funkcija ce nan tribat za "ubacit" osobu na odredeno misto u vezanu listu za "A" i "C"

int ubaci_nakon(pozicija _pozicija, pozicija nova_osoba)
{
	pozicija temp = _pozicija->sljedeci;
	_pozicija->sljedeci = nova_osoba;
	nova_osoba->sljedeci = temp;
	return EXIT_SUCCESS;
}
//ova funkcija nam pomaze kako bi ubacili prvu osobu nakon "Head" za "A" i zadnju osobu za "C"

int dodaj_osobu_na_pocetak(pozicija nova_prva_osoba, pozicija head, char ime[MAX_SIZE], char prezime[MAX_SIZE], int godina_rodenja)
{
	ubaci_nakon(head, nova_prva_osoba);//dodavanje osobe na pocetak liste
	return EXIT_SUCCESS;
}
//zadatak pod "A" rjesen

int ispis_liste(pozicija prvi) 
{
	pozicija temp = prvi;
	while (temp)
	{
		printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n", temp->ime, temp->prezime, temp->godina_rodenja);
		temp = temp->sljedeci;
	}
	return EXIT_SUCCESS;
}
//zadatak pod "B" rjesen

pozicija nadji_zadnji_el(pozicija head) 
{
	pozicija temp = head;
	while (temp->sljedeci) 
	{
		temp = temp->sljedeci;
	}
	return temp;
}
//ova funkcija nan triba za "C"

int dodaj_osobu_na_kraj(pozicija nova_zadnja_osoba, pozicija head, char ime[MAX_SIZE], char prezime[MAX_SIZE], int godina_rodenja)
{
	pozicija zadnja_osoba = nadji_zadnji_el(head);
	ubaci_nakon(zadnja_osoba, nova_zadnja_osoba);
	return EXIT_SUCCESS;
}
//zadatak pod "C" rjesen

pozicija nadji_po_prezimenu(pozicija prvi, char* prezime) {
	pozicija temp = prvi;
	while (temp) {
		if (strcmp(temp->prezime, prezime) == 0) {//vraca true ako je prvi veci po ASCII tablici od drugog
			return temp;
		}
	}
	return NULL;
}
//zadatak pod "D" rjesen

int izbrisi_el(pozicija prvi, char* prezime)
{
	pozicija ono_sta_trazimo = nadji_po_prezimenu(prvi, prezime);
	pozicija temp = prvi;
	pozicija prijasnji = prvi;
	while (temp)
	{
		temp = temp->sljedeci;
		if (ono_sta_trazimo == temp)
		{
			pozicija temp2 = ono_sta_trazimo->sljedeci;
			free(ono_sta_trazimo);
			prijasnji->sljedeci = temp2;
			break;
		}
		temp = temp->sljedeci;
		prijasnji = prijasnji->sljedeci;
	}
	return 0;
}

int main()
{
	osoba head;// = alociraj_memoriju_za_osobu("0", "0", 0);
	head.sljedeci = NULL;
	int a, b ,c , godina_rodenja;
	char* ime[MAX_SIZE], prezime[MAX_SIZE];
	pozicija nova_osoba = NULL;
	//osoba head = { .sljedeci = NULL, .ime = {0}, .prezime = {0}, .godina_rodenja = 0 };
	//ne svida mi se ovo zasad al ostavicu jer ce mi se vjerojatno svidit kad mi se malo slegne
	//nadan se da je moja verzija (prve dvi linije u main-u) dobra i da radi isto
	while (1)
	{
		printf("Zelite li upisati novu osobu?\nUpisite 0 ako necete, 1 ako ocete, 2 ako zelite brisat clan, 3 za izlaz.\n");
		scanf("%d", &b);
		if (b == 0)
		{
			printf("\nLijep pozdrav! :) \n");
		}
		else if (b == 1)
		{
			printf("Koliko puta?\n");
			scanf("%d", &c);
			for (int i = 0; i < c; i++)
			{
				printf("Unesite ime:\n");
				scanf(" %s", ime);
				printf("Unesite prezime:\n");
				scanf(" %s", prezime);
				printf("Unesite godinu rodjenja:\n");
				scanf(" %d", &godina_rodenja);
				nova_osoba = alociraj_memoriju_za_osobu(ime, prezime, godina_rodenja);
				dodaj_osobu_na_kraj(nova_osoba, &head, ime, prezime, godina_rodenja);
			}
		}
		else if (b == 2)
		{
			char prezime[MAX_SIZE] = "";
			printf("\nUnesite prezime za brisat!\n");
			scanf("%s", &prezime);
			izbrisi_el(head.sljedeci, prezime);
			printf("\n");
			ispis_liste(head.sljedeci);
		}
		else if (b == 3)
		{
			break;
		}
	}
	printf("\n");
	ispis_liste(head.sljedeci);
	return EXIT_SUCCESS;
}
