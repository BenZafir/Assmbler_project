#include "header.h"

/*---------------------------------------------------------line_reader-----------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*those functions are responsable to break down the input line to its basic compunents in order to make the necessary information easy accessible to the all other functions in assembler program */
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*this function getting the input line and delete the new line char (\n) and the CR char(/r) if exist. this function also determin if the corrent line is a comment line (if it begin with ';') or a line to which is need to be prossesed*/
int get_input(FILE* file)
{
	int i;
	int input_size;
	char* line;
	if (data_set_line(file) == EOF)												/*setting the next input line in the data_base. if there is no more input return EOF*/
		return EOF;
	line = data_get_line();
	input_size = strlen(line);
	if (input_size != 0)														/*getting the line lenth*/
	{
		if (line[input_size - 1] == NEW_LINE_LINX) 
			line[input_size - 1] = END_STRING;									/*delete the new line char(\n)*/

		input_size = strlen(line);												/*getting the new line lenth*/

		if (line[input_size - 1] == NEW_LINE_MAC)
			line[input_size - 1] = END_STRING;									/*delete the CR char(\r) if exist*/
	}
	

	input_size = strlen(line);													/*getting the new line lenth*/

	
	for (i = 0; i <= input_size; i++)											/*determin if the corrent line is a comment line (if it begin with ';') or a line to which is need to be prossesed */
	{
		if ((line[i] == SPACE) || (line[i] == TAB));							/*ignoring leading spaces and tabs)*/
		else if ((line[i] == COMMENT_SYMBOL) || (line[i] == END_STRING))		/*determin if the corrent line is a comment line (if it begin with ';' or \n)*/
		{
			return COMMENT;
		}
		else
			break;																/*the corrent line is not a comment line */
	}

	get_lable();																/*calling to a function that get the label from the input line and put it in input_data_base */
	get_command();																/*calling to a function that get the command from the input line and put it in input_data_base */
	get_value();																/*calling to a function that get the values from the input line and put it in input_data_base */

	return 	OK;
}


/*this function get the label component from the input line and put it in input_data_base */
void get_lable()
{
	char* command_begin;
	char* line;
	char** label;
	char** command;
	command=data_get_command();													/*get the address of the "command" variable in data_base*/
	line = data_get_line();														/*get the input from data_base*/
	label = data_get_lable();													/*get the address of the "label" variable in data_base*/
	*label = trim_space(line);													/*trim space from the input and store it in label variable in data_base*/
	if (!((command_begin = strstr(*label, LABEL_END_AND_SPACE)) || (command_begin = strstr(*label, LABEL_END_AND_TAB)))) /*check if there is a char that indicate end of label. if not, label = NULL else put label string in the variable */
	{
		*command = *label;
		*label = NULL;
	}
	else
	{
		*command = command_begin + 1;
		*command_begin = END_STRING;
	}

}


/*this function get the command component from the input line and put it in input_data_base */
void get_command()
{
	int i;
	int command_size;
	char** command;
	char** value;
	command = data_get_command();												/*get the address of the "command" variable in data_base*/
	value = data_get_value();													/*get the address of the "value" variable in data_base*/
	*command = trim_space(*command);											/*trim space from the input and store it in command variable in data_base*/

	command_size = strlen(*command);

	for (i = 0; i < command_size; i++)											/*check where is the first space (becouse there is where the command component ends)*/
	{
		if ((*command)[i] == SPACE || (*command)[i] == TAB)
			break;
	}

	if (i < command_size)														/*put \0 where the command component ends and pu the rest in the value variable*/
	{
		*value = (*command) + i + 1;
		*((*command) + i) = END_STRING;
	}
	else 
		*value = (*command) + i;
	

	get_command_type();															/*getting the command type ('c'- commands like mov,add,sub... ; 'd'-data ; 's'-string ; 'i'-entry ; 'x'-extern ; 'e'- error or invalid command )*/
}



/*this function get the value component from the input line and put it in input_data_base (and in value_arr)*/
void get_value()
{
	int i;
	int j = 1;
	int value_size;
	char** value;
	int* num_of_values;
	value_and_mode** value_arr;

	value_arr = data_get_value_arr();											/*get the address of the "value_arr" variable in data_base*/
	num_of_values = data_get_num_value();										/*get the address of the "num of value" variable in data_base*/
	value = data_get_value();													/*get the address of the "value" variable in data_base*/
	(*num_of_values) = 1;														/*starting with the assumption that there is 1 value*/
	*value = trim_space(*value);												/*trim space in the "value" variable and store it in again in value variable in data_base*/
	value_size = strlen(*value);

	for (i = 0; i < value_size; i++)											/*this loop check how many commas there are in the input (this number + 1 is the number of the values in this line)*/
	{
		if ((*value)[i] == COMMA)
			(*num_of_values)++;
	}

	if ((**value) == END_STRING)												/*if there is no string in the value section, there are no values*/
	{
		*num_of_values = ZERO;
		*value_arr = NULL;
		return;
	}

	if ((*value_arr = (value_and_mode*)calloc((*num_of_values), sizeof(value_and_mode))) == NULL)	/*allocating space for the values array*/
	{
		print_error(MALLOC_FAILURE_CODE);
		exit(EXIT_FAILURE);
	}

	((*value_arr)->value) = (*value);											
	
	for (i = 0; i < value_size; i++)											/*this loop divade the value string (for every comma it finds) and put every diffrent value in deffrent cell in the value array*/
	{
		if ((*value)[i] != COMMA);
		else
		{
			(*value)[i] = END_STRING;
			((*value_arr) +j)->value = (*value) + i + 1;
			((*value_arr) +j)->value = trim_space(((*value_arr) + j)->value);
			((*value_arr) + j - 1)->value = trim_space(((*value_arr) + j - 1)->value);
			j++;
		}
	}

	for (i = 0; i < *num_of_values; i++)									/*this loop give every diffrent value in the value array a char that indicate its type ('c'-command, 'd'-data , 's'-string , 'i'-entry , 'x'-extern , 'e'- error) */
	{
		(*value_arr + i)->value_mode = check_val_type((*value_arr + i)->value);
	}
	
}






