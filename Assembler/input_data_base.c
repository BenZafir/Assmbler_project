#include "header.h"


/*---------------------------------------------------------funcs for input data base (per line)-----------------------------------*/


 /*database_get_pointer_to_*/

input_data* get_data_base()
{
	static input_data data;
	return &data;
}

int data_set_line(FILE* file)
{
	input_data* data;
	data = get_data_base();
	if (fgets(data->line, MAX_LINE_LEN, file) == NULL)
		return EOF;
	return OK;

}

char* data_get_line()
{
	input_data* data;
	data = get_data_base();
	return data->line;
}


char** data_get_lable()
{
	input_data* data;
	data = get_data_base();
	return &(data->lable);
}

char** data_get_command()
{
	input_data* data;
	data = get_data_base();
	return &(data->command);
}

char* data_get_command_type()
{
	input_data* data;
	data = get_data_base();
	return &(data->command_type);
}


char** data_get_value()
{
	input_data* data;
	data = get_data_base();
	return &(data->str_value);
}

int* data_get_num_value()
{
	input_data* data;
	data = get_data_base();
	return &(data->num_of_values);
}

value_and_mode** data_get_value_arr()										/*geting a pinter to a array of structs that store the values */
{
	input_data* data;
	data = get_data_base();
	return &(data->values_arr);
}
