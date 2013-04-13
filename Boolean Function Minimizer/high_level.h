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

#ifndef _high_level_
#define _high_level_

	/* includes */
#include "medium_level.h"
	/* details about the functions can be found at the .c file   */

plain_termlist getterms(void);
plain_termlist simplify(plain_termlist initial_list);

#endif
