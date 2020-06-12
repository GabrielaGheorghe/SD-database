/* GHEORGHE Luminita-Gabriela - 312 CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

 /* functie pentru alocarea unei celule de lista de tipul t_stringLine
 	care reprezinta o celula din lista ce formeaza capetele de linie ale tabelului, 
 	cu elemente de tipul string */

t_stringLine *AllocateStringLine() 

{
	t_stringLine *aux;
	aux = malloc(sizeof(t_stringLine)); //alocare dinamica a celulei de lista de tipul t_stringLine
	if(!aux) //verificare alocare
		return NULL;
	aux->cells = NULL; //setarea campului ce indica spre elementele unei linii pe NULL
	aux->next = NULL; //setarea campului ce face legatura cu alta linie pe NULL
	
return aux;

}

 /* functie pentru alocarea unei celule de lista de tipul t_stringCell
 	care reprezinta o celula din lista ce formeaza o linie a tabelului, 
 	cu elemente de tipul string */

t_stringCell *AllocateStringCell(char *val)

{
	t_stringCell *aux;
	aux = (t_stringCell*)malloc(sizeof(t_stringCell)); //alocarea dinamica celula de lista de tipul t_stringCell
	if(!aux) //verificare alocare celula
		return NULL;
	aux->value= malloc(strlen(val) + 1); //alocarea vectorului ce stocheaza informatia unei celule de lista
	if(!aux->value) //verificare alocare
		return NULL;
	strcpy(aux->value, val); //copierea informatiei in celula de lista
	aux->next = NULL; //setarea legaturii cu alta celula din linia respectiva pe NULL
	
return aux;

}


 /* functie pentru alocarea unei celule de lista de tipul t_IntLine
 	care reprezinta o celula din lista ce formeaza capetele de linie ale tabelului, 
 	cu elemente de tipul int */

t_intLine *AllocateIntLine()

{
	t_intLine *aux;
	aux = (t_intLine*)malloc(sizeof(t_intLine)); //alocare dinamica a celulei de lista de tipul t_intLine
	if(!aux) //verificare alocare
		return NULL;
	aux->cells = NULL; //setarea campului ce indica spre elementele unei linii pe NULL
	aux->next = NULL; //setarea campului ce face legatura cu alta linie pe NULL

return aux;

}

 /* functie pentru alocarea unei celule de lista de tipul t_intCell
 	care reprezinta o celula din lista ce formeaza o linie a tabelului, 
 	cu elemente de tipul int */

t_intCell *AllocateIntCell(int val)

{
	t_intCell *aux;
	aux = (t_intCell*)malloc(sizeof(t_intCell)); //alocarea dinamica celula de lista de tipul t_intCell
	if(!aux) //verificare alocare celula
		return NULL;
	aux->value = val; //copierea informatiei in celula de lista
	aux->next = NULL; //setarea legaturii cu alta celula din linia respectiva pe NULL
	
return aux;

}

 /* functie pentru alocarea unei celule de lista de tipul t_floatLine
 	care reprezinta o celula din lista ce formeaza capetele de linie ale tabelului, 
 	cu elemente de tipul float */

t_floatLine *AllocateFloatLine()

{
	t_floatLine *aux;
	aux = (t_floatLine*)malloc(sizeof(t_floatLine)); //alocare dinamica a celulei de lista de tipul t_floatLine
	if(!aux) //verificare alocare
		return NULL;
	aux->cells = NULL; //setarea campului ce indica spre elementele unei linii pe NULL
	aux->next = NULL; //setarea campului ce face legatura cu alta linie pe NULL
	
return aux;

}

 /* functie pentru alocarea unei celule de lista de tipul t_floatCell
 	care reprezinta o celula din lista ce formeaza o linie a tabelului, 
 	cu elemente de tipul float */

t_floatCell *AllocateFloatCell(float val)

