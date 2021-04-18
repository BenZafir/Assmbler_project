
#include "header.h"

/*This function going through the input line after line and it checks the Symbole Table with all the libels it had saw in the source code while going through the input
it also going through all the data labels and adding the IC number to them (so the data section will show up after the command section)*/
void second_pass(FILE* file)
{
	int input_retern_val;
	int i;
	int index;
	int corrent_ic;
	char command_type;
	value_and_mode* value_arr;
	int num_value;
	char symbol_attributes;

	rewind(file);																					/*making sure to read the input from the begining*/
	line_num_back_to_start();																		/*bring the line counter to the start*/
	corrent_ic = get_ic();																			/*getting the corrent number of lines in the IC*/

/*At the end of the first pass, the assembler updates the symbol table, each symbol characterized as data.
Adding (100 + (IC) decimal) to the value of the symbol. This is because in the overall picture of code
the data image is separated from the instruction image, and all data is required to appear in the machine code
after all the instructions*/
	i = 0;
	while ((symbol_attributes = get_symbol_attributes(i)) != END_STRING)							
	{
		if (symbol_attributes == DATA_COMMAND_TYPE || symbol_attributes == STRING_COMMAND_TYPE)		/*going through all the data labels*/
			add_to_symbol_value(i, corrent_ic);														/*adding the IC number to all data section labels*/
		i++;
	}


	/*going through the input untill EOF (and ignoring comments)*/
	while ((input_retern_val = get_input(file)) != EOF)												
	{
		if (input_retern_val == COMMENT)															/*ignoring comments and increment the line counter (source code line counter)*/
		{
			next_line_num();
			continue;																				
		}

		command_type = *data_get_command_type();													/*geting the char that symbolize the corrent command type ('c'- commands ; 'd'-data ; 's'-string ; 'i'-entry ; 'x'-extern ; 'e'- error )*/
		value_arr = *data_get_value_arr();															/*geting a pinter to a array of structs that store the values */
		num_value = *data_get_num_value();															/*geting the number of values in the corrent line */

		/*check that every "direct address mode" value (label value) is a label that appearing in the symbol table, if one of the value is a label that doesn't appeared in the symbol table, it sends an error massage*/
		if ((command_type == INSTRUC_COMMAND_TYPE) || (command_type == ENTRY_COMMAND_TYPE))
		{
			for (i = 0; i < num_value; i++)
			{

				if (((value_arr + i)->value_mode) == MODE_DIRECT_CHAR)
				{
					index = check_symbol_by_name((value_arr + i)->value);
					if (index == NO_VAL)
					{
						print_error(NO_SUCH_LABALE_IN_CODE);
					}
				}
			}
			/*check if there is a label in entry command (as a value) that has already been definded as extern (if so, it sends an error massage)*/
			if ((command_type == ENTRY_COMMAND_TYPE) && (num_value !=0))
			{
				index = check_symbol_by_name((value_arr)->value);								/*this line checking the first value becouse entry command can be correct only if it has only one correct value.*/
				if (get_symbol_attributes(index) == EXTERN_COMMAND_TYPE)
				{
					print_error(ENTRY_AND_EXTERN_CODE);
				}
			}

		}

		next_line_num();																		/*increment the line counter to the next line*/
		if (num_value > ZERO)																	/*if there are values saved for this line, free it. (freeing calloc)*/
			free(*data_get_value_arr());														/*free values that was saved for this line*/
	}
}