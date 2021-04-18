#include "header.h"

int build_command(int);																			/*private function prototype*/
int first_line(int opcode, int funct, int sour_addr_mode, int dest_addr_mode);					/*private function prototype*/
void copy_data_to_ob_file(OUTPUT_FILE* output);													/*private function prototype*/



/*this function print the output files after the first and the second passes determined that there are no syntactics errors in the source code */
void output_printer(OUTPUT_FILE* output, FILE* source_file)
{
	int index;
	int input_retern_val;
	int i = 0;
	char command_type;
	int num_of_values;
	int serial_num;
	value_and_mode* value_arr;
	int value;
	int ob_command_line_numer = IC_START_CUNT;
	int ob_data_line_numer = get_ic();															/*getting the corrent number of lines in the IC*/

	rewind(source_file);																		/*making sure to read the input from the begining*/

	fprintf(output->ob, OB_FILE_PRINT_TITEL, get_ic() - IC_START_CUNT, get_dc());				/*printing the ob file titel*/

	/*this loop going through all the source code and sends line after line to be printed along with its values*/
	while ((input_retern_val = get_input(source_file)) != EOF)
	{
		if (input_retern_val == COMMENT)														/*ignoring comments*/
			continue;

		command_type = *data_get_command_type();												/*geting the command type*/
		num_of_values = *data_get_num_value();													/*geting the numbers of value in that line*/
		value_arr = *data_get_value_arr();														/*geting a pinter to a array of structs that store the values */

		switch (command_type)																	/*sends the commands to be printed based on there type*/
		{
		case(INSTRUC_COMMAND_TYPE):																/*'c' type case*/

			serial_num = get_command_serial_num_by_name(*data_get_command());					/*getting the number of the command in the constant tabel*/
			value = build_command(serial_num);													/*building the first line to be printed (the command itself)*/
			fprintf(output->ob, OB_FILE_PRINT_FORMAT, ob_command_line_numer++, value, ABSOLUTE);/*printing it to the 'ob' file*/

			/*this loop prints the values comming after words*/
			for (i = 0; i < num_of_values; i++)
			{

				switch ((value_arr + i)->value_mode)											/*sends the values to be printed based on there addres mode*/
				{
				case(MODE_IMMED_CHAR):															/*in case of immediate address mode value*/
					value = (atoi(((value_arr + i)->value) + 1) & (MASK_FOR_12_BITS));		/*changs the value to an int number and making sure that it is not begger then 12 bit number*/
					fprintf(output->ob, OB_FILE_PRINT_FORMAT, ob_command_line_numer++, value, ABSOLUTE);/*printing it to the 'ob' file*/
					break;

				case(MODE_DIRECT_CHAR):															/*in case of direct address mode value*/

					index = check_symbol_by_name((value_arr + i)->value);						/*geting its serial number in the symbole tabel*/

					if (get_symbol_attributes(index) == EXTERN_COMMAND_TYPE)					/*if the tabel is an extern type*/
					{
						fprintf(output->ext, ENT_OR_EXT_FILE_PRINT_FORMAT, (value_arr + i)->value, ob_command_line_numer);	/*prints its label name to the 'ext' file*/
						fprintf(output->ob, OB_FILE_PRINT_FORMAT, ob_command_line_numer++, 0, EXTERNAL);	/*printing a spacial line to the 'ob' file (with value 000)*/
					}
					else
					{
						value = get_symbol_value(index);										/*geting the label "address" in the code (its line (IC) number)*/
						fprintf(output->ob, OB_FILE_PRINT_FORMAT, ob_command_line_numer++, value, RELOCATABLE);/*printing it to the 'ob' file*/
					}

					break;

				case(MODE_RELATIVE_CHAR):														/*in case of relative address mode value*/
					index = check_symbol_by_name(((value_arr + i)->value)+1);					/*geting its serial number in the symbole tabel*/
					if (get_symbol_attributes(index) == EXTERN_COMMAND_TYPE)					/*if the tabel is an extern type*/
					{
						value = ((ZERO - ob_command_line_numer) & (MASK_FOR_12_BITS));			/*geting the label "address" in the code and calculate its distance from the corrent address line (which is 000 becouse it is extern value)*/
						fprintf(output->ext, ENT_OR_EXT_FILE_PRINT_FORMAT, ((value_arr + i)->value)+1, ob_command_line_numer);	/*prints its label name to the 'ext' file*/
						fprintf(output->ob, OB_FILE_PRINT_FORMAT, ob_command_line_numer++, value, EXTERNAL);	/*printing it to the 'ob' file*/
					}
					else
					{
						value = ((get_symbol_value(index) - ob_command_line_numer) & (MASK_FOR_12_BITS));	/*geting the label "address" in the code and calculate its distance from the corrent line*/
						fprintf(output->ob, OB_FILE_PRINT_FORMAT, ob_command_line_numer++, value, RELOCATABLE);	/*printing it to the 'ob' file*/
					}

					break;

				case(MODE_REGISTER_CHAR):														/*in case of register address mode value*/
					value = (1 << atoi(((value_arr + i)->value)+1));							/*calculating the number that represent the register -> 2^(register number) */
					fprintf(output->ob, OB_FILE_PRINT_FORMAT, ob_command_line_numer++, value, ABSOLUTE);	/*printing it to the 'ob' file*/
					break;
				}
			}

			break;

		case(DATA_COMMAND_TYPE):																/*in case of 'date' address mode value (numbers)*/
			/*in case of date address mode value (numbers) we need to print it after the commands, so the program save its corrent positin -> jump to the end of th 'ob' file -> printing the data -> and than returns to its previous position*/

			for (i = 0; i < num_of_values; i++)													/*printing the data value to the 'tmp_data' file*/
			{
				value = (atoi((value_arr + i)->value) & (MASK_FOR_12_BITS));
				fprintf(output->tmp_data, OB_FILE_PRINT_FORMAT, ob_data_line_numer++, value, ABSOLUTE);
			}

			break;

		case(STRING_COMMAND_TYPE):																/*in case of 'date' (string) address mode value (letters and \0 in the end)*/


			i = 1;
			while (*((value_arr->value) + i) != QUOTE_MARK)										/*printing the data (string) value to the 'tmp_data' file*/
			{
				value = *((value_arr->value) + i);
				fprintf(output->tmp_data, OB_FILE_PRINT_FORMAT, ob_data_line_numer++, value, ABSOLUTE);
				i++;
			}
			fprintf(output->tmp_data, OB_FILE_PRINT_FORMAT, ob_data_line_numer++, ZERO, ABSOLUTE);	/*in the end, printing the end of string (\0) value to the 'tmp_data' file*/

			break;

		case(ENTRY_COMMAND_TYPE):																/*in case of 'entry' command */
			value = get_symbol_value(check_symbol_by_name(value_arr->value));
			fprintf(output->ent, ENT_OR_EXT_FILE_PRINT_FORMAT, value_arr->value, value);		/*printing it to the 'ent' file*/
			break;

		case(EXTERN_COMMAND_TYPE):																/*in case of 'extern' command */
			break;

		case(ERROR_VAL):
			break;

		}

		if (num_of_values > ZERO)																/*if there are values saved for this line, free it. (freeing calloc)*/
			free(*data_get_value_arr());														/*free values that was saved for this line*/

	}

	copy_data_to_ob_file(output); /*copy all data lines from the temporary "tmp_data.tmp" file to the end of the ob file*/
}

