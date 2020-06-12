/* GHEORGHE Luminita-Gabriela - 312 CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

 void PRINT_FLOAT(t_table *table) //functie pentru printarea uui tabel cu elemente de tip float

 {
 	t_floatCell *cell;
	t_floatLine *s;

	for(s = table->lines; s != NULL; s = s->next){ //parcurgerea fiecarei linii a tabelului

   		cell = s->cells; //celula ce face legatura cu prima informatie de pe o linie

   		while(cell != NULL){

   			printf("%-31f", cell->value); //printarea informatiei de pe o linie cu 31 de saptii intre ele
  			cell = cell->next; //avansul la urmatoarea linie
    	}
    printf("\n");
  	}
 }

 void PRINT_STRING(t_table *table) //functie pentru printarea uui tabel cu elemente de tip string

 {
 	t_stringCell *cell;
 	t_stringLine *s;
 	int i;

 	 for(s = table->lines; s != NULL; s = s->next){ //parcurgerea fiecarei linii a tabelului

 		cell = s->cells; //celula ce face legatura cu prima informatie de pe o linie

   			while(cell != NULL){
   				printf("%s", cell->value); //printarea informatiei de pe o linie
   					for(i = 0; i < MAX_COLUMN_NAME_LEN - strlen(cell->value) + 1; i++){ //spatierea intre informatiile din linie
   						printf(" ");
   					}
  
   			cell = cell->next; //avansul la urmatoarea linie
   			}

	 printf("\n");
  }
 }

int Number(int nr) //functie care numara cifrele dintr-un numar de tip int

{
	int numar_de_cifre = 0;
	if(nr == 0)
		return 1;
	else{
	while(nr != 0)
	{
		numar_de_cifre++;
		nr = nr/10;
	}
		return numar_de_cifre;
	}
}

 void PRINT_INT(t_table *table) //functie pentru printarea uui tabel cu elemente de tip int
 {
 	t_intCell *cell;
	t_intLine *s;
	int nr, i;

	for(s = table->lines; s != NULL; s = s->next){ //parcurgerea fiecarei linii a tabelului

  		cell = s->cells; //celula ce face legatura cu prima informatie de pe o linie

  		 	while(cell != NULL){
   				nr = Number(cell->value);
   				printf("%d", cell->value); //printarea informatiei de pe o linie
   					for(i = 0; i < MAX_COLUMN_NAME_LEN - nr + 1; i++){ //spatierea intre liniile tabelului
   						printf(" ");
  			}
   		cell = cell->next; //avansul la urmatoarea linie
  	 }

    printf("\n");
  }
 }


void PRINT(t_table *table) //functia pentru printarea unui tabel

{
	t_column *column;
	int nr = 0;
	int i, j;
	
	printf("TABLE: %s\n", table->name);
	column = table->columns;
	while(column != NULL)
	{
		nr++;
		printf("%s", column->name);
		for(i = 0; i < (MAX_COLUMN_NAME_LEN - strlen(column->name) + 1); i++) //spatierea dintre coloane
			printf(" ");
		
		 column = column->next;
	}
	printf("\n");
	for(i = 0; i < nr; i++)
	{
		for(j = 0; j < MAX_COLUMN_NAME_LEN; j++) //printarea unei linii specifice dupa afisarea coloanelor
			printf("-");
		printf(" ");
	}
	printf("\n");

	// printarea unui tabel in functie de tipul de date pe care il contine

	if(table->type == FLOAT){
		PRINT_FLOAT(table);
		printf("\n");
	}
	else if(table->type == STRING){
		PRINT_STRING(table);
		printf("\n");
	}
	else if(table->type == INT){
		PRINT_INT(table);
		printf("\n");
	}

 }


void PRINT_DB(t_db **database) //functie pentru printarea bazei de date
{
	t_table *table;
	printf("DATABASE: %s\n", (*database)->name);
	printf("\n");
	for(table = (*database)->tables; table != NULL; table = table->next){ /* pentru fiecare tabel se apeleazaa
																			functia de printare a unui tabel */
		PRINT(table); 
	}
}

/* functie pentru printarea unei singure linii cu elemente de tip int */

void PRINT_INT_LINE(t_intLine *s)

