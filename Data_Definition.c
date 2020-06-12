/* GHEORGHE Luminita-Gabriela - 312 CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"


t_db* INIT_DB(char name[MAX_DB_NAME_LEN]) //functia pentru initializarea bazei de date

{
	t_db *baza_de_date;
	baza_de_date = (t_db*)malloc(sizeof(t_db));//alocare memorie pentru un element de tip t_db
	if(!baza_de_date) //verificare alocare baza de date
		return NULL;
	strcpy(baza_de_date->name, name);
	baza_de_date->tables = NULL; //initializare vactorul ce pointeaza catre tabele cu NULL
	return baza_de_date; //returneaza baza de date initializata

}

t_column *AllocateColumn(char column_name[MAX_COLUMN_NAME_LEN]) //functie pentru alocarea unei celule de lista de tip t_column

{
	t_column *new_column;
	new_column = (t_column*)malloc(sizeof(t_column)); //alocarea dinamica a unei celule de lista de dimensiune t_column
	if(!new_column) //verificare alocare celula
		return NULL;
	strcpy(new_column->name, column_name); //copierea numelui coloanei in campul name al celulei de lista
	new_column->next = NULL; //setarea me NULL a legaturii cu alta celula de tip t_column
	return new_column;
}

void CREATE(t_db **database, char name_table[MAX_TABLE_NAME_LEN], char *data_type, char *column_names) //functie pentru crearea unui tabel

{
	t_table *table = (t_table*)malloc(sizeof(t_table)); //alocare dinamica tabel de dimensiune t_table
	t_table *t; //contor 
	t_table *last_table; //ultimul tabel din lista de tabele
	char *name_of_one_column;
	t_column *column;
	t_column *p; //contor
	t_column *last_column;

	if(!table) //verificrae alocare table
		return;
	strcpy(table->name, name_table); //copierea numelui tabelului in campul name 
	//setarea pe NULL a pointerilor ce indica spre lista de coloane, lista de linii si spre urmatorul tabel
	table->columns = NULL;
	table->lines = NULL; 
	table->next = NULL;
	//verificarea tipului datelor din tabel
	if(strcmp(data_type, "INT") == 0){
		table->type = INT;
	}
	if(strcmp(data_type, "FLOAT") == 0){
		table->type = FLOAT;
	}
	if(strcmp(data_type, "STRING") == 0){
		table->type = STRING;
	}

	if((*database)->tables == NULL){ //legarea tabelului de baza de date, in cazul in care este nu mai exista altul
		(*database)->tables = table;
	}
	else{

		for(t = (*database)->tables; t!=NULL; t = t->next){ /* legarea tabelului de cel anterior, 
															in cazul in care exista deja un tabel inseart */
			last_table = t;
		}

	last_table->next = table;
	}

	name_of_one_column = strtok(column_names, " "); //numele primei coloane din tabel


	while(name_of_one_column != NULL){ //cat timp numele citit este diferit de NULL

			column = AllocateColumn(name_of_one_column); //se creeaza o celula de lista de tip t_column cu numele citit
			if(!column){ //verificare alocare celula
			}
			if(table->columns == NULL){ //verificare daca este prima celula de lista din lista ce contine numele coloanelor
				table->columns = column; //in caz afirmativ, celula este legata de tabel prin pointerul table->columns
			}
			else{
				for(p = table->columns; p != NULL; p = p->next){ /* altfel, celula este legata de celulele 
																	din lista de coloane deja intorduse */
					last_column = p;
				}
			last_column->next = column;

			}
			name_of_one_column = strtok(NULL, " "); //se trece la urmatorul cuvant din lista numelor de coloane

	  }

 }

 /* functie pentru dezalocarea memoriei unui tabel cu date de tip string */

void DEZALOC_STRING(t_table *table)