{
	t_floatCell *aux;
	aux = (t_floatCell*)malloc(sizeof(t_floatCell)); //alocarea dinamica celula de lista de tipul t_intCell
	if(!aux) //verificare alocare celula
		return NULL;
	aux->value = val; //copierea informatiei in celula de lista
	aux->next = NULL; //setarea legaturii cu alta celula din linia respectiva pe NULL
	
return aux;

}	

/* functie pentru crearea unei linii dintr-un tabel cu calori de tip string, 
	fara celula de inceput ce face legatrua cu alta linie */

t_stringCell* InsertValueString(char*values)

{
	t_stringCell *cell, *last_cell;
	t_stringCell *c = NULL;

	char* one_value = strtok(values, " "); //prima informatie din linie
	while(one_value != NULL){ //cat timp se citeste o informatie
	
		cell = AllocateStringCell(one_value); //se aloca o celula de lista
			if(!cell)
			return NULL;

		if(c == NULL){ //cazul in care este prima informatie din linie
		
			c = cell;
			last_cell = cell;
		}
		else{  //cazul in care mai exista informatii in linie
		
			last_cell->next = cell;
			last_cell = last_cell->next;
		}
	one_value = strtok(NULL, " "); //se trece la urmatorul element de inserat pe linie

	}

return c;
		
}

void ADD_LINE_STRING(t_table *table, char *val) //functie pentru adaugarea unei linii intr-un tabel cu date de tipul string

{
	t_stringLine *p, *line, *last_line;
	t_stringCell *c;
	

 	line = AllocateStringLine(); //crearea unui inceput de linie
	c = InsertValueString(val); /* crearea listei ce contine o linie de tabel, 
									fara celula ce face legatura cu linia urmatoare */
 	if(!line)
		return;
	if(table->lines == NULL){ //daca nu mai exista nicio linie in tabel
		table->lines = line;  //se leaga prima linie in tabel
		line->cells = c; //se leaga prima celula dintr-o linie cu restul liniei
	}
	//cazul in care nu se insereaza prima linie a tabelului
	else{ 
		for(p = table->lines; p != NULL; p = p->next){   /* se insereaza linia la sfarsitul celorlalte
						            						linii deja existente */
		last_line = p;
		}

		last_line->next = line;
		line->cells = c;
	}

 }


/* functie pentru crearea unei linii dintr-un tabel cu calori de tip float, 
	fara celula de inceput ce face legatrua cu alta linie */

t_floatCell* InsertValueFloat(char*values)

{
	t_floatCell *cell, *last_cell;
	t_floatCell *c = NULL;
	float one_value_float;

	char* one_value = strtok(values, " "); //prima informatie din linie
	while(one_value != NULL){ //cat timp se citeste o informatie

		one_value_float = atof(one_value);
		cell = AllocateFloatCell(one_value_float); //se aloca o celula de lista
			if(!cell)
			return NULL;

		if(c == NULL){ //cazul in care este prima informatie din linie
		
			c = cell;
			last_cell = cell;
		}
		else{ //cazul in care mai exista informatii in linie
		
			last_cell->next = cell;
			last_cell = last_cell->next;
		}
	one_value = strtok(NULL, " "); //se trece la urmatorul element de inserat pe linie

	}

return c;
		
}

void ADD_LINE_FLOAT(t_table *table, char *val) //functie pentru adaugarea unei linii intr-un tabel cu date de tipul float

{
	t_floatLine *p, *line, *last_line;
	t_floatCell *c;
	

 	line = AllocateFloatLine(); //crearea unui inceput de linie
	c = InsertValueFloat(val); /* crearea listei ce contine o linie de tabel, 
									fara celula ce face legatura cu linia urmatoare */
	if(!line)
		return;
	if(table->lines == NULL){ //daca nu mai exista nicio linie in tabel
		table->lines = line; //se leaga prima linie in tabel
		line->cells = c; //se leaga prima celula dintr-o linie cu restul liniei
	}
	//cazul in care nu se insereaza prima linie a tabelului
	else{
		for(p = table->lines; p != NULL; p = p->next){ /* se insereaza linia la sfarsitul celorlalte
						            						linii deja existente */
		
			last_line = p;
		}

		last_line->next = line;
		line->cells = c;
	}

 }


