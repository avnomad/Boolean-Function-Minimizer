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

#include "low_level.h"

	/******************************************************************/
	/* Name:     findterm                                             */
	/* Purpose:  searches an (unsorted) termlist                      */
	/*           to find the term containing the minterm              */
	/* Returns:  a pointer to the term or NULL if it cannot be found  */
	/******************************************************************/

term *findterm(char *minterm,termlist target)
{
	while (target)
	{
		if (strcmp(target->content,minterm))
			target = target->next;
		else
			break;
	}
	return target;
}

	/****************************************************/
	/* Name:     count_ases                             */
	/* Purpose:  counts the number of '1's in a string  */
	/*           representing a minterm                 */
	/* Returns:  the number of '1's                     */
	/****************************************************/

unsigned char count_ases(char *minterm)
{
	unsigned char counter = 0;
	while (*minterm)
		if (*minterm++ == '1') counter++;
	return counter;
}

	/****************************************************/
	/* Name:     count_minus                            */
	/* Purpose:  counts the number of '-'s in a string  */
	/*           representing a minterm                 */
	/* Returns:  the number of '-'s                     */
	/****************************************************/

unsigned char count_minus(char *minterm)
{
	unsigned char counter = 0;
	while (*minterm)
		if (*minterm++ == '-') counter++;
	return counter;
}

	/****************************************************/
	/* Name:     count_variables                        */
	/* Purpose:  counts the number of variables in a    */
	/*			 string representing a minterm. That is */
	/*			 the number of characters in the string */
	/* Returns:  the number of variables                */
	/****************************************************/

unsigned char count_variables(char *minterm)
{
	unsigned char counter = 0;
	while (*minterm++) counter++;
	return counter;
}

	/****************************************************/
	/* Name:     simplify_terms                         */
	/* Purpose:  takes two strings representing two     */
	/*			 minterms or prime implicants as an     */
	/*			 input and creates another string       */
	/*			 representing the minimized term if a   */
	/*			 minimization can be done               */
	/* Returns:  the address of the minimized term, or  */
	/*			 NULL if a minimization is imposssible  */
	/****************************************************/

char *simplify_terms(char *term1,char *term2,char minterm_size)
{
		/* declarations */
	char *simplified_term;
	unsigned char counter = 0,differences = 0;

		/* allocate memory for the new term */
	if (!(simplified_term = malloc(minterm_size)))
	{
		/* if there is not enough memory, terminate. */
		fprintf(stderr,"Not enough memory. Terminating...\n");
		system("PAUSE");
		exit(1);
	}
		/* look each one of the strings characters in succetion */
	for(counter=0;counter<minterm_size;counter++)
	{
		/* check if the characters are equal */
		if (*(term1+counter) == *(term2+counter))
		{
			/* they are. make the respective character of the new string equal as well */
			*(simplified_term+counter) = *(term1+counter);
		}
		else
		{
			/* a difference has been found. Check if it is the first. */
			if (differences)
			{
				/* a second difference has been found. Free the memory */
				/* and return a value that cannot be the address of a string. */
				free(simplified_term);
				return 0;
			}
			else
			{
				/* it's the first difference. But a '-' in the minimized term */
				/* to represent the absence of the variable. */
				*(simplified_term+counter) = '-';
				differences++;
			}
		}
	}	
	return simplified_term;
}

	/****************************************************/
	/* Name:     link_lists                             */
	/* Purpose:  inputs two plain_termlists and creates */
	/*			 a new one which contains the elements  */
	/*			 of both lists. the lists remain        */
	/*			 unchanged.                             */
	/* Returns:  the newly created list                 */
	/****************************************************/

plain_termlist link_lists(plain_termlist list1,plain_termlist list2)
{
	plain_termlist linked;

	initialize(linked);
	while (list1)
	{
		addtostart(content(list1),linked,plain_term);
		list1 = next(list1);
	}
	while (list2)
	{
		addtostart(content(list2),linked,plain_term);
		list2 = next(list2);
	}
	return linked;
}

	/****************************************************/
	/* Name:     deleteterm                             */
	/* Purpose:  finds the minterm in the target        */
	/*			 plain_termlist and deletes the         */
	/*			 corresponding node. Though designed    */
	/*			 for plain_termlists it works with any  */
	/*			 list that has the first two fields of  */
	/*			 it's node being pointers with the      */
	/*			 second pointing to the next node.      */
	/* Returns:  Nothing.                               */
	/****************************************************/

void deleteterm(char *minterm,plain_termlist *target)
{
	plain_term *current_node;
	if (*target)
	{
		if (strcmp(content(*target),minterm))
		{
			current_node = *target;
			while (next(current_node))
				if (strcmp(content(next(current_node)),minterm))
					current_node = next(current_node);
				else
				{
					deletenext(current_node,plain_term);
					break;
				}
		}
		else
			deletefirst(*target);
	}
}

	/****************************************************/
	/* Name:     copy                                   */
	/* Purpose:  creates a new plain_termlist which is  */
	/*			 identical to the one given as an       */
	/*			 argument                               */
	/* Returns:  the newly created list                 */
	/****************************************************/

plain_termlist copy(plain_termlist target)
{
	plain_termlist copied;

	initialize(copied);
	while(first(target))
	{
		addtostart(content(first(target)),copied,plain_term);
		first(target) = next(first(target));
	}
	return copied;
}
