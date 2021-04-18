#include "header.h"

static char* entry_extern();		/*prototype for private func "entry_extern"*/



/***************************************************************************** check_space *****************************************************************************/

/*a function that check if there are spaces or tabs in a given string*/
int check_space(char* value)												
{
	int i;
	int value_len = strlen(value);											/*checking what is the lenth of the string*/
	for (i = 0; i < value_len; i++)
	{
		if (value[i] == SPACE || value[i] == TAB)							/*for every char, check if it is space or tab*/
			return NOT_OK;													/*if space or tab have found, return not_ok*/
	}
	return 	OK;																/*if space and tab haven't found, return ok*/
}


/***************************************************************************** trim_space *****************************************************************************/

/*a function that delete space and tabs from the begining and ending of a given string*/
char* trim_space(char* with_space)											
{
	int i = 0;
	char* without_space;
	int with_space_size = strlen(with_space);								/*checking what is the lenth of the string*/
	if (with_space_size == ZERO)											/*if the lenth of the string is zero, there is nothing to do*/
		return with_space;
	for (i = with_space_size - 1; i >= 0; i--)
	{
		if (with_space[i] == SPACE || with_space[i] == TAB);				/*checking the string form the end to the begining, and find the last space \ tab (from the end)*/
		else
			break;
	}

	with_space[i + 1] = END_STRING;											/*put end_string on the last space \ tab (from the end) */

	for (i = 0; i < with_space_size; i++)									/*search for the last space \ tab (from the begining) */
	{
		if (with_space[i] == SPACE || with_space[i] == TAB);
		else
			break;
	}
	without_space = (with_space + i);
	return 	without_space;													/*return a pointer to the string after the last space \ tab (from the begining) */
}

/***************************************************************************** entry_extern *****************************************************************************/


/*those "entry_extern" function are fonction that check if there are entry commands or extern commands in the source code (so we will know which files we need to open in the print stage) */

static char* entry_extern() /*private func*/
{
	static char ent_ext = NEITHER_CHAR;										/*in the begining, the program has not seen any extern or entry yet. so the flag value is 'n'- nither*/
	return (&ent_ext);
}

char is_there_entry_or_extern()												/*return the corrnt status of the flag */
{
	return *entry_extern(); 
}

void update_entry_extern(char update)										/*if the program sow entry or extern command (in the first pass) it sends an update to the flag */
{
	char* corrent_entry_extern = entry_extern();

	if ((update != ENTRY_COMMAND_TYPE) && (update != EXTERN_COMMAND_TYPE)) /*if the update is not 'i' or 'x' there is a problem in the update */
		return;

	switch (*corrent_entry_extern) 
	{
	case(NEITHER_CHAR):														/*if the update is 'i' or 'x' and the flag is on nither state, the flag update it self to the value of the update */
		*corrent_entry_extern = update;
		break;

	case(EXTERN_COMMAND_TYPE):												/*if the update is 'x' and the flag was on 'i' state, the flag update it self to the value "both" */
		if (update == ENTRY_COMMAND_TYPE)
			*corrent_entry_extern = BOTH_CHAR;
		break;

	case(ENTRY_COMMAND_TYPE):												/*if the update is 'i' and the flag was on 'x' state, the flag update it self to the value "both" */
		if (update == EXTERN_COMMAND_TYPE)
			*corrent_entry_extern = BOTH_CHAR;
		break;

	case(BOTH_CHAR):														/*if the flag was on 'b'- both  state, there is nothing to update */
		break;
	}
}

void entry_extern_back_to_start()											/*reset the flag back to 'n' - nither */
{
	*entry_extern() = NEITHER_CHAR;
}