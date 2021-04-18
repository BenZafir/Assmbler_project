#include "header.h"

 /*those function create and menage a link list of structs that work as a symbol tabal*/

static symbol_cell** head_addr();															/*prototype for private func head_addr */



static symbol_cell** head_addr()															/*private func head_addr*/
{
	static symbol_cell* head;																/*create a head for the link list*/

	return &head;																			/*sends its address*/

}

/*function for adding new values to the table*/
void set_symbol_val(char* symbol, int value, char attributes)
{
	symbol_cell* new_symbol;
	symbol_cell** head_address = head_addr();												/*get a pinter to the address of the head of the link list*/
	symbol_cell* pointer_to_cell = *head_address;											/*get the address of the head of the link list*/
	if ((new_symbol = (symbol_cell*) calloc(1, sizeof(symbol_cell))) == NULL)				/*get new dynamic space for the new symbol*/
	{
		print_error(MALLOC_FAILURE_CODE);
		exit(EXIT_FAILURE);
	}
	strcpy(new_symbol->symbol,symbol);														/*put the new symbol name*/
	new_symbol->value = value;																/*put the new symbol address (line number)*/
	new_symbol->attributes = attributes;													/*put a char that indicate the new symbol attribute ('c','d','s'...)*/
	
	if (*head_address == NULL)																/*if it is the first cell (link) in the link-list*/
	{
		new_symbol->next = NULL;
		new_symbol->prev = NULL;
		*head_address = new_symbol;
	}
	else
	{
		while (pointer_to_cell->next != NULL)												/*if it is not the first cell (link) in the link-list (adding it in the end of the list)*/
		{
			pointer_to_cell = pointer_to_cell->next;
		}
		new_symbol->next = NULL;
		new_symbol->prev = pointer_to_cell;
		pointer_to_cell->next = new_symbol;
	}

}

/*functin that get the symble name in the cell number "index"*/
char* get_symbol_symbol(int index)
{
	int i=0;
	symbol_cell* cell = *(head_addr());														/*get the address of the head of the link list*/

	while ((cell != NULL) && (i < index))													/*search for the index*/
	{
		cell = cell->next;
		i++;
	}
		
	if (cell == NULL)
		return NULL;
	else
	return cell->symbol;																	/*return the name*/
}

/*functin that get the cell number ("index") by searching its symble name */
int check_symbol_by_name(char* label)
{
	int index =0;
	symbol_cell* cell = *(head_addr());														/*get the address of the head of the link list*/

	if (cell == NULL)
		return NO_VAL;																		/*return the no_val if there is not list*/

	if (strcmp(cell->symbol, label) == ZERO)												/*search for the name*/
		return ZERO;

	index++;
	while ((cell = cell->next) != NULL)
	{
		if (strcmp(cell->symbol, label) == ZERO)
			return index;																	/*return the index*/
		index++;
	}
		return NO_VAL;																		/*return the no_val if there is not such name*/
}

/*functin that get the symble value (address \ number of line) in the cell number "index"*/
int get_symbol_value(int index)
{
	int i=0;
	symbol_cell* cell = *(head_addr());														/*get the address of the head of the link list*/

	while ((cell != NULL) && (i < index))
	{
		cell = cell->next;
		i++;
	}

	if (cell == NULL)
		return NO_VAL;																		/*return the no_val if there is not such name*/
	else
		return cell->value;																	/*return the index*/
}

/*functin that add an int value to cell that already exists*/
int add_to_symbol_value(int index,int add_val)
{
	int i=0;
	symbol_cell* cell = *(head_addr());														/*get the address of the head of the link list*/

	while ((cell != NULL) && (i < index))
	{
		cell = cell->next;
		i++;
	}

	if (cell == NULL)
		return NOT_OK;																		/*return the not_ok if there is not such index*/

	cell->value = (cell->value) + add_val;
	return OK;																				/*return the ok if successed*/
}

/*functin that get the symble attribute char in the cell number "index"*/
char get_symbol_attributes(int index)
{
	int i=0;
	symbol_cell* cell = *(head_addr());														/*get the address of the head of the link list*/

	if (index == NO_VAL)
		return END_STRING;

	while ((cell != NULL) && (i < index))
	{
		cell = cell->next;
		i++;
	}

	if (cell == NULL)
		return END_STRING;
	else
	return (cell->attributes);
}

/*functin that delete the list and free its alocate space*/
void symbol_free_all()
{
	symbol_cell* delete_cell;
	symbol_cell** head_addrs = (head_addr());												/*get the address of the head of the link list*/
	symbol_cell* cell = *head_addrs;
	delete_cell = cell;

	while (cell != NULL)																	/*free the malloc list*/
	{
		cell = cell->next;
		free(delete_cell);
		delete_cell = cell;
	}

	*head_addrs = NULL;																		/*delete the head address*/
}