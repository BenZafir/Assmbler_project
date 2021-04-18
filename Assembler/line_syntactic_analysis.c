#include "header.h"


/*----------------------------------------------------parameter validation check-----------------------------------*/

/*this function check if an input line is syntacly correct or not*/
int check_line()
{
	int is_line_ok = OK;
	int i=0;
	int serial_num;
	char* lable = *data_get_lable();														/*geting a pinter to the label that was defined in that line (if exist) */
	char* command = *data_get_command();													/*geting a pinter to the command that was defined in that line */
	char command_type = *data_get_command_type();											/*geting the char that symbolize the corrent command type (for that line)*/
	int num_of_values = *data_get_num_value();												/*geting the number of values in that line*/
	int num_of_needed_lines = 1;															/*starting with the assumption that there is only 1 line to be print in the output*/
	char* allowed_dest_mode = NO_MODE_ALLOWED;												/*starting with the assumption that there is no address mode allowed for that line*/
	char* allowed_sour_mode = NO_MODE_ALLOWED;												/*starting with the assumption that there is no address mode allowed for that line*/
	value_and_mode* value_arr = *data_get_value_arr();										/*geting a pinter to a array of structs that store the values */
	char val;

	if (!check_lable(lable))																/*check if the label is syntacly correct (if exist)*/
	{
		print_error(INVALID_LABALE_CODE);													/*printing an error massage if the label is syntacly incorrect*/
		is_line_ok = NOT_OK;
	}

	if (command_type == INSTRUC_COMMAND_TYPE)											/*if the type of command is 'c', check if the command and its values are syntacly correct*/
	{
		serial_num = get_command_serial_num_by_name(command);								/*geting the serial number of command from the constant table*/

		if (serial_num == NO_VAL)															/*if there is no such command defined, the line is syntacly incorrect*/
			return NOT_OK;
		else
		{
			num_of_needed_lines = get_command_table_needed_lines(serial_num);
			allowed_dest_mode = get_command_table_dest_mode(serial_num);
			allowed_sour_mode = get_command_table_sour_mode(serial_num);
		}


		if (num_of_values > (num_of_needed_lines - 1))										/*if there are more values in the input line than what was defined in the constant table, the line is syntacly incorrect*/
		{
			print_error(TOO_MANY_VAL_CODE);
			is_line_ok = NOT_OK;
		}

		if (num_of_values < (num_of_needed_lines - 1))										/*if there are less values in the input line than what was defined in the constant table, the line is syntacly incorrect*/
		{
			print_error(TOO_FEW_VAL_CODE);
			is_line_ok = NOT_OK;
		}
		/*check if the values are syntacly correct and if thier address mode adhere with what was defined in the constant table for that command */
		for (i = num_of_values - 1; i >= 0; i--)												
		{
			val = (value_arr + i)->value_mode;

			if (val == ERROR_VAL || val == DATA_COMMAND_TYPE || val == STRING_COMMAND_TYPE)	/*check if the values are syntacly correct*/
			{
				print_error(INVALID_VAL_CODE);
				is_line_ok = NOT_OK;
			}

			if (i == (num_of_values - 1))													/*check if the destination address mode adhere with what was defined in the constant table*/
			{
				if (strchr(allowed_dest_mode, val) == NULL)
				{
					print_error(INVALID_DEST_CODE);
					is_line_ok = NOT_OK;
				}
			}

			if (i != (num_of_values - 1))													/*check if the source address mode adhere with what was defined in the constant table*/
			{
				if (strchr(allowed_sour_mode, val) == NULL)
				{
					print_error(INVALID_SOUR_CODE);
					is_line_ok = NOT_OK;
				}
			}
			/*check if the value is not between 2047 to -2048 (so it can not be represented as 12 bit number)*/
			if (((value_arr + i)->value_mode) == MODE_IMMED_CHAR)
			{
				if ((atoi(((value_arr + i)->value) + 1) > MAX_NUM_IN_12_BITS) || (atoi(((value_arr + i)->value) + 1) < MIN_NUM_IN_12_BITS))
				{
					print_worning(VAL_BIGER_2047_OR_SMOLLER_MINUS_2048_CODE);
				}

			}
		}
	}

	else if (command_type == DATA_COMMAND_TYPE)												/*if the type of command is 'd', check if the command and its values are syntacly correct*/
	{
		if (num_of_values < 1)																/*if there is less then one value in the input line than the line is syntacly incorrect*/
		{
			print_error(TOO_FEW_VAL_CODE);
			is_line_ok = NOT_OK;
		}

		for (i = 0; i < num_of_values; i++)													/*check if the values are syntacly correct*/
		{
			val = (value_arr + i)->value_mode;
			if (val != DATA_COMMAND_TYPE)
			{
				print_error(INVALID_VAL_CODE);
				is_line_ok = NOT_OK;
			}
			/*check if the value is not between 2047 to -2048 (so it can not be represented as 12 bit number)*/
			if ((atoi((value_arr + i)->value) > MAX_NUM_IN_12_BITS) || (atoi((value_arr + i)->value) < MIN_NUM_IN_12_BITS))
			{
				print_worning(VAL_BIGER_2047_OR_SMOLLER_MINUS_2048_CODE);
			}

		}
	}

	else if (command_type == STRING_COMMAND_TYPE)											/*if the type of command is 's', check if the command and its values are syntacly correct*/
	{
		if (num_of_values > 1)																/*if there is more then one value in the input line than the line is syntacly incorrect*/
		{
			print_error(TOO_MANY_VAL_CODE);
			is_line_ok = NOT_OK;
		}

		if (num_of_values < 1)																/*if there is less then one value in the input line than the line is syntacly incorrect*/
		{
			val = ERROR_VAL;
			print_error(TOO_FEW_VAL_CODE);
			is_line_ok = NOT_OK;
		}
		else
			val = value_arr->value_mode;
		
		
		if (val != STRING_COMMAND_TYPE)														/*check if the values are syntacly correct*/
		{
			print_error(INVALID_VAL_CODE);
			is_line_ok = NOT_OK;
		}
	}

	else if ((command_type == EXTERN_COMMAND_TYPE) || (command_type == ENTRY_COMMAND_TYPE))	/*if the type of command is 'x' or 'i', check if the command and its values are syntacly correct*/
	{


		if (num_of_values > 1)
		{
			print_error(TOO_MANY_VAL_CODE);													/*if there is more then one value in the input line than the line is syntacly incorrect*/
			is_line_ok = NOT_OK;
		}

		if (num_of_values < 1)
		{
			val = ERROR_VAL;
			print_error(TOO_FEW_VAL_CODE);													/*if there is less then one value in the input line than the line is syntacly incorrect*/
			is_line_ok = NOT_OK;
		}
		else
			val = value_arr->value_mode;
			
		if (val != MODE_DIRECT_CHAR)														/*check if the values are syntacly correct*/
		{
			print_error(INVALID_VAL_CODE);
			is_line_ok = NOT_OK;
		}

	}

	else
	{
		print_error(INVALID_COMMAND_CODE);
		is_line_ok = NOT_OK;
	}

	return is_line_ok;
}