/* functie pentru crearea unei linii dintr-un tabel cu calori de tip int, 
	fara celula de inceput ce face legatrua cu alta linie */

 t_intCell* InsertValueInt(char*values)

{
	t_intCell *cell, *last_cell;
	t_intCell *c = NULL;
	int one_value_int;

	char* one_value = strtok(values, " "); //prima informatie din linie
	while(one_value != NULL){ //cat timp se citeste o informatie
	
		one_value_int = atoi(one_value);
		cell = AllocateIntCell(one_value_int); //se aloca o celula de lista
			if(!cell)
			return NULL;

		if(c == NULL){ //cazul in care este prima informatie din linie
		
			c = cell;
			last_cell = cell;
		}
		else{ //cazul in care mai exista informatii in linie
		
			last_cell->next = cell;
			last_cell = last_cell->next;
		}
	one_value = strtok(NULL, " "); //se trece la urmatorul element de inserat pe linie

	}

return c;
		
}

void ADD_LINE_INT(t_table *table, char *val) //functie pentru adaugarea unei linii intr-un tabel cu date de tipul int

{
	t_intLine *p, *line, *last_line;
	t_intCell *c;
	

 	line = AllocateIntLine(); //crearea unui inceput de linie
	c = InsertValueInt(val); /* crearea listei ce contine o linie de tabel, 
									fara celula ce face legatura cu linia urmatoare */
	if(!line)
		return;
	if(table->lines == NULL){ //daca nu mai exista nicio linie in tabel
		table->lines = line; //se leaga prima linie in tabel
		line->cells = c; //se leaga prima celula dintr-o linie cu restul liniei
	}
	//cazul in care nu se insereaza prima linie a tabelului
	else{
		for(p = table->lines; p != NULL; p = p->next){ /* se insereaza linia la sfarsitul celorlalte
						            						linii deja existente */
		
			last_line = p;
		}
		last_line->next = line; 
		line->cells = c;
	}

 }

 // functie care sterge o singura linie din tabel ce contine date de tipul int

void DELETE_INT_LINE(t_intLine *s, t_table *table)

{

   t_intCell *c, *caux;
   c = s->cells;
   t_intLine *l, *ant;

   
   if((table->lines == s) && (s->next == NULL)){ //daca linia este singura din tabel
   
   	table->lines = NULL;
   }

   else if((table->lines == s) && (s->next != NULL)){ //daca linia este prima din tabel, dar nu singura
   
   	table->lines = s->next;
   }
   else if(table->lines != s){ //daca linia nu este prima in tabel
   
   	for(l = table->lines, ant = NULL; l != NULL; ant = l, l = l->next){
   	
   		if(l == s){
   		
   			ant->next = s->next;
  
   		}
   	}
   }
    while(c){
  
   	caux = c;
   	c = c->next;
   	free(caux);
   }

}

/* functei pentru stergerea unor linii ale unui tabel
	dupa un criteriu, intr-un tabel cu date de tipul int */


void DELETE_INT(t_table *table, char *column_name, char *value, char *relation)

