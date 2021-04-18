
/***************************************************includes***************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/***************************************************************************************************************/
/*************************************************** macros ****************************************************/
/***************************************************************************************************************/

 /***************************************************macro to reset counters***************************************************/

 /*A macro to reset counters befor first pass*/
#define RESET_COUNTERS ic_back_to_start();\
dc_back_to_start();\
error_cunter_back_to_start();\
line_num_back_to_start();\
entry_extern_back_to_start();

/***************************************************macro to open files***************************************************/

 /*A macro to try to open a file for writing*/
#define TRY_FOPEN_WRITE(poiner, name)\
if ((poiner = fopen(name, "w+")) == NULL)\
{\
	print_error(FOPEN_FAILURE_CODE);\
	exit(EXIT_FAILURE);\
}

/***************************************************macro to check if- letter or number***************************************************/

#define IS_A_NUMBER_OR_LETTER(pointer) (((pointer) < ASCII_NUMBERS_START) || ((pointer) > ASCII_NUMBERS_END)) && (((pointer) < ASCII_ABC_START) || ((pointer) > ASCII_ABC_END)) && (((pointer) < ASCII_ABC_UPERCASE_START) || ((pointer) > ASCII_ABC_UPERCASE_END))

/***************************************************macro to check if- letter***************************************************/

#define IS_A_LETTER(pointer) (((pointer) < ASCII_ABC_START) || ((pointer) > ASCII_ABC_END)) && (((pointer) < ASCII_ABC_UPERCASE_START) || ((pointer) > ASCII_ABC_UPERCASE_END))


/*************************************************** files open mode and name ending ***************************************************/

#define OPEN_FOR_READ "r"					/*A string for fopen*/
#define ASSEMBLY_FILE_ENDING ".as"			/*An end string for the source file*/
#define OBJECT_FILE_ENDING ".ob"			/*An end string for the object file*/
#define EXTERN_FILE_ENDING ".ext"			/*An end string for the extern file*/
#define ENTERY_FILE_ENDING ".ent"			/*An end string for the entry file*/
#define TEMP_FILE_NAME "tmp_data.tmp"		/*An temporary file to contain the data line before attaching it to the end of "object" file*/



/*************************************************** OP codes ***************************************************/

#define MOV_OP 0															/*An OP code for mov*/
#define CMP_OP 1															/*An OP code for cmp*/
#define ADD_SUB_OP 2														/*An OP code for add and sub*/
#define LEA_OP 4															/*An OP code for lea*/
#define CLR_NOT_INC_DEC_OP 5												/*OP code for clr, not, inc and dec*/
#define JMP_BNE_JSR_OP 9													/* OP code for mov jmp, bne and jsr*/
#define RED_OP 12															/*An OP code for red*/
#define PRN_OP 13															/*An OP code for prn*/
#define RTS_OP 14															/*An OP code for rts*/
#define STOP_OP 15															/*An OP code for stop*/

/*************************************************** func codes ***************************************************/

#define FUNC_IS_ZERO 0														/*func code 0*/
#define FUNC_IS_10 10														/*func code 10*/
#define FUNC_IS_11 11														/*func code 11*/
#define FUNC_IS_12 12														/*func code 12*/
#define FUNC_IS_13 13														/*func code 13*/


/*************************************************** number of lines needed for command ***************************************************/

#define ONE_LINES 1															/*commmands that translated to 1 line in the object file*/
#define TWO_LINES 2															/*commmands that translated to 2 line in the object file*/
#define TREE_LINES 3														/*commmands that translated to 3 line in the object file*/


/*************************************************** allowed modes for command ***************************************************/

#define MODE_IMMED_DIRECT_REG "013"											/*A string of allowed address modes*/
#define MODE_DIRECT_REG "13"												/*A string of allowed address modes*/
#define MODE_DIRECT_RELAT "12"												/*A string of allowed address modes*/
#define MODE_DIRECT "1"														/*A string of allowed address mode*/
#define NO_MODE_ALLOWED ""													/*no address mode is allowed*/


/*************************************************** save words in language ***************************************************/

#define DATA ".data"
#define STRING ".string"
#define EXTERN ".extern"
#define ENTERY ".entry"


/*************************************************** command type in one char ***************************************************/