{
	t_intCell *cell;
	cell = s->cells;
	int nr = 0;
	int i;

	while(cell != NULL){
		nr = Number(cell->value);
		printf("%d", cell->value);
		for(i = 0; i < MAX_COLUMN_NAME_LEN - nr + 1; i++){
			printf(" ");
		
		}
		cell = cell->next;
	}
	printf("\n");
	
}

/* functie pentru printarea unei singure linii cu elemente de tip float */

void PRINT_FLOAT_LINE(t_floatLine *s)

{
	t_floatCell *cell;
	cell = s->cells;
	while(cell != NULL){
   		printf("%-31f", cell->value);
  		cell = cell->next;
   }
    printf("\n");
}

/* functie pentru printarea unei singure linii cu elemente de tip string */
	

void PRINT_STRING_LINE(t_stringLine *s)

{
	t_stringCell *cell;
	cell = s->cells;
	int nr = 0;
	int i;

	while(cell != NULL){
		nr++;
		printf("%s", cell->value);
		for(i = 0; i < (MAX_COLUMN_NAME_LEN - strlen(cell->value) + 1); i++)
			printf(" ");
	
		cell = cell->next;
	}

	printf("\n");
}

/* functie pentru printarea inceputului unui tabel, 
	reprezentand numele coloanelor si o linie de separare */

void PRINT_INTRO(t_column *column)

{

int i, j;
int nr = 0;

while(column != NULL){
	nr++;
	printf("%s", column->name);
	for(i = 0; i < (MAX_COLUMN_NAME_LEN - strlen(column->name) + 1); i++){
		printf(" ");
	}
	column = column->next;
}

printf("\n");
for(i = 0; i < nr; i++){
	for(j = 0; j < MAX_COLUMN_NAME_LEN; j++){
		printf("-");
	}
	printf(" ");
}
//printf("\n");
printf("\n");

}

/* functei pentru cautarea unor anumite valori dintr-o coloana 
	dupa un criteriu, intr-un tabel cu date de tipul int */

void SEARCH_INT(t_table *table, char *column_name, char *value, char *relation)
{
	t_column *c;
	t_intLine *s;
	t_intCell *p;
	int a, b;
	a= b =0;
	int nr = 0;
	int n1, n2, n3, n4, n5, n6;
	n1 = n2 = n3 = n4 = n6 = 0;
	int i;
	int int_value;
	t_column *column;

	column = table->columns;
	int_value = atoi(value); //transformarea valorii date ca parametru intr-o variabila de tip int
	for(c = table->columns; c!= NULL; c = c->next){
		nr++; //numerotarea coloanelor tabelului
		if(strcmp(column_name, c->name) == 0){
			break;
		}
	
	}

	for(s = table->lines; s != NULL; s = s->next){
		b++; //numerotarea liniilor tabelului
		p = s->cells;

		for(i = 0; i < (nr-1); i++){
			p = p->next; //p va pointa, pe rand, catre celulele de sub coloana cautata
		}

		if(strcmp(relation, "<=") == 0){ //cazul pentru primul criteriu

		if(p->value <= int_value){ /* verificare daca fiecare informatie de sub coloana cautata
										respecta criteriul */
				
			if(n1 == 0){ //cazul pentru care informatia de pe prima linie respecta crietriul

				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column); //se afiseaza capetele de coloane
				PRINT_INT_LINE(s); //se afiseaza linia care contine elementul ce repsecta criteriul
				
				n1++;
			}

			else if(n1 != 0){
				PRINT_INT_LINE(s); //cazul in care informatia ce respecta criteriul nu se afla pe prima linie a tabelului
			}
		}
		else{
			a++;
		}
		}

		/* analog, urmeaza cazurile pentru celelalte criterii de comparatie, si anume:
		   ">=", "<", ">", "==" sau "!=" */

		if(strcmp(relation, ">=") == 0){

		if(p->value >= int_value){

			if(n2 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_INT_LINE(s);	
				n2++;
			}

			else if(n2 != 0){
				PRINT_INT_LINE(s);
			}
		}
		else{
			a++;
		}
		}

		if(strcmp(relation, "<") == 0){
				if(p->value < int_value){

			if(n3 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_INT_LINE(s);
				n3++;
			}

			else if(n3 != 0){
				PRINT_INT_LINE(s);
			}

		}
		else{
			a++;
		}
		}

		if(strcmp(relation, ">") == 0){
				if(p->value > int_value){

			if(n4 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_INT_LINE(s);
				n4++;
			}

			else if(n4 != 0){
				PRINT_INT_LINE(s);
			}

		}
		else{
			a++;
		}
		}

		if(strcmp(relation, "==") == 0){
				if(p->value == int_value){

			if(n5 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_INT_LINE(s);
				n5++;
			}

			else if(n5 != 0){
				PRINT_INT_LINE(s);
			}
		}
		else{
			a++;
		}
		}

		if(strcmp(relation, "!=") == 0){
				if(p->value != int_value){

			if(n6 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_INT_LINE(s);
				n6++;
			}

			else if(n6 != 0){
				PRINT_INT_LINE(s);
			}

		}
		else{
			a++;
		}
		}
	}

	/* in cazul in care nicio linie nu indeplinesre criteriul, 
		se vor afisa capetele de coloane si linia despartitoare */
	if(a == b){
		printf("TABLE: %s\n", table->name);
		PRINT_INTRO(column);
		printf("\n");
	}
	if(a != b){
		printf("\n");
	}
	
	}