{
	t_column *c;
	t_intLine *s;
	t_intCell *p;
	int nr = 0;
	int i;
	
	//t_column *column;
	//column = table->columns;

	int int_value = atoi(value); //conversia valorii intr-o variabila de tipul int

	for(c = table->columns; c!= NULL; c = c->next){
		nr++; //numerotarea coloanelor
		if(strcmp(column_name, c->name) == 0){
			break;
		}
	}

	for(s = table->lines; s != NULL; s = s->next){
		
		p = s->cells;
		

		for(i = 1; i < nr; i++){
			p = p->next; //p va pointa catre celulele de sub coloana cautata
		}

		if(strcmp(relation, "<=") == 0){ //primul criteriu de comparatie

			if(p->value <= int_value){

				DELETE_INT_LINE(s, table); //se sterge linia care respecta criteriul
			}
		}

		/* analog se parcurg si celelalte criterii de comparatie,
		si anume: ">=", "<", ">", "==" si "!=" */

		if(strcmp(relation, ">=") == 0){

			if(p->value >= int_value){
				DELETE_INT_LINE(s, table);

			}
		}

		if(strcmp(relation, "<") == 0){
			if(p->value < int_value){
				DELETE_INT_LINE(s, table);
			}
		}

		if(strcmp(relation, ">") == 0){
			if(p->value > int_value){
				DELETE_INT_LINE(s, table);
			}
		}
		

		if(strcmp(relation, "==") == 0){
			if(p->value == int_value){
				DELETE_INT_LINE(s, table);
			}
		
		}

		if(strcmp(relation, "!=") == 0){
			if(p->value != int_value){
				DELETE_INT_LINE(s, table);
			}
		}
		

	}
	free(s);
}

// functie care sterge o singura linie din tabel ce contine date de tipul float

void DELETE_FLOAT_LINE(t_floatLine *s, t_table *table)
{
   t_floatCell *c, *caux;
   c = s->cells;
   t_floatLine *l, *ant;

   
   if((table->lines == s) && (s->next == NULL)){ //daca linia este singura din tabel
   
   	table->lines = NULL;
   }

   else if((table->lines == s) && (s->next != NULL)){ //daca linia este prima din tabel, dar nu singura
   
   	table->lines = s->next;
   }
   else if(table->lines != s){ //daca linia nu este prima in tabel
   
   	for(l = table->lines, ant = NULL; l != NULL; ant = l, l = l->next){
   	
   		if(l == s){
   		
   			ant->next = s->next;
  
   		}
   	}
   }
    while(c){
  
   	caux = c;
   	c = c->next;
   	free(caux);
   }

}

/* functei pentru stergerea unor linii ale unui tabel
	dupa un criteriu, intr-un tabel cu date de tipul float */

void DELETE_FLOAT(t_table *table, char *column_name, char *value, char *relation)
{
	t_column *c;
	t_floatLine *s;
	t_floatCell *p;
	int nr = 0;
	int i;
	
	// t_column *column;
	// column = table->columns;

	float float_value = atof(value); //conversia valorii intr-o variabila de tipul float

	for(c = table->columns; c!= NULL; c = c->next){
		nr++; //numerotarea coloanelor
		if(strcmp(column_name, c->name) == 0){
			break;
		}
	}

	for(s = table->lines; s != NULL; s = s->next){
		
		p = s->cells;
		

		for(i = 1; i < nr; i++){
			p = p->next; //p va pointa catre celulele de sub coloana cautata
		}

		if(strcmp(relation, "<=") == 0){ //primul criteriu de comparatie

			if(p->value <= float_value){

				DELETE_FLOAT_LINE(s, table); //se sterge linia care respecta criteriul
			}
		}

		/* analog se parcurg si celelalte criterii de comparatie,
		si anume: ">=", "<", ">", "==" si "!=" */

		if(strcmp(relation, ">=") == 0){

			if(p->value >= float_value){
				DELETE_FLOAT_LINE(s, table);

			}
		}

		if(strcmp(relation, "<") == 0){
			if(p->value < float_value){
				DELETE_FLOAT_LINE(s, table);
			}
		}

		if(strcmp(relation, ">") == 0){
			if(p->value > float_value){
				DELETE_FLOAT_LINE(s, table);
			}
		}
		

		if(strcmp(relation, "==") == 0){
			if(p->value == float_value){
				DELETE_FLOAT_LINE(s, table);
			}
		
		}

		if(strcmp(relation, "!=") == 0){
			if(p->value != float_value){
				DELETE_FLOAT_LINE(s, table);
			}
		}
		

	}
	free(s);
}

