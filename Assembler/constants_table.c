#include "header.h"

static void create_register_table(register_list* register_table);				/*a prototype for private function for criating new register table*/  
static void create_table(command_list* command_table);							/*a  prototype for private function for criating new command table*/ 
static command_list* get_command_table();										/*a  prototype for private function for criating new command table*/ 




static command_list* get_command_table()										 /*a private function for criating new command table*/ 
{
	static command_list command_table[NUM_OF_COMMANDS];

	if (*(command_table->name) == END_STRING)									/*if it is the first call, bliud the tabel first*/
		create_table(command_table);

		return command_table;
}

static void create_table(command_list* command_table)							 /*a private function for criating new command table*/
{
	command_list* command;
	int serial_num=0;															 /*first serial num*/

	command = (command_table + serial_num);										 /*go to the right place in the table in order to fill it*/
		
	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name,"mov");												 /*put the name of the command*/
	command->opcode = MOV_OP;													 /*put the op code of the command*/
	command->funct = FUNC_IS_ZERO;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, MODE_IMMED_DIRECT_REG);				 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TREE_LINES;									 /*put the number of the lines it will take in the output file*/
	

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "cmp");												 /*put the name of the command*/
	command->opcode = CMP_OP;													 /*put the op code of the command*/
	command->funct = FUNC_IS_ZERO;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, MODE_IMMED_DIRECT_REG);				 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_IMMED_DIRECT_REG);				 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TREE_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "add");												 /*put the name of the command*/
	command->opcode = ADD_SUB_OP;												 /*put the op code of the command*/
	command->funct = FUNC_IS_10;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, MODE_IMMED_DIRECT_REG);				 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TREE_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "sub");												 /*put the name of the command*/
	command->opcode = ADD_SUB_OP;												 /*put the op code of the command*/
	command->funct = FUNC_IS_11;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, MODE_IMMED_DIRECT_REG);				 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TREE_LINES;									 /*put the number of the lines it will take in the output file*/
	
	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "lea");												 /*put the name of the command*/
	command->opcode = LEA_OP;													 /*put the op code of the command*/
	command->funct = FUNC_IS_ZERO;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, MODE_DIRECT);						 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TREE_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "clr");												 /*put the name of the command*/
	command->opcode = CLR_NOT_INC_DEC_OP;										 /*put the op code of the command*/
	command->funct = FUNC_IS_10;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "not");												 /*put the name of the command*/
	command->opcode = CLR_NOT_INC_DEC_OP;										 /*put the op code of the command*/
	command->funct = FUNC_IS_11;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "inc");												 /*put the name of the command*/
	command->opcode = CLR_NOT_INC_DEC_OP;										 /*put the op code of the command*/
	command->funct = FUNC_IS_12;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "dec");												 /*put the name of the command*/
	command->opcode = CLR_NOT_INC_DEC_OP;										 /*put the op code of the command*/
	command->funct = FUNC_IS_13;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "jmp");												 /*put the name of the command*/
	command->opcode = JMP_BNE_JSR_OP;											 /*put the op code of the command*/
	command->funct = FUNC_IS_10;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_RELAT);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "bne");												 /*put the name of the command*/
	command->opcode = JMP_BNE_JSR_OP;											 /*put the op code of the command*/
	command->funct = FUNC_IS_11;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_RELAT);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "jsr");												 /*put the name of the command*/
	command->opcode = JMP_BNE_JSR_OP;											 /*put the op code of the command*/
	command->funct = FUNC_IS_12;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_RELAT);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "red");												 /*put the name of the command*/
	command->opcode = RED_OP;													 /*put the op code of the command*/
	command->funct = FUNC_IS_ZERO;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_DIRECT_REG);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "prn");												 /*put the name of the command*/
	command->opcode = PRN_OP;													 /*put the op code of the command*/
	command->funct = FUNC_IS_ZERO;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, MODE_IMMED_DIRECT_REG);				 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = TWO_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "rts");												 /*put the name of the command*/
	command->opcode = RTS_OP;													 /*put the op code of the command*/
	command->funct = FUNC_IS_ZERO;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = ONE_LINES;									 /*put the number of the lines it will take in the output file*/

	command = (command_table + (serial_num += 1));								 /*get the next serial number for the next command*/

	command->serial_num = serial_num;											 /*put the corrent serial number*/
	strcpy(command->name, "stop");												 /*put the name of the command*/
	command->opcode = STOP_OP;													 /*put the op code of the command*/
	command->funct = FUNC_IS_ZERO;												 /*put the func code of the command*/
	strcpy(command->allowed_sour_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed sour address mode for the command*/
	strcpy(command->allowed_dest_addr_mode, NO_MODE_ALLOWED);					 /*put the allowed dest address mode for the command*/
	command->num_of_needed_lines = ONE_LINES;									 /*put the number of the lines it will take in the output file*/
}

 /*----------------------------------------------------------*/