/*this function get the command components (opcode, funct, sour_addr_mode, dest_addr_mode) and sends it to "first_line" function to build the first line of 'c' type command*/
int build_command(int serial_num)
{
	int opcode;
	int funct;
	int sour_addr_mode;
	int dest_addr_mode;
	int num_of_needed_lines;
	value_and_mode* value_arr = *data_get_value_arr();											/*geting a pinter to a array of structs that store the values */
	
	opcode = get_command_table_opcode(serial_num);												/*geting the opcode of the command */
	funct = get_command_table_funct(serial_num);												/*geting the funct of the command */
	num_of_needed_lines = get_command_table_needed_lines(serial_num);							/*geting the number of line that should be printed for this command (number of values + 1) */

	if (num_of_needed_lines == 3)
	{
		sour_addr_mode = ((value_arr->value_mode) - ASCII_OF_0);								/*source address mode in 3 lines case*/
		dest_addr_mode = (((value_arr+1)->value_mode) - ASCII_OF_0);							/*destination address mode in 3 lines case*/
		return (first_line(opcode, funct, sour_addr_mode, dest_addr_mode));
	}
		
	else if (num_of_needed_lines == 2)
	{
		sour_addr_mode = ZERO;																	/*source address mode in 2 lines case*/
		dest_addr_mode = ((value_arr->value_mode) - ASCII_OF_0);								/*destination address mode in 2 lines case*/
		return(first_line(opcode, funct, sour_addr_mode, dest_addr_mode));
	}
	else
	{
		sour_addr_mode = ZERO;																	/*source address mode in 1 lines case*/
		dest_addr_mode = ZERO;																	/*destination address mode in 1 lines case*/
		return(first_line(opcode, funct, sour_addr_mode, dest_addr_mode));
	};
}


/*this function get the command components and than build and return the first line of 'c' type command ([8-12 bits: opcode], [4-8 bits: funct], [2-4 bits: sour_addr_mode], [0-2 bits: dest_addr_mode])*/
int first_line(int opcode, int funct, int sour_addr_mode, int dest_addr_mode)
{
	int word = ZERO;
	word |= (opcode <<= EGHIT_STEPS);															/*puts the opcode in its place (8 bits from the most left end) - [8-12 bits: opcode]*/
	word |= (funct <<= FOUR_STEPS);																/*puts the funct in its place (4 bits from the most left end) - [4-8 bits: funct]*/
	word |= (sour_addr_mode <<= TWO_STEPS);														/*puts the source address mode in its place (2 bits from the most left end) - [2-4 bits: sour_addr_mode]*/
	word |= (dest_addr_mode);																	/*puts the destination address mode in its place (0 bits from the most left end) - [0-2 bits: dest_addr_mode]*/
	return word;
}

 /*this function copy all data lines from the temporary "tmp_data.tmp" file to the end of the ob file */
void copy_data_to_ob_file(OUTPUT_FILE* output)
{
	char copy_line[MAX_LINE_LEN];																/*buffer*/
	rewind(output->tmp_data);																	/*starting the temp file from the begining*/
	while ((fgets(copy_line, MAX_LINE_LEN, output->tmp_data)) != NULL)
	{
		fputs(copy_line, output->ob);															/*copy all data lines untill EOF*/
	}

}