#include "header.h"


static int* line_num();									/*prototype for private func line_num*/
static int* ic();										/*prototype for private func ic*/
static int* dc();										/*prototype for private func dc*/
static int* error_cunter();								/*prototype for private func error_cunter*/

/*********************************** line_num ***********************************/

/*those function are responsible to work as a conter that count the number of source (assembly) code line we saw up to now*/

static int* line_num()									/*private func for line_num*/
{
	static int line_num = LINE_START_CUNT;				/*set the conter to begin from number 1 */
	return &line_num;
}

int get_line_num()										/*return the number of the line we are about to read from the source code*/
{
	return *(line_num());
}

void next_line_num()									/*go to the next line number*/
{
	int* corrent_line_num = line_num();
	*corrent_line_num = (*corrent_line_num) + 1;	
}

void line_num_back_to_start()							/*going back to the begining (number 1)*/
{
	*line_num() = LINE_START_CUNT;
}


/*********************************** IC ***********************************/

/*those function are responsible to work as a instraction conter (ic) */

static int* ic()										/*private func for ic*/
{
	static int ic = IC_START_CUNT;
	return &ic;
}

int get_ic()											/*return the corrent number of the instraction conter (ic)*/
{
	return *ic();
}

void increment_ic(int num)								/*increment the number of the instraction conter (ic) by the number "num" */
{
	int* corrent_ic = ic();
	*corrent_ic = (*corrent_ic) + num;
}

void ic_back_to_start()									/*going back to the begining (number 100)*/
{
	*ic() = IC_START_CUNT;
}




/*********************************** DC ***********************************/


/*those function are responsible to work as a data conter (dc) */

static int* dc()										/*private func for dc*/
{
	static int dc = DC_START_CUNT;
	return &dc;
}

int get_dc()											/*return the corrent number of the data conter (dc)*/
{
	return *dc();
}

void increment_dc(int num)								/*increment the number of the data conter (dc) by the number "num" */
{
	int* corrent_dc = dc();
	*corrent_dc = (*corrent_dc) + num;
}

void dc_back_to_start()									/*going back to the begining (number 0)*/
{
	*dc() = DC_START_CUNT;
}



/*********************************** ERROR CUNTER ***********************************/

/*those function are responsible to work as a error conter (syntactic errors in the source code) */

static int* error_cunter()								/*private func for error_cunter*/
{
	static int error_cunter = ERROR_CUNTER_START_CUNT;
	return &error_cunter;
}

int get_error_cunter()									/*return the corrent number error we saw up to now*/
{
	return *error_cunter();
}

void increment_error_counter()
{
	int* corrent_error_cunter = error_cunter();			/*increment the number of the error_cunter by 1 */
	*corrent_error_cunter = (*corrent_error_cunter) + 1;
}

void error_cunter_back_to_start()						/*going back to the begining (number 0)*/
{
	*error_cunter() = ERROR_CUNTER_START_CUNT;
}

