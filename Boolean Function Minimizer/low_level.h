//	Copyright (C) 2006, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Boolean Function Minimizer.
 *
 *	Boolean Function Minimizer is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Boolean Function Minimizer is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Boolean Function Minimizer.  If not, see <http://www.gnu.org/licenses/>.
 */

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