int get_command_serial_num_by_name(char* name)									/*a function that search for a command by name and return the command serial number. if not found return -1*/
{
	int serial_num = 0;
	for (serial_num = 0; serial_num < NUM_OF_COMMANDS + 1; serial_num++)
	{
		if (strcmp(get_command_table_name(serial_num), name) == 0)				/*search for the name in all table cells  */
		{
			return serial_num;													/*return the serial number  */
		}
	}
	return NO_VAL;																/*return no_val (-1) if not found  */
}


char* get_command_table_name(int serial_num)									/*a function that search for a command by serial number and return the command name. if not found return "" */
{
	if ((serial_num > NUM_OF_COMMANDS) || (serial_num < ZERO))					/*check if the serial number is ok */
	{
		return EMPTY_STRING;															
	}
	command_list* table = get_command_table();
	return (table + serial_num)->name;											/*return the name  */
}

int get_command_table_opcode(int serial_num)									/*a function that search for a command by serial number and return the command op code. if not found return -1 */
{
	if ((serial_num > NUM_OF_COMMANDS) || (serial_num < ZERO))					/*check if the serial number is ok */
	{
		return NO_VAL;
	}
	command_list* table = get_command_table();
	return (table + serial_num)->opcode;										/*return the op code*/
}

int get_command_table_funct(int serial_num)										/*a function that search for a command by serial number and return the command func code. if not found return -1 */
{
	if ((serial_num > NUM_OF_COMMANDS) || (serial_num < ZERO))					/*check if the serial number is ok */
	{
		return NO_VAL;
	}
	command_list* table = get_command_table();
	return (table + serial_num)->funct;											/*return the funct */
}

char* get_command_table_sour_mode(int serial_num)
{
	if ((serial_num > NUM_OF_COMMANDS) || (serial_num < ZERO))					/*check if the serial number is ok */
	{
		return EMPTY_STRING;
	}
	command_list* table = get_command_table();
	return (table + serial_num)->allowed_sour_addr_mode;
}

char* get_command_table_dest_mode(int serial_num)
{
	if ((serial_num > NUM_OF_COMMANDS) || (serial_num < ZERO))					/*check if the serial number is ok */
	{
		return EMPTY_STRING;
	}
	command_list* table = get_command_table();
	return (table + serial_num)->allowed_dest_addr_mode;
}

int get_command_table_needed_lines(int serial_num)
{
	if ((serial_num > NUM_OF_COMMANDS) || (serial_num < ZERO))					/*check if the serial number is ok */
	{
		return NO_VAL;
	}
	command_list* table = get_command_table();
	return (table + serial_num)->num_of_needed_lines;
}

     /*--------------------------------registers---------------------------------*/




register_list* get_register_table()												/*a private function for criating new register table*/
{
	static register_list register_table[NUM_OF_REGISTERS];

	if (*(register_table->name) == END_STRING)
		create_register_table(register_table);

	return (register_table);
}

static void create_register_table(register_list* register_table)
{
	register_list* reg;
	int serial_num = 0;															/*first serial num*/

	reg = (register_table + serial_num);

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r0");													/*put the name of the register*/
	
	reg = (register_table + (serial_num += 1));									/*get the next serial number for the next reg*/

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r1");													/*put the name of the register*/

	reg = (register_table + (serial_num += 1));									/*get the next serial number for the next reg*/

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r2");													/*put the name of the register*/

	reg = (register_table + (serial_num += 1));									/*get the next serial number for the next reg*/

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r3");													/*put the name of the register*/

	reg = (register_table + (serial_num += 1));									/*get the next serial number for the next reg*/

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r4");													/*put the name of the register*/

	reg = (register_table + (serial_num += 1));									/*get the next serial number for the next reg*/

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r5");													/*put the name of the register*/

	reg = (register_table + (serial_num += 1));									/*get the next serial number for the next reg*/

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r6");													/*put the name of the register*/

	reg = (register_table + (serial_num += 1));									/*get the next serial number for the next reg*/

	reg->serial_num = serial_num;												/*put the corrent serial number*/
	strcpy(reg->name, "r7");													/*put the name of the register*/

}

char* get_register_table_name(int serial_num)									/*a function that search for a reg by serial number and return the reg name. if not found return "" */
{
	if ((serial_num > NUM_OF_REGISTERS) || (serial_num < ZERO))					/*check if the serial number is ok */
	{
		return EMPTY_STRING;													/*if not found return "" */
	}
	register_list* table = get_register_table();
	return (table + serial_num)->name;											/*return the name*/
}