#define ERROR_VAL 'e'															/*A char that represent error in the command or value*/
#define ENTRY_COMMAND_TYPE 'i'													/*A char that represent entry type in the command or value*/
#define EXTERN_COMMAND_TYPE 'x'													/*A char that represent extern type in the command or value*/
#define INSTRUC_COMMAND_TYPE 'c'												/*A char that represent regular command type in the command or value*/
#define DATA_COMMAND_TYPE 'd'													/*A char that represent data type in the command or value*/
#define STRING_COMMAND_TYPE 's'													/*A char that represent string type in the command or value*/

/*************************************************** address modes ***************************************************/
#define MODE_IMMED_CHAR '0' 													/*A char that represent immediate address mode*/
#define MODE_DIRECT_CHAR '1'  													/*A char that represent direct address mode*/
#define MODE_RELATIVE_CHAR '2' 													/*A char that represent relative address mode*/
#define MODE_REGISTER_CHAR '3'  												/*A char that represent register address mode*/

/*************************************************** more chars for address mode function ***************************************************/

#define IMMED_MODE_BEGIN_CHAR '#' 												/*A char that indicating this is an immediate addressing mode value*/
#define RELATIVE_MODE_BEGIN_CHAR '%' 											/*A char that indicating this is an relative addressing mode value*/

/*************************************************** ABSOLUTE, RELOCATABLE and EXTERNAL feature ***************************************************/

#define ABSOLUTE 'A'															/*A char to indicate that this line is absolute*/
#define RELOCATABLE 'R'															/*A char to indicate that this line is relocatable*/
#define EXTERNAL 'E'															/*A char to indicate that this line is external*/

/*************************************************** numbers of steps for bitwise functions ***************************************************/

#define EGHIT_STEPS 8							
#define FOUR_STEPS 4
#define TWO_STEPS 2

/*************************************************** maximums and constants ***************************************************/

#define MAX_SYMBOL_LEN 20														/*max symbole name lengh*/
#define MAX_NAME_LEN 35															/*max file name lengh*/
#define MAX_NAME_ENDING_LEN 5													/*max file ending name lengh (like .ob .ext...)*/
#define MIN_NAME_LEN 1															/*min file name lengh*/
#define CONSTANT_CHAR_NAME 10													/*register or command name lengh*/
#define ALLOWED_ADDR_MODE 5														/*allowed addressing mode string lengh*/
#define NUM_OF_COMMANDS 16														/*total number of commands (mov,add,sub...)*/
#define NUM_OF_REGISTERS 8														/*total number of registers*/
#define MASK_FOR_12_BITS 4095													/*the mazimum number 12 bit can represent*/
#define MAX_NUM_IN_12_BITS 2047													/*the mazimum number 12 bit can represent*/
#define MIN_NUM_IN_12_BITS -2048												/*the mazimum number 12 bit can represent*/
#define MAX_LINE_LEN 100														/*max lengh of one line in input*/
#define LINE_START_CUNT 1 														/*the first number to start count lines in input*/
#define IC_START_CUNT 100 														/*the first number to start count IC*/
#define DC_START_CUNT 0 														/*the first number to start count DC*/
#define ERROR_CUNTER_START_CUNT 0 												/*the first number to start count errors in code*/

#define NOT_OK 0 																/*return value if someting worng*/
#define OK 1																	/*return value if all ok*/
#define NO_VAL -1																/*return value if no value found*/
#define COMMENT 2																/*return value to indicate comment in input*/


/*************************************************** useful chars ***************************************************/
#define NEW_LINE_LINX '\n'
#define NEW_LINE_MAC '\r'
#define END_STRING '\0'
#define COMMA ','
#define COMMENT_SYMBOL ';'
#define TAB '\t'
#define SPACE ' '
#define POINT "."																/*string of only 1 point*/
#define QUOTE_MARK '\"'
#define EMPTY_STRING ""

/*************************************************** useful strings ***************************************************/

#define LABEL_END_AND_SPACE ": "												/*string indicating end of label and space*/
#define LABEL_END_AND_TAB ":\t"													/*string indicating end of label and tab*/
#define WORKING_ON "working on - %s\n\n"										/*print for the user when starting to work on new file*/
#define SUCCESS "success!\n\n"													/*print for the user when finish to work on a file successfully */
/*print for the user when finish to work on a file with errors */
#define ERROR_IN_SOURCE_FILE "There was some errors in the source file. output files are not created for this file.\n\n "

