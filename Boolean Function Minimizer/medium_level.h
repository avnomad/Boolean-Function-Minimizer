#ifndef _medium_level_
#define _medium_level_

	/* includes */
#include "low_level.h"
	/* details about the functions can be found at the .c file   */

classlist divide_in_classes(plain_termlist undivided,unsigned char minterm_size);
classlist create_next_level(classlist current_level,unsigned char minterm_size);
termlist filter(levellist *levels);
termlist find_implication_lists(termlist minterms,termlist prime_implicants);
plain_termlist choose_least_subset(termlist minterms,plain_termlist simplified);
#endif