/* functei pentru cautarea unor anumite valori dintr-o coloana 
	dupa un criteriu, intr-un tabel cu date de tipul float */

void SEARCH_FLOAT(t_table *table, char *column_name, char *value, char *relation)
{
	t_column *c;
	t_floatLine *s;
	t_floatCell *p;
	int a, b;
	a = b = 0;
	int nr = 0;
	int n1, n2, n3, n4, n5, n6;
	n1 = n2 = n3 = n4 = n6 = 0;
	int i;
	float float_value;
	t_column *column;

	column = table->columns;
	float_value = atof(value); //transformarea valorii date ca parametru intr-o variabila de tip float
	for(c = table->columns; c!= NULL; c = c->next){
		nr++; //numerotarea coloanelor tabelului
		if(strcmp(column_name, c->name) == 0){
			break;
		}
	}
	for(s = table->lines; s != NULL; s = s->next){
		b++; //numerotarea liniilor tabelului 
		p = s->cells;

		for(i = 0; i < (nr-1); i++){
			p = p->next; //p va pointa catre celulele de sub coloana cautata
		}

		if(strcmp(relation, "<=") == 0){ //cazul pentru primul criteriu

		if(p->value <= float_value){  /* verificare daca fiecare informatie de sub coloana cautata
										respecta criteriul */
				
			if(n1 == 0){ //cazul pentru care informatia de pe prima linie respecta crietriul

				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column); //se afiseaza capetele de coloane
				PRINT_FLOAT_LINE(s); //se afiseaza linia care contine elementul ce repsecta criteriul
				n1++;
			}

			else if(n1 != 0){ //cazul in care informatia ce respecta criteriul nu se afla pe prima linie a tabelului
				PRINT_FLOAT_LINE(s);
			}
		}
		else{
			a++;
		}
		}


		/* analog, urmeaza cazurile pentru celelalte criterii de comparatie, si anume:
		   ">=", "<", ">", "==" sau "!=" */


		if(strcmp(relation, ">=") == 0){

		if(p->value >= float_value){

			if(n2 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_FLOAT_LINE(s);
				n2++;
			}

			else if(n2 != 0){
				PRINT_FLOAT_LINE(s);
			}

		}
		else{
			a++;
		}
		}

		if(strcmp(relation, "<") == 0){
				if(p->value < float_value){

			if(n3 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_FLOAT_LINE(s);
				n3++;
			}

			else if(n3 != 0){
				PRINT_FLOAT_LINE(s);
			}

		}
		else{
			a++;
		}
		}

		if(strcmp(relation, ">") == 0){
				if(p->value > float_value){

			if(n4 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_FLOAT_LINE(s);
				n4++;
			}

			else if(n4 != 0){
				PRINT_FLOAT_LINE(s);
			}

		}
		else{
			a++;
		}
		}

		if(strcmp(relation, "==") == 0){
				if(p->value == float_value){

			if(n5 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_FLOAT_LINE(s);
				n5++;
			}

			else if(n5 != 0){
				PRINT_FLOAT_LINE(s);
			}

		}
		else{
			a++;
		}
		}

		if(strcmp(relation, "!=") == 0){
			if(p->value != float_value){

			if(n6 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_FLOAT_LINE(s);
				n6++;
			}

			else if(n6 != 0){
				PRINT_FLOAT_LINE(s);
			}

		}
		else{
			a++;
		}
		}

	}

	/* in cazul in care nicio linie nu indeplinesre criteriul, 
		se vor afisa capetele de coloane si linia despartitoare */
	if(a == b){
		printf("TABLE: %s\n", table->name);
		PRINT_INTRO(column);
		printf("\n");
	}
	if(a != b){
		printf("\n");
	}

}