/*************************************************** printf formats ***************************************************/

#define OB_FILE_PRINT_TITEL "\t%d %d\n"
#define OB_FILE_PRINT_FORMAT "%.4d\t%.3X\t%c\n"
#define ENT_OR_EXT_FILE_PRINT_FORMAT "%s\t%.4d\n"
#define ERROR_LINE_NUMBER "Error in line number- %d: %s \n"


/*************************************************** errors codes ***************************************************/

#define INVALID_LABALE_CODE 401
#define INVALID_COMMAND_CODE 402
#define MALLOC_FAILURE_CODE 403
#define TOO_MANY_VAL_CODE 405
#define TOO_FEW_VAL_CODE 406
#define INVALID_VAL_CODE 407
#define DOPLICAT_LABLES_CODE 408
#define INVALID_DEST_CODE 409
#define INVALID_SOUR_CODE 410
#define NO_SUCH_LABALE_IN_CODE 411
#define FTELL_FAILURE_CODE 412
#define FSEEK_FAILURE_CODE 413
#define FOPEN_FAILURE_CODE 414
#define FILE_NAME_CODE 415
#define ENTRY_AND_EXTERN_CODE 416


/*************************************************** errors strings ***************************************************/

#define INVALID_LABALE_STRING "there is an invalid name to a label (structure: <label:> <command> <value>,<...>)"
#define INVALID_COMMAND_STRING "there is an invalid name to a command (structure: <label:> <command> <value>,<...>)"
#define MALLOC_FAILURE_STRING "error in geting new space with malloc or calloc. the pogram can't continue"
#define TOO_MANY_VAL_STRING "there are too many values."
#define TOO_FEW_VAL_STRING "there are too few values."
#define INVALID_VAL_STRING "there are invalid names to values (structure : <label : > <command> <value>, <...>)"
#define DOPLICAT_LABLES_STRING "doplicat labels, this label already exist"
#define INVALID_DEST_STRING "there is invalid value to the value that represent the destnation mode"
#define INVALID_SOUR_STRING "there is invalid value to the value that represent the source mode"
#define NO_SUCH_LABALE_IN_STRING "one of the value that refer to address by label refer to a label name that does not exist"
#define FTELL_FAILURE_STRING "error in reading position from file by ftell func. the pogram can't continue"
#define FSEEK_FAILURE_STRING "error in put a position to a file by using fseek func. the pogram can't continue"
#define FOPEN_FAILURE_STRING "failure in tring to open a file. the pogram can't continue"
#define FILE_NAME_STRING "error in the file name. please check it agian"
#define ENTRY_AND_EXTERN_STRING "there is a label that has been defined both entry and extern"


/*************************************************** worning codes ***************************************************/

#define EXTERN_LABEL_WORNING_CODE 501
#define ENTRY_LABEL_WORNING_CODE 502
#define VAL_BIGER_2047_OR_SMOLLER_MINUS_2048_CODE 503

/*************************************************** worning strings ***************************************************/

#define EXTERN_LABEL_WORNING_STRING "Worning: There is a label before extern command, which is meaningless"
#define ENTERY_LABEL_WORNING_STRING "Worning: There is a label before entry command, which is meaningless"
#define VAL_BIGER_2047_OR_SMOLLER_MINUS_2048_STRING "Worning: there is a value that biger then 2047 or smaller then -2048. the full number can not be represented in 12 bits"
/*************************************************** others ***************************************************/

#define ZERO 0
#define ASCII_OF_0 48
#define ASCII_ABC_START 'a'
#define ASCII_ABC_END 'z'
#define ASCII_ABC_UPERCASE_START 'A'
#define ASCII_ABC_UPERCASE_END 'Z'
#define ASCII_NUMBERS_START '0'
#define ASCII_NUMBERS_END '9'
#define ASCII_TABLE_ALL_START 1 /*the first ligal char in the ascii table (after \0)*/
#define ASCII_TABLE_ALL_END 127  /*last ligal char in the ascii table*/

#define PLUS '+'
#define MINUS '-'

#define NEITHER_CHAR 'n'							/*represent a situation that we haven't seen entry or extern yet */
#define BOTH_CHAR 'b'								/*represent a situation that we already haven seen entry and extern */

/***************************************************************************************************************/
/*************************************************** structs ***************************************************/
/***************************************************************************************************************/