// functie care sterge o singura linie din tabel ce contine date de tipul string

void DELETE_STRING_LINE(t_stringLine *s, t_table *table)

{

   t_stringCell *c, *caux;
   c = s->cells;
   t_stringLine *l, *ant;

   
   if((table->lines == s) && (s->next == NULL)){ //daca linia este singura din tabel
   
   	table->lines = NULL;
   }

   else if((table->lines == s) && (s->next != NULL)){ //daca linia este prima din tabel, dar nu singura
   
   	table->lines = s->next;
   }

   else if(table->lines != s){ //daca linia nu este prima in tabel
   
   	for(l = table->lines, ant = NULL; l != NULL; ant = l, l = l->next){
   	
   		if(l == s){
   		
   			ant->next = s->next;
  
   		}
   	}
   }
    while(c){
  
   	caux = c;
   	c = c->next;
   	free(caux);
   }

}

/* functei pentru stergerea unor linii ale unui tabel
	dupa un criteriu, intr-un tabel cu date de tipul string */

void DELETE_STRING(t_table *table, char *column_name, char *value, char *relation)
{
	t_column *c;
	t_stringLine *s;
	t_stringCell *p;
	int nr = 0;
	int i;

	for(c = table->columns; c!= NULL; c = c->next){
		nr++; //numerotarea coloanelor
		if(strcmp(column_name, c->name) == 0){
			break;
		}
	}

	for(s = table->lines; s != NULL; s = s->next){
		
		p = s->cells;
		

		for(i = 1; i < nr; i++){
			p = p->next; //p va pointa catre celulele de sub coloana cautata
		}

		if(strcmp(relation, "<=") == 0){ //primul criteriu de comparatie

			if(strcmp(p->value, value) <= 0){

				DELETE_STRING_LINE(s, table); //se sterge linia care indeplineste criteriul
			}
		}

		/* analog se parcurg si celelalte criterii de comparatie,
		si anume: ">=", "<", ">", "==" si "!=" */

		if(strcmp(relation, ">=") == 0){

			if(strcmp(p->value, value) >= 0){
				DELETE_STRING_LINE(s, table);

			}
		}

		if(strcmp(relation, "<") == 0){
			if(strcmp(p->value, value) < 0){
				DELETE_STRING_LINE(s, table);
			}
		}

		if(strcmp(relation, ">") == 0){
			if(strcmp(p->value, value) > 0){
				DELETE_STRING_LINE(s, table);
			}
		}
		

		if(strcmp(relation, "==") == 0){
			if(strcmp(p->value, value) == 0){
				DELETE_STRING_LINE(s, table);
			}
		
		}

		if(strcmp(relation, "!=") == 0){
			if(strcmp(p->value, value) != 0){
				DELETE_STRING_LINE(s, table);
			}
		}
		

	}
	free(s);
}


/* functie pentru dezalocarea memoriei a tuturor liniilor dintr-un tabel ce
	contine date de tipul string */

void CLEAR_STRING_LINES(t_table *table)

{
	t_stringLine *s, *saux;
	t_stringCell *c, *aux;
	s = table->lines;
	c = s ->cells;

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

/* functie pentru dezalocarea memoriei a tuturor liniilor dintr-un tabel ce
	contine date de tipul float */

void CLEAR_FLOAT_LINE(t_table *table)

{
	t_stringLine *s, *saux;
	t_stringCell *c, *aux;
	s = table->lines;
	c = s ->cells;
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

/* functie pentru dezalocarea memoriei a tuturor liniilor dintr-un tabel ce
	contine date de tipul int */

void CLEAR_INT_LINE(t_table *table)

{
	t_stringLine *s, *saux;
	t_stringCell *c, *aux;
	s = table->lines;
	c = s ->cells;
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
