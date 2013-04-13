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