typedef struct										/*a struct to make it easer to send file pointers for output */
{
	FILE* ob;
	FILE* ent;
	FILE* ext;
	FILE* tmp_data;
} OUTPUT_FILE;

typedef struct sym_cell								/*a struct for symbol table */
{
	char symbol[MAX_SYMBOL_LEN];
	int value;
	char attributes;
	struct sym_cell* next;
	struct sym_cell* prev;

} symbol_cell;



typedef struct 										/*a struct for commands in the constant table */
{
	int serial_num;
	char name[CONSTANT_CHAR_NAME];
	int opcode;
	int funct;
	char allowed_sour_addr_mode[ALLOWED_ADDR_MODE];
	char allowed_dest_addr_mode[ALLOWED_ADDR_MODE];
	int num_of_needed_lines;

} command_list;

typedef struct 										/*a struct for registers in the constant table */
{

	int serial_num;
	char name[CONSTANT_CHAR_NAME];
	int register_bit_on;

} register_list;

typedef struct  										/*a struct represent values by string and type (mode) */
{
	char* value;
	char value_mode;
} value_and_mode;

typedef struct  										/*a struct represent data-base which contain all information needed for every line in the input */
{
	char line[MAX_LINE_LEN];  							/*copy of the line from the input*/
	char* lable;  										/*save the label name if any*/
	char* command;  									/*save the command name*/
	char command_type;  								/*save the command type*/
	int num_of_values;  								/*save the number of values comming after the command (separated by ",") */
	char* str_value;									/*save the values in one (unseparated) string*/
	value_and_mode* values_arr;  						/*save the values and ther type (already separated)*/


} input_data;


/***************************************************************************************************************/
/*************************************************** prototypes ***************************************************/
/***************************************************************************************************************/




/*************************************************** prototypes funcs_for_auxiliary_structs ***************************************************/


char* data_get_line();
int data_set_line(FILE* file);
char** data_get_lable();
char** data_get_command();
char** data_get_value();
char* data_get_command_type();
int* data_get_num_value();
value_and_mode** data_get_value_arr();


/*************************************************** prototypes for constants_table ***************************************************/

int get_command_serial_num_by_name(char* name);
char* get_command_table_name(int serial_num);
int get_command_table_opcode(int serial_num);
int get_command_table_funct(int serial_num);
char* get_command_table_sour_mode(int serial_num);
char* get_command_table_dest_mode(int serial_num);
int get_command_table_needed_lines(int serial_num);

/*registers*/

register_list* get_register_table();
char* get_register_table_name(int serial_num);



/*************************************************** prototypes for line_break_down ***************************************************/
int get_input(FILE*);
void get_lable();
void get_command();
void get_value();


/*************************************************** prototypes for line_syntactic_analysis ***************************************************/

int check_line();
void get_command_type();
int check_lable(char* lable);
char check_val_type(char*);




/*************************************************** prototypes for error_printer ***************************************************/

void print_error(int error_num);
void print_worning(int worning_num);


/*************************************************** prototypes for program_counters ***************************************************/

 /*ic*/

int get_ic();
void increment_ic(int num);
void ic_back_to_start();

/*dc*/

int get_dc();
void increment_dc(int num);
void dc_back_to_start();

/*error conter*/

int get_error_cunter();
void increment_error_counter();
void error_cunter_back_to_start();

/*line number*/

int get_line_num();
void next_line_num();
void line_num_back_to_start();


/*************************************************** prototypes for symbol_table ***************************************************/
void set_symbol_val(char* symbol, int value, char attributes);
char* get_symbol_symbol(int index);
int check_symbol_by_name(char* label);
int get_symbol_value(int index);
int add_to_symbol_value(int index, int add_val);
char get_symbol_attributes(int index);
void symbol_free_all();




/*************************************************** prototypes for first_pass ***************************************************/
int first_pass(FILE* file);




/*************************************************** prototypes for second_pass ***************************************************/
void second_pass(FILE* file);




/*************************************************** prototypes for output_printer ***************************************************/
void output_printer(OUTPUT_FILE* output, FILE* file);



/*************************************************** prototypes for auxiliary_functions ***************************************************/

int check_space(char* value);
char* trim_space(char*);

char is_there_entry_or_extern();
void update_entry_extern(char update);
void entry_extern_back_to_start();