/* GHEORGHE Luminita-Gabriela - 312 CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

int main(void)
{
	t_db *database;
	char *p;
	char command_copy[MAX_CMD_LEN];
	int number_spaces;
	int i;

	while(1) {

	char command[MAX_CMD_LEN];
	fgets(command, MAX_CMD_LEN, stdin); //citirea comenzilor introduse de la tastatura
	if(!strcmp("\n", command))
	return -1;
	int len = strlen(command);
	if ( command[len - 1] == '\n') {  //eliminare '\n' de la sfarsitul comenzii date 
		command[len - 1] = '\0';
		len --;
	}

	number_spaces = 0; /* numerotarea spatiilor din fiecare comanda introdusa */
	for(i = 0; i < strlen(command); i++)
	{
		if(command[i] == ' ')
			number_spaces++;
	}

	strcpy(command_copy, command);
	char *first_word = strtok(command_copy, " "); //primul cuvant din comanda introdusa

	/* cazul pentru initializarea bazei de date */

	if (strcmp(first_word, "INIT_DB") == 0) { 

		database = INIT_DB(command+8);
	
	}

	/* cazul pentru crearea bazei de date */

 	else if (strcmp(first_word, "CREATE") == 0) {

 		char *rest = command;
 		t_table *t;
 		char *first = strtok_r(rest, " ", &rest);
 		char *table_name = strtok_r(rest, " ", &rest); //numele tabelului
 		char *data_type = strtok_r(rest, " ", &rest); //tipul de date continut de tabel
 		//in variabila rest este stocat vectorul cu numele coloanelor

 		for(t = database->tables; t != NULL; t = t->next)
 		{
 			if(strcmp(table_name, t->name) == 0) //cazul cand un tabel exista in baza de date
 				printf("Table \"%s\" already exists.", table_name);
 		}

 		/* cazul cand nu se cunoaste tipul de date al informatiilor ce urmeaza a fi introduse in tabel */

 		if(((strcmp(data_type, "INT") != 0) && (strcmp(data_type, "STRING") != 0) && (strcmp(data_type, "FLOAT") != 0)))
 		{
 			printf("Unknown data type: %s.\n", data_type);
 		}

 		else
 		{
 			CREATE(&database, table_name, data_type, rest);
 		}
 		
 	}
 
 	/* cazul pentru adaugarea unei linii intr-un tabel */

 	else if (strcmp(first_word, "ADD") == 0) {

 		t_table *t;
 		char *rest = command;
 		char *first = strtok_r(rest, " ", &rest);
 		char *table_name = strtok_r(rest, " ", &rest); //numele tabelului

		for(t = database->tables; t != NULL; t = t->next)
		{
			if(strcmp(table_name, t->name) == 0){
				break;
			}
		}
		
		/* cazul in care tabelul nu se afla in baza de date */

		if(t == NULL)
		{
			printf("Table \"%s\" not found in database.\n", table_name);
		}		
		 
		/* adaugarea liniei in tabel in functie de tipul de date pe care il contine */

		else{
					if(t->type == STRING)
						ADD_LINE_STRING(t, rest);
					if(t->type == FLOAT)
						ADD_LINE_FLOAT(t, rest);
					if(t->type == INT)
						ADD_LINE_INT(t, rest);
			}
					
	}

	/* cazul pentru printarea unui tabel */

	else if (strcmp(first_word, "PRINT") == 0){
		
		char *table_name = strtok(NULL, " ");

		t_table *t;

		for(t = database->tables; t != NULL; t = t->next)
		{
			if(strcmp(table_name, t->name) == 0){
				break;
			}
		}

		// cazul cand tabelul nu se afla in baza de date

		if(t == NULL){
			printf("Table \"%s\" not found in database.\n", table_name);
		}

		else{
			PRINT(t);
			
		}
		
	}

	/* cazul pentru stergerea unui tabel din baza de date */

	else if ((strcmp(first_word, "DELETE") == 0) && (number_spaces == 1)){
	char *table_name = strtok(NULL, " ");
	t_table *t;

		for(t = database->tables; t != NULL; t = t->next)
		{
			if(strcmp(table_name, t->name) == 0){
				break;
			}
		}

		// cazul in care tabelul nu se afla in baza de date

		if(t == NULL){

			printf("Table \"%s\" not found in database.\n", table_name);
		}

		//stergerea tabelului in functie de tipul de date pe care il contine

		else{

			if(t->type == STRING){
				DELETE_STRING_TABLE(&database, t);
			}
			if(t->type == FLOAT){
				DELETE_FLOAT_TABLE(&database, t);
			}
			if(t->type == INT){
				DELETE_INT_TABLE(&database, t);
			}
		}
			
	}

	/* cazul pentru printarea bazei de date */

	else if(strcmp(first_word, "PRINT_DB") == 0){
		PRINT_DB(&database);
	}

	/* cazul pentru eliminarea tuturor liniilor unui tabel */

	else if(strcmp(first_word, "CLEAR") == 0){
		char *table_name = strtok(NULL, " ");
		t_table *t; //contor
		for(t = database->tables; t != NULL; t = t->next)
		{
			if(strcmp(table_name, t->name) == 0)
			{
				break;
			}
		}

	//cazul cand tabelul nu se afla in baza de date

	if(t == NULL){
		printf("Table \"%s\" not found in database.\n", table_name);
	}

	//stergerea liniilor in functie de tipul de date pe care il contin

	else{

		if(t->type == STRING)
			CLEAR_STRING_LINES(t);
		if(t->type == FLOAT)
			CLEAR_FLOAT_LINE(t);
		if(t->type == INT)
			CLEAR_INT_LINE(t);	
		}
	}

	/* cazul pentru cautarea unor anumitor linii in tabel */

	else if(strcmp(first_word, "SEARCH") == 0){

		p = strtok(NULL, " ");
		char *table_name = strdup(p); //numele tabelului
		p = strtok(NULL, " ");
		char *column_name = strdup(p); //numele coloanei dupa care se va compara
		p = strtok(NULL, " ");
		char *relation = strdup(p); //relatia de comparatie
		p = strtok(NULL, " ");
		char *value = strdup(p); //valoarea cu care informatiile vor fi comparate
		t_table *t;
		t_column *c;
		int nr1 = 0;
		int nr2 = 0;
		

		for(t = database->tables; t != NULL; t = t->next){
			if(strcmp(table_name, t->name) == 0){
				break;
			}
			
		}

		// cazul in care tabelul nu se afla in baza de date

		if(t == NULL)
		{
			printf("Table \"%s\" not found in database.\n", table_name);
		}

		else{
				for(c = t->columns; c != NULL; c = c->next)
				{
					if(strcmp(column_name, c->name) != 0)
						nr1++; //numerotarea coloanelor care nu corespund cu numele celei introduse 
				}

				for(c = t->columns; c != NULL; c = c->next)
				{
						nr2++; //numerotarea tuturor coloanelor
				}
		
				//cazul in care tabelul nu contine coloana introdusa

				if(nr1 == nr2){

					printf("Table \"%s\" does not contain column \"%s\".\n", table_name, column_name);		
				}

				//cautarea liniilor in functie de tipul de date continut in tabel

				else{

				if(t->type == INT)
				{
					SEARCH_INT(t, column_name, value, relation);
					//printf("\n");
				}	
				if(t->type == FLOAT)
				{
					SEARCH_FLOAT(t, column_name, value, relation);
					//printf("\n");
				}
				if(t->type == STRING)
				{
					SEARCH_STRING(t, column_name, value, relation);
					//printf("\n");
				}
		
			}

		}
	}

	 /* cazul pentru stergerea unei linii care indeplineste o anumita conditie */

	else if((strcmp(first_word, "DELETE") == 0) && (number_spaces == 4)){

		p = strtok(NULL, " ");
		char *table_name = strdup(p); //numele tabelului
		p = strtok(NULL, " ");
		char *column_name = strdup(p); //numele coloanei dupa care se va face comparatie
		p = strtok(NULL, " ");
		char *relation = strdup(p); //relatia de comparatie
		p = strtok(NULL, " ");
		char *value = strdup(p); //valoarea cu care informatiile vor fi comparate

		t_table *t;
		t_column *c;
		int nr1 = 0;
		int nr2 = 0;

		for(t = database->tables; t != NULL; t = t->next){
			if(strcmp(table_name, t->name) == 0){
				break;
			}
		}

		//cazul in care tabelul nu se afla in baza de date 

		if(t == NULL)
		{
			printf("Table \"%s\" not found in database.\n", table_name);
		}
		else{
			for(c = t->columns; c != NULL; c = c->next)
				{
					if(strcmp(column_name, c->name) != 0)
						nr1++; //numerotarea coloaneloe cu nume diferite fata de cel introdus
				}
			for(c = t->columns; c != NULL; c = c->next)
				{
						nr2++; //numerotarea coloanelor tabelului
				}

			/* cazul in care coloana cautata nu se afla in tabel */

			if(nr1 == nr2){
	  		printf("Table \"%s\" does not contain column \"%s\".\n", table_name, column_name);
			}

			/*stergerea liniei cu informatia ce respecta criteriul
				in functie de tipul datelor continute de tabel */

			else{
				if(t->type == INT)
				{
				 	DELETE_INT(t, column_name, value, relation);
				}	

				if(t->type == FLOAT)
				{
					DELETE_FLOAT(t, column_name, value, relation);
				}

				if(t->type == STRING)
				{
					DELETE_STRING(t, column_name, value, relation);
				}
			}
		
		}
	}

	/* cazul pentru stergerea bazei de date */

	else if(strcmp(first_word, "DELETE_DB") == 0){

		t_table *table;

		/* pentru fiecare tabel al bazei de date, se verifica tipul continut de acesta
			si se merge pe cazul corespunzator de stergere al tabelului */

		for(table= database->tables; table != NULL; table = table->next)
		{
			if(table->type == STRING){
				DELETE_STRING_TABLE(&database, table);
			}
			if(table->type == FLOAT){
				DELETE_FLOAT_TABLE(&database, table);
			}
			if(table->type == INT){
				DELETE_INT_TABLE(&database, table);
			}
		}
		free(database->tables);
		free(database);
		break;
	}

	/* cazul in care comanda introdusa nu este cunoascuta */

	else{
		printf("Unknown command: %s.\n", command);
	}

 }
return 0;

}