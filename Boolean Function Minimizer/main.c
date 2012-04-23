//	Copyright (C) 2006, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
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

#include "high_level.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	plain_termlist minterm_list;

	puts("---------------------------------------------------");
	puts(" Welcome to the Boolean Function Minimizirer v1.0 ");
	puts("---------------------------------------------------");
	puts("Copyright (C) 2006, 2012 Vaptistis Anogeianakis.\n");
	puts("This program comes with ABSOLUTELY NO WARRANTY.");
	puts("This is free software, and you are welcome to redistribute it");
	puts("under certain conditions; see license.txt for details.\n\n");
	minterm_list = getterms();

	puts("The given minterms are:");
	printlist("%s\t",minterm_list,plain_termlist);
	putchar('\n');

	puts("The simplified minterms are:");
	printlist("%s\t",simplify(minterm_list),plain_termlist);
	putchar('\n');

	system("PAUSE");
	return 0;
}