/*check if the label is syntacly correct (if exist)*/
int check_lable(char* lable)
{
	int i;
	int lable_len;

	if (lable == NULL)																		/*if there is no label, accept it*/
		return OK;

	lable_len = strlen(lable);
	if (lable_len == 0)																		/*if the label has no string at all, do not accept it*/
		return NOT_OK;

	if (lable_len > MAX_SYMBOL_LEN)																		/*if the label has no string at all, do not accept it*/
		return NOT_OK;

	if (!check_space(lable))
		return NOT_OK;

	if (IS_A_LETTER(*lable))																	/*if the label first letter is not abc letter, do not accept it*/
	return NOT_OK;

	for (i = 1; i < lable_len; i++)
	{
		/*if the label letter after the first letter is not abc letter or number, do not accept it*/
		if (IS_A_NUMBER_OR_LETTER(*(lable + i)))
			return NOT_OK;
	}
	

	if(get_command_serial_num_by_name(lable) != NO_VAL)										/*if the label string is identical to command name, do not accept it*/
		return NOT_OK;

	for (i = 0; i < NUM_OF_REGISTERS; i++)													/*if the label string is identical to register name, do not accept it*/
	{
		if (strcmp(get_register_table_name(i), lable) == ZERO)
			return NOT_OK;
	}

	return 	OK;
}