/* functei pentru cautarea unor anumite valori dintr-o coloana 
	dupa un criteriu, intr-un tabel cu date de tipul string */


void SEARCH_STRING(t_table *table, char *column_name, char *value, char *relation)
{
	t_column *c;
	t_stringLine *s;
	t_stringCell *p;
	int a,b;
	a = b =0;
	int nr = 0;
	int n1, n2, n3, n4, n5, n6;
	n1 = n2 = n3 = n4 = n6 = 0;
	int i;
	t_column *column;

	column = table->columns;
	for(c = table->columns; c!= NULL; c = c->next){
		nr++; //numerotarea coloanelor
		if(strcmp(column_name, c->name) == 0){
			break;
		}
	}
	for(s = table->lines; s != NULL; s = s->next){
		b++; //numerotarea liniilor
		p = s->cells;

		for(i = 0; i < (nr-1); i++){
			p = p->next; //p va pointa catre celulele de sub coloana cautata
		}

		if(strcmp(relation, "<=") == 0){ //cazul pentru primul criteriu

		if(strcmp(p->value, value) <= 0){ /* verificare daca fiecare informatie de sub coloana cautata
										respecta criteriul */
				
			if(n1 == 0){ //cazul pentru care informatia de pe prima linie respecta crietriul

				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column); //se afiseaza capetele de coloane
				PRINT_STRING_LINE(s); //se afiseaza linia care contine elementul ce repsecta criteriul
				n1++;
			}

			else if(n1 != 0) {//cazul in care informatia ce respecta criteriul nu se afla pe prima linie a tabelului
				PRINT_STRING_LINE(s);
			}
			}
		else{
			a++;
		}
		}

		/* analog, urmeaza cazurile pentru celelalte criterii de comparatie, si anume:
		 ">=", "<", ">", "==" sau "!=" */

		if(strcmp(relation, ">=") == 0){

		if(strcmp(p->value, value) >= 0){

			if(n2 == 0){

				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_STRING_LINE(s);
				n2++;
			}

			else if(n2 != 0){
				PRINT_STRING_LINE(s);
			}
		}
		else{
			a++;
		}

		}

		if(strcmp(relation, "<") == 0){
				if(strcmp(p->value, value) < 0){

			if(n3 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_STRING_LINE(s);
				n3++;
			}

			else if(n3 != 0){
				PRINT_STRING_LINE(s);
			}
		}
		else{
		a++;
		}
		}

		if(strcmp(relation, ">") == 0){
				if(strcmp(p->value, value) > 0){

			if(n4 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_STRING_LINE(s);
				n4++;
			}

			else if(n4 != 0){
				PRINT_STRING_LINE(s);
		
		}
		}
		else{
		a++;
	}
		}

		if(strcmp(relation, "==") == 0){
				if(strcmp(p->value, value) == 0){

			if(n5 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_STRING_LINE(s);
				n5++;
			}

			else if(n5 != 0){
				PRINT_STRING_LINE(s);
			
		}
		}
		else{
		a++;
		}
		}

		if(strcmp(relation, "!=") == 0){
				if(strcmp(p->value, value) != 0){

			if(n6 == 0){
				printf("TABLE: %s\n", table->name);
				PRINT_INTRO(column);
				PRINT_STRING_LINE(s);
				n6++;
			}

			else if(n6 != 0){
				PRINT_STRING_LINE(s);
			
		}
		}
		else{
		a++;
		}
	}
}

	/* in cazul in care nicio linie nu indeplinesre criteriul, 
		se vor afisa capetele de coloane si linia despartitoare */

	if(a == b){
		printf("TABLE: %s\n", table->name);
		PRINT_INTRO(column);
		printf("\n");
	}
	if(a != b){
		printf("\n");
	}
}
