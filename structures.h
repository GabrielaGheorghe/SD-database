/* GHEORGHE Luminita-Gabriela - 312 CB */
#ifndef __STRUCTURES__
#define __STRUCTURES__

#define MAX_COLUMN_NAME_LEN 30
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300

// int
typedef struct intCell {
	int    value;
	struct intCell* next;
} t_intCell;

typedef struct intLine {
	t_intCell*      cells;
	struct intLine* next;
} t_intLine;

// float
typedef struct floatCell {
	float  value;
	struct floatCell* next;
} t_floatCell;

typedef struct floatLine {
	t_floatCell*      cells;
	struct floatLine* next;
} t_floatLine;

// string
typedef struct stringCell {
	char*  value;
	struct stringCell* next;
} t_stringCell;

typedef struct stringLine {
	t_stringCell*       cells;
	struct stringLine* next;
} t_stringLine;

// cell type
typedef enum {
	INT,
	FLOAT,
	STRING
} t_cellType;

// column
typedef struct column {
	char name[MAX_COLUMN_NAME_LEN];
	struct column* next;
} t_column;

// table
typedef struct table {
	char name[MAX_TABLE_NAME_LEN];
	t_cellType    type;
	t_column*     columns;
	void*         lines;  // t_intLine* | t_floatLine* | t_stringLine*
	struct table* next;
} t_table;

// database
typedef struct db {
	char name[MAX_DB_NAME_LEN];
	t_table* tables;
} t_db;



/* definire functii utilizate */



/* Data Definition */

t_db* INIT_DB(char name[MAX_DB_NAME_LEN]);
t_column *AllocateColumn(char column_name[MAX_COLUMN_NAME_LEN]);
void CREATE(t_db **database, char name_table[MAX_TABLE_NAME_LEN], char *data_type, char *column_names);
void DEZALOC_STRING(t_table *table);
void DELETE_STRING_TABLE(t_db **database, t_table *table);
void DEZALOC_FLOAT(t_table *table);
void DELETE_FLOAT_TABLE(t_db **database, t_table *table);
void DEZALOC_INT(t_table *table);
void DELETE_INT_TABLE(t_db **database, t_table *table);

/*Data Query*/

void PRINT_FLOAT(t_table *table);
void PRINT_STRING(t_table *table);
int Number(int nr);
void PRINT_INT(t_table *table);
void PRINT(t_table *table);
void PRINT_DB(t_db **database);
void PRINT_INT_LINE(t_intLine *s);
void PRINT_FLOAT_LINE(t_floatLine *s);
void PRINT_STRING_LINE(t_stringLine *s);
void PRINT_INTRO(t_column *column);
void SEARCH_INT(t_table *table, char *column_name, char *value, char *relation);
void SEARCH_FLOAT(t_table *table, char *column_name, char *value, char *relation);
void SEARCH_STRING(t_table *table, char *column_name, char *value, char *relation);

/*Data Manipulation*/

t_stringLine *AllocateStringLine();
t_stringCell *AllocateStringCell(char *val);
t_intLine *AllocateIntLine();
t_intCell *AllocateIntCell(int val);
t_floatLine *AllocateFloatLine();
t_floatCell *AllocateFloatCell(float val);
t_stringCell* InsertValueString(char*values);
void ADD_LINE_STRING(t_table *table, char *val);
t_floatCell* InsertValueFloat(char*values);
void ADD_LINE_FLOAT(t_table *table, char *val);
t_intCell* InsertValueInt(char*values);
void ADD_LINE_INT(t_table *table, char *val);
void DELETE_INT_LINE(t_intLine *s, t_table *table);
void DELETE_INT(t_table *table, char *column_name, char *value, char *relation);
void DELETE_FLOAT_LINE(t_floatLine *s, t_table *table);
void DELETE_FLOAT(t_table *table, char *column_name, char *value, char *relation);
void DELETE_STRING_LINE(t_stringLine *s, t_table *table);
void DELETE_STRING(t_table *table, char *column_name, char *value, char *relation);
void CLEAR_STRING_LINES(t_table *table);
void CLEAR_FLOAT_LINE(t_table *table);
void CLEAR_INT_LINE(t_table *table);


#endif