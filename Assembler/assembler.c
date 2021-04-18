#include "header.h"




/*The role of the assembler is to build a file containing machine code, from a given file of a program written in its own dedicated assembly language.
In this project we will write an assembler (i.e. a program that translates into machine language), for the computer language.
The next steps are linkage and loading, but we will not deal with this issue.*/


int main(int argc, char** argv)
{
	int i;
	char name[MAX_NAME_LEN + MAX_NAME_ENDING_LEN] = EMPTY_STRING;				/*assigned array for the name of the files to open (the + 5 is for the file ending). initialaze it with empty string*/
	FILE* source_file;															/*a pointer for the source file*/
	OUTPUT_FILE output;															/*a struct of pointers for the output files*/

	for (i = 1; i < argc; i++)													/*a loop that continue until there is no more files to read*/
	{
		if((strlen(*(argv + i)) < MAX_NAME_LEN)&&((strlen(*(argv + i)) > MIN_NAME_LEN))) /*check if the source file name is a ligal name (longer then 1 and not longer then 20)*/
			strcpy(name, (*(argv + i)));										/*if this is a ligal name, copy it to the variable "name" */
		else
		{
			print_error(FILE_NAME_CODE);										/*if this is not a ligal name, print error and continue to the next name in the list*/
			continue;
		}

		printf(WORKING_ON, name);												 /*print a massage for the user that we work on <name> file*/
		if ((source_file = fopen(strcat(name, ASSEMBLY_FILE_ENDING), OPEN_FOR_READ)) == NULL)  /*check if we can open the file <name.as>, if not print error and go to the next file on the list*/
		{
			print_error(FOPEN_FAILURE_CODE);
			continue;															/*continue to the next file on the list*/
		}

		(void)strtok(name, POINT);												/*this is a function for deleting the "ending" name  (like ".as") so we can work again on the original name*/

		if (first_pass(source_file) == NOT_OK)									/*check if the first pass function and the second pass function pass with errors */
		{
			printf(ERROR_IN_SOURCE_FILE);										/*if the first pass function or the second pass function pass with errors, print error massage */
			symbol_free_all();													/*free all malloc we used for the symbole table */
			fclose(source_file);												/*close the bad file */
			continue;															/*continue to the next file on the list*/
		}

		output.ob = NULL;														/*initialaze the pointers of output struct to NULL */
		output.ext = NULL;														/*initialaze the pointers of output struct to NULL */
		output.ent = NULL;														/*initialaze the pointers of output struct to NULL */
		output.tmp_data = NULL;													/*initialaze the pointers of output struct to NULL */

		switch (is_there_entry_or_extern())										/*get the result of the check if there was extern commands or entry commands in the code so we will know what files we need to open. (the actually check was made in the first pass)*/
		{
		case(BOTH_CHAR):														/*if there are both - extern and entry commands, we open 3 files -.ob,.ent,.ext */
			TRY_FOPEN_WRITE(output.ob, strcat(name, OBJECT_FILE_ENDING));		/*tring to open <name.ob> */
			TRY_FOPEN_WRITE(output.tmp_data, TEMP_FILE_NAME);					/*tring to open "tmp_data.tmp" for writing*/
			(void)strtok(name, POINT);											/*deleting the "ending" name  (like ".as") so we can work again on the original name*/
			TRY_FOPEN_WRITE(output.ent, strcat(name, ENTERY_FILE_ENDING));		/*tring to open <name.ent> for writing*/
			(void)strtok(name, POINT);											/*deleting the "ending" name  (like ".as") so we can work again on the original name*/
			TRY_FOPEN_WRITE(output.ext, strcat(name, EXTERN_FILE_ENDING));		/*tring to open <name.ext> for writing*/
			break;
		case(ENTRY_COMMAND_TYPE):												/*if there is only entry commands, we open 2 files -.ob,.ent */
			TRY_FOPEN_WRITE(output.ob, strcat(name, OBJECT_FILE_ENDING));		/*tring to open <name.ob> for writing*/
			TRY_FOPEN_WRITE(output.tmp_data, TEMP_FILE_NAME);					/*tring to open "tmp_data.tmp" for writing*/
			(void)strtok(name, POINT);											/*deleting the "ending" name  (like ".as") so we can work again on the original name*/
			TRY_FOPEN_WRITE(output.ent, strcat(name, ENTERY_FILE_ENDING));		/*tring to open <name.ent> for writing*/

			break;
		case(EXTERN_COMMAND_TYPE): 												/*if there is only extern commands, we open 2 files -.ob,.ext */

			TRY_FOPEN_WRITE(output.ob, strcat(name, OBJECT_FILE_ENDING));		/*tring to open <name.ob> for writing*/
			TRY_FOPEN_WRITE(output.tmp_data, TEMP_FILE_NAME);					/*tring to open "tmp_data.tmp" for writing*/
			(void)strtok(name, POINT);											/*deleting the "ending" name  (like ".as") so we can work again on the original name*/
			TRY_FOPEN_WRITE(output.ext, strcat(name, EXTERN_FILE_ENDING));		/*tring to open <name.ext> for writing*/

			break;

		case(NEITHER_CHAR):														/*if there is nither, we open 1 file -.ob */
			TRY_FOPEN_WRITE(output.ob, strcat(name, OBJECT_FILE_ENDING));		/*tring to open <name.ob> for writing*/
			TRY_FOPEN_WRITE(output.tmp_data, TEMP_FILE_NAME);					/*tring to open "tmp_data.tmp" for writing*/
			break;
		}

		output_printer(&output, source_file);									/*calling to function that print the output files (after we made sure that there are no errors in the code in the first and second pass)*/

		symbol_free_all();														/*free all malloc we used for the symbole table */
		fclose(source_file);													/*close the source file */
		if (output.ob != NULL)
			fclose(output.ob);													/*close the .ob file */
		if (output.tmp_data != NULL)
			fclose(output.tmp_data);											/*close the "tmp_data.tmp"*/
		if (output.ent != NULL)
			fclose(output.ent);													/*close the .ent file if exist */
		if (output.ext != NULL)
			fclose(output.ext);													/*close the .ext file if exist */

		printf(SUCCESS);														/*print to the user that the output files criated successfully */
	}

	remove(TEMP_FILE_NAME);														/*removing the temporary file after we finished with it*/
	return 	EXIT_SUCCESS;														/*the program has ended and returned "success" */
}

