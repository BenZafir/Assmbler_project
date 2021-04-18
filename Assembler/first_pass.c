
#include "header.h"
 /*this function going through the input line after line and if the line is ok syntactly, it fill up the Symbole Table with all the libels it have seen in the source code while going through it*/
int first_pass(FILE* file)
{
	char* label;
	int input_retern_val;														/*a flag that say if the input line is ok or not ok or a comment*/
	int index;
	int corrent_ic;
	int corrent_dc;
	char command_type;
	value_and_mode* value_arr;													/*a pinter to an array of structs that store the values (that cames after the command) */
	int num_value;

	RESET_COUNTERS																/*a macro to reset counters before strting to going through new input code */
	
	while ((input_retern_val = get_input(file)) != EOF)							/*a loop that looping untill EOF, and update the input_retern_val flag for every line */
	{
		if (input_retern_val == COMMENT)										/*if the the line if commant type, there is nothing to do */
		{
			next_line_num();													/*increment the line counter to the next line*/
			continue;															/*go to the next input line*/
		}
			
		
		num_value = *data_get_num_value();										/*geting the number of values after the command*/

		if (check_line() != OK)													/*checking if the input line is syntacly correct */
		{
			next_line_num();													/*increment the line counter to the next line*/
			if(num_value> ZERO)													/*if there are values saved for this line, free it. (freeing calloc)*/
				free(*data_get_value_arr());									/*free values that was saved for this line*/
			continue;															/*go to the next input line*/
		}

		label = *data_get_lable();												/*geting a pinter to string of label (if exist) */
		/*geting the char that symbolize the corrent command type ('c'- commands like mov,add,sub... ; 'd'-data ; 's'-string ; 'i'-entry ; 'x'-extern ; 'e'- error or invalid command )*/
		command_type = *data_get_command_type(); 
		value_arr = *data_get_value_arr();										/*geting a pinter to a array of structs that store the values */

		
		/*checking if the corrent label is already exist in the symbole table, if yes- print error massage and continue after delete the corrent label, if not continue forword */
		if (label != NULL) 
		{
			index = check_symbol_by_name(label);								/*checking if the corrent label is already exist in the symbole table*/

			if (index != NO_VAL)
			{
				print_error(DOPLICAT_LABLES_CODE);								/*if yes - print error massage*/
				label = NULL;													/*continue after delete the corrent label*/
			}
		}

		if (command_type == INSTRUC_COMMAND_TYPE)								/*if there is a label, and if the command is 'c' type (like mov add sub...) it put the label in the symbol tabal with IC counter and its type */
		{
			corrent_ic = get_ic();
			increment_ic(*data_get_num_value() + 1);
			if (label != NULL)
				set_symbol_val(label, corrent_ic, INSTRUC_COMMAND_TYPE);		/*put the label in the symbol tabal with IC counter and its type*/
		}

		else if (command_type == EXTERN_COMMAND_TYPE)							/*if there is a label (in the values), and if the command is 'x' type (extern) it put the label in the symbol tabal with 0 counter and its type */
		{
			if (label != NULL)
			{
				print_worning(EXTERN_LABEL_WORNING_CODE);						/*print a worning if there is a label before extern*/
			}

			if (check_symbol_by_name(value_arr->value) == NO_VAL)
				set_symbol_val(value_arr->value, ZERO, EXTERN_COMMAND_TYPE);
			else
				print_error(DOPLICAT_LABLES_CODE);

			update_entry_extern(EXTERN_COMMAND_TYPE);							/* the program sow an extern command, so it sends an update to the entry_extern flag */
		}

		else if (command_type == ENTRY_COMMAND_TYPE)
		{
			if (label != NULL)
				print_worning(ENTRY_LABEL_WORNING_CODE);						/*print a worning if there is a label before entry*/

			update_entry_extern(ENTRY_COMMAND_TYPE);							/*the program sow an entry command, so it sends an update to the entry_extern flag */
		}
			

		else if (command_type == DATA_COMMAND_TYPE)								/*if there is a label, and if the command is 'd' type (data) it put the label in the symbol tabal with DC counter and its type */
		{
			corrent_dc = get_dc();
			increment_dc(*data_get_num_value());
			if (label != NULL)
				set_symbol_val(label, corrent_dc, DATA_COMMAND_TYPE);			/*put the label in the symbol tabal with DC counter and its type*/


		}
		else if (command_type == STRING_COMMAND_TYPE)							/*if there is a label, and if the command is 's' type (string) it put the label in the symbol tabal with DC counter and its type */
		{
			corrent_dc = get_dc();
			increment_dc(strlen(value_arr->value) - 1);
			if (label != NULL)
				set_symbol_val(label, corrent_dc, STRING_COMMAND_TYPE);			/*put the label in the symbol tabal with DC counter and its type*/
		}

		next_line_num();														/*increment the line counter to the next line*/
		if (num_value > ZERO)													/*if there are values saved for this line, free it. (freeing calloc)*/
			free(*data_get_value_arr());										/*free values that was saved for this line*/

	}

	second_pass(file);															/*calling to the second pass*/

	if (get_error_cunter() > ZERO)												/*return ok only if there are no errors at all in the first and the second pass*/
		return NOT_OK;
	else
		return OK;

}