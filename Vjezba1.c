#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct _student 
{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajBrojRedakaIzDatoteke(char* NazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = {0};//buffer je ka spremnik u koji spremamo sve iz datoteke, niz charova

	datoteka = fopen(NazivDatoteke, "r");//otvori datoteku (analogija: posudujes knjigu iz knjiznice)
	if (!datoteka)//ako je nema izbaci gresku
	{
		printf("Greska");
		return -1;//OS vidi da nesto ne valja jer je negativan broj, mozemo uzet bilo koji
	}
	while (!feof(datoteka))//Dok nije feof(!feof), tj dok nije end of file, tj dok jos ucitavamo podatke iz datoteke
	{
		fgets(buffer, MAX_LINE, datoteka);//fgets stavlja sve iz datoteke u buffer velicine MAX_LINE
										  //ako stavimi manje od toga ostatak buffera ostaje na nuli ka sta je inicijalizirano u 19. liniji
										  //buffer ucitava liniju po liniju koda, zato mozemo lako odredit koliko ima redaka priko njega
		brojac++;
	}

	fclose(datoteka);//zatvori datoteku (analogija: vracanje knjige koju si posudija iz knjiznice)

	return brojac;
}

student* ProcitajMemorijuIAlocirajStudente(int BrojStudenata, char* NazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(BrojStudenata * sizeof(student));
	datoteka = fopen(NazivDatoteke, "r");
	
	if (!datoteka)
	{
		printf("Greska alociranja");
		free(studenti);//ako nema nicega u datoteci alociranu memoriju iz 46. linije oslobodi da je drugi mogu koristit (OBAVEZNO!)
		return -1;
	}
	while (!feof(datoteka))
	{
		fscanf(datoteka, "%s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		//(cptr, cptr, &lf) i zbog toga moramo stavit & isprid bodova - npr. ode nan triba bit &a, a posto vrijedi:
		//tip_varijable* cptr;
		//cptr = pointer/adresa nekog chara
		//&lf = adresa na kojoj se nalazi neki long float(double)
		brojac++;
	}

	fclose(datoteka);

	return studenti;
}

int main()
{
	int BrojStudenata = ProcitajBrojRedakaIzDatoteke("RezultatiIspita.txt");
	student* studenti = ProcitajMemorijuIAlocirajStudente(BrojStudenata, "RezultatiIspita.txt");
  
	for (int i = 0; i < BrojStudenata; i++)
	{
		printf("%s %s %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
	}
  
	return 0;//0 - sve dobro
			 //-n - katastrofalna greska
			 //+n - korsinicka greska
}
