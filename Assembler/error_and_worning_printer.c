#include "header.h"





/*************************************************** error_printer ***************************************************/


 /*this function is responseble to print an error massage with its line number in the source code.
 that is, if the program found an error in the source code it send its error code to print_error,
 and this function print the error massage with the line number in the code which couse the problam*/

void print_error(int error_num)
{
	char* error;

	increment_error_counter();  /*telling "error_counter" to counte that error in the error counter (increment error counter by 1)*/


	switch (error_num)														/*a switch that translate the error code recived to a string to be printed to the user*/
	{
	case(INVALID_LABALE_CODE):
		error = INVALID_LABALE_STRING;
		break;
	case(INVALID_COMMAND_CODE):
		error = INVALID_COMMAND_STRING;
		break;
	case(MALLOC_FAILURE_CODE):
		error = MALLOC_FAILURE_STRING;
		break;
	case(TOO_MANY_VAL_CODE):
		error = TOO_MANY_VAL_STRING;
		break;
	case(TOO_FEW_VAL_CODE):
		error = TOO_FEW_VAL_STRING;
		break;
	case(INVALID_VAL_CODE):
		error = INVALID_VAL_STRING;
		break;
	case(DOPLICAT_LABLES_CODE):
		error = DOPLICAT_LABLES_STRING;
		break;
	case(INVALID_DEST_CODE):
		error = INVALID_DEST_STRING;
		break;
	case(INVALID_SOUR_CODE):
		error = INVALID_SOUR_STRING;
		break;
	case(NO_SUCH_LABALE_IN_CODE):
		error = NO_SUCH_LABALE_IN_STRING;
		break;
	case(FTELL_FAILURE_CODE):
		error = FTELL_FAILURE_STRING;
		break;
	case(FSEEK_FAILURE_CODE):
		error = FSEEK_FAILURE_STRING;
		break;
	case(FOPEN_FAILURE_CODE):
		error = FOPEN_FAILURE_STRING;
		break;
	case(FILE_NAME_CODE):
		error = FILE_NAME_STRING;
		break;
	case(ENTRY_AND_EXTERN_CODE):
		error = ENTRY_AND_EXTERN_STRING;
		break;
	default:
		error = "unknown error";
		break;
	}
	
	printf(ERROR_LINE_NUMBER, get_line_num(), error);				/*print the error massage with the line number in the code which couse the problam*/

}



/*************************************************** error_printer ***************************************************/


/*this function is responseble to print an worning massages with its line number in the code which couse the problam*/

void print_worning(int worning_num)
{
	char* worning;

	switch (worning_num)											/*a switch that translate the worning code recived to a string to be printed to the user*/
	{
	case(EXTERN_LABEL_WORNING_CODE):
		worning = EXTERN_LABEL_WORNING_STRING;
		break;
	case(ENTRY_LABEL_WORNING_CODE):
		worning = ENTERY_LABEL_WORNING_STRING;
		break;
	case(VAL_BIGER_2047_OR_SMOLLER_MINUS_2048_CODE):
		worning = VAL_BIGER_2047_OR_SMOLLER_MINUS_2048_STRING;
		break;
		
	default:
		worning = "unknown worning";
		break;
	}

	printf(ERROR_LINE_NUMBER, get_line_num(), worning);				/*print the worning massage with the line number in the code which couse the problam*/
}