{	 
	t_stringLine *s, *saux;
	t_stringCell *c, *aux;
	t_column *t, *taux;
	t = table->columns;

	if(table->lines != NULL){
		s = table->lines;
		c = s->cells;
 			while(s){

				while(c){

					aux = c;
					c = c ->next;
					free(aux->value);
					free(aux);
				}
				saux = s;
				s = s->next;
				free(saux);
			}

	table->lines = NULL;

	}

	while(t){
		taux = t;
		t = t->next;
		free(taux);
	}

	table->columns = NULL;
	free(table);
	
}

/* functie pentru stergerea unui tabel cu date de tipul string */

void DELETE_STRING_TABLE(t_db **database, t_table *table)

{

	t_table *t, *ant;
	t_table *aux_table;

	for(t = (*database)->tables, ant = NULL; t != NULL;){
		if(strcmp(t->name, table->name) == 0){
			if(ant){
				ant->next = t->next;	/* refacerea legaturilor dintre tabele in urma
											stergerii unui tabel */
			}
			else{
				(*database)->tables = t->next;
			}
			aux_table = t;
			t = t->next;
			DEZALOC_STRING(aux_table); // dezalocarea memoriei
		}
		else{

			ant = t;  //avansul intre tabele
			t = t->next;

		}
	}

}


/* functie pentru dezalocarea memoriei unui tabel cu date de tip float */

void DEZALOC_FLOAT(t_table *table)

{
	 
	t_floatLine *s, *saux;
	t_floatCell *c, *aux;
	t_column *t, *taux;
	t = table->columns;

	if(table->lines != NULL){

		s = table->lines;
		c = s->cells;

		while(s){
			while(c){

				aux = c;
				c = c ->next;
				free(aux);
			}
			saux = s;
			s = s->next;
			free(saux);
		}
	 table->lines = NULL;
	}

	while(t){

		taux = t;
		t = t->next;
		free(taux);
	}

	table->columns = NULL;
	free(table);	

}


/* functie pentru stergerea unui tabel cu date de tipul float */

void DELETE_FLOAT_TABLE(t_db **database, t_table *table)

{

	t_table *t, *ant;
	t_table *aux_table;

	for(t = (*database)->tables, ant = NULL; t != NULL;){
		if(strcmp(t->name, table->name) == 0)
		{
			if(ant){
				ant->next = t->next; /* refacerea legaturilor dintre tabele in urma
											stergerii unui tabel */
			}
			else{
				(*database)->tables = t->next;
			}
			aux_table = t;
			t = t->next;
			DEZALOC_FLOAT(aux_table); // dezalocarea memoriei
		}
		else
		{
			ant = t;
			t = t->next; // avansul intre tabele

		}
	}

}

/* functie pentru dezalocarea memoriei unui tabel cu date de tip int */

void DEZALOC_INT(t_table *table)

{
	 
	t_intLine *s, *saux;
	t_intCell *c, *aux;
	t_column *t, *taux;
	t = table->columns; 

	if(table->lines != NULL){

		s = table->lines;
		c = s->cells;

		while(s){
			while(c){

				aux = c;
				c = c ->next;
				free(aux);
			}
			saux = s;
			s = s->next;
			free(saux);
		}
	table->lines = NULL;
	}

	while(t){

		taux = t;
		t = t->next;
		free(taux);
	}

	table->columns = NULL;
	free(table);
}

/* functie pentru stergerea unui tabel cu date de tipul int */

void DELETE_INT_TABLE(t_db **database, t_table *table)

{
	t_table *t, *ant;
	t_table *aux_table;

	for(t = (*database)->tables, ant = NULL; t != NULL;){
		if(strcmp(t->name, table->name) == 0){
			if(ant){
				ant->next = t->next; /* refacerea legaturilor dintre tabele in urma
											stergerii unui tabel */
			}
			else{
				(*database)->tables = t->next;
			}
			aux_table = t;
			t = t->next;
			DEZALOC_INT(aux_table); // dezalocarea memoriei
		}
		else{
			ant = t;
			t = t->next; // avansul intre tabele

		}
	}

}

