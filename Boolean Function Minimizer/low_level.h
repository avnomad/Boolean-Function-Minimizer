#ifndef _low_level_
#define _low_level_

	/* includes */
#include "definitions.h"

	/* simple functions intended to be used by more complex ones */

	/* details about the functions can be found at the .c file   */

term *findterm(char *minterm,termlist target);
unsigned char count_ases(char *minterm);
unsigned char count_minus(char *minterm);
unsigned char count_variables(char *minterm);
char *simplify_terms(char *term1,char *term2,char minterm_size);
plain_termlist link_lists(plain_termlist list1,plain_termlist list2);
void deleteterm(char *minterm,plain_termlist *target);
plain_termlist copy(plain_termlist target);
#endif