/*this functin set a char in the data-base that symbolize the corrent command type (for that line)*/
void get_command_type()
{
	char* command = *data_get_command();													/*geting a pinter to the command location in the data-base */
	char* command_type = data_get_command_type();											/*geting a pinter to the command_type location in the data-base (for update) */

	*command_type = ERROR_VAL;																/*starting with the assumption that the command is invalid*/
	if (check_space(command) == NOT_OK)														/*making sure that there are no space it the command*/
		return;

	if (strcmp(command, DATA) == ZERO)														/*if the command is ".data" put the char 'd' in the command_type location in the data-base */
		*command_type = DATA_COMMAND_TYPE;
	else if (strcmp(command, STRING) == ZERO)												/*if the command is ".sting" put the char 's' in the command_type location in the data-base */
		*command_type = STRING_COMMAND_TYPE;
	else if (strcmp(command, EXTERN) == ZERO)												/*if the command is ".extern" put the char 'x' in the command_type location in the data-base */
		*command_type = EXTERN_COMMAND_TYPE;
	else if (strcmp(command, ENTERY) == ZERO)												/*if the command is ".entry" put the char 'i' in the command_type location in the data-base */
		*command_type = ENTRY_COMMAND_TYPE;
	else
	{
		if (get_command_serial_num_by_name(command) != NO_VAL)								/*if the command is one of the commands in the constant table put the char 'c' in the command_type location in the data-base */
			*command_type = INSTRUC_COMMAND_TYPE;
	}
}

/*this function check if the values are syntacly correct and decide thier address mode */
char check_val_type(char* value)
{
	int len;
	int i = 0;
	register_list* reg;
	reg = get_register_table();



	if ((*value) == IMMED_MODE_BEGIN_CHAR)													/*immediat mode - if the value start with # check if it is a valid number*/
	{
		if (check_space(value) == NOT_OK) 														/*making sure that there are no space it the value*/
			return ERROR_VAL;

		if ((value[1]) == PLUS || (value[1]) == MINUS)										/*check if the number starts with  '+' or '-' */
		{
			i = 2;
			while (*(value + i) != END_STRING)
			{
				if (!isdigit(*(value + i)))													/*check if the number is a valid number (after the '+' or '-' signs)*/
					return ERROR_VAL;
				i++;

			}
			if (i == 2)
				return ERROR_VAL;
		}
		else
		{
			i = 1;
			while (*(value + i) != END_STRING)
			{
				if (!isdigit(*(value + i)))													/*check if the number is a valid number (there is no '+' or '-' signs)*/
					return ERROR_VAL;
				i++;
			}
			if (i == 1)
				return ERROR_VAL;
		}
		return MODE_IMMED_CHAR;																/*return '0' for immediat mode)*/
	}

	if ((*value) == RELATIVE_MODE_BEGIN_CHAR)												/*relative mode - if the value start with % check if it is a valid label*/
	{
		if (check_space(value) == NOT_OK) 														/*making sure that there are no space it the value*/
			return ERROR_VAL;

		if (check_lable(value + 1) != NOT_OK)
			return MODE_RELATIVE_CHAR;														/*return '2' for relative mode)*/
		else
			return ERROR_VAL;
	}

	for (i = 0; i < NUM_OF_REGISTERS; i++)													/*regeister mode - if the value is a register name*/
	{
		if ((strcmp((reg + i)->name, value) == ZERO))
			return MODE_REGISTER_CHAR;														/*return '3' for regeister mode)*/
	}


	if ((*value) == PLUS || (*value) == MINUS || isdigit(*value))							/*data mode - if the value is a number (without #)*/
	{
		if (check_space(value) == NOT_OK) 														/*making sure that there are no space it the value*/
			return ERROR_VAL;

		i = 0;
		if ((*value) == PLUS || (*value) == MINUS)
			i++;

		while (*(value + i) != END_STRING)
		{
			if (!isdigit(*(value + i)))														/*check if the number is a valid number (after the '+' or '-' signs)*/
				return ERROR_VAL;
			i++;

		}
		if (i == 0)
			return ERROR_VAL;
		return DATA_COMMAND_TYPE;															/*return 'd' for "data")*/
	}


	else if (((*value) == QUOTE_MARK) && (*((value)+strlen(value) - 1) == QUOTE_MARK))		/*string mode - if the value is a "string" (begins and ends with the "quote mark" chars)*/
	{
		len = strlen(value);
		for (i = 1; i < (len - 1); i++)
		{
			if (!(*(value + i) >= ASCII_TABLE_ALL_START || *(value + i) <= ASCII_TABLE_ALL_END))
				return ERROR_VAL;
			i++;

		}
		return STRING_COMMAND_TYPE;															/*return 's' for "string")*/
	}

	else if (check_lable(value) != NOT_OK)													/*if the value is not data mode or string mode and it is a valid label - so it is direct mode*/
	{
		return MODE_DIRECT_CHAR;															/*return '1' for direct mode)*/
	}


	else
		return ERROR_VAL;																	/*return 'e' for "error")*/
}
