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

#include "medium_level.h"

	/******************************************************************/
	/* Name:     divide_in_classes                                    */
	/* Purpose:  takes a plain_termlist containing the minterms given */
	/*			 by the user as an argument and divides them in		  */	
	/*			 classes of equal number of '1's.					  */
	/* Returns:  the list of classes								  */
	/******************************************************************/

classlist divide_in_classes(plain_termlist undivided,unsigned char minterm_size)
{	
		/* declarations */
	termlist temp_termlist;
	classlist divided;
	plain_term *current_node;

		/* initialize the classlist divided for future use */
	initialize(divided);
		/* if the inputed list is not empty */
	if (undivided)
	{	
		/* for each number of '1's */
		while (minterm_size--) 
		{
				/* initialize temp_termlist which will temporarily hold the terms which will form the class */
			initialize(temp_termlist);
				/* put the pointer current_node to point to the first node of the list undivided */
			current_node = first(undivided);
				/* while there are more nodes in the list */
			while (current_node)
			{
				/* if the minterm in the current node has the desired number of '1's */
				if (minterm_size == count_ases(content(current_node)))
				{
					addtostart(content(current_node),temp_termlist,term);
					first(temp_termlist)->used = 0;
					initialize(first(temp_termlist)->represented);
					addtostart(content(current_node),first(temp_termlist)->represented,plain_term);
				}
				current_node = next(current_node);
			}
			if (temp_termlist)
			{
				addtostart(temp_termlist,divided,Class);
				first(divided)->ases = minterm_size;
			}
		}
	}
	return divided;
}

classlist create_next_level(classlist current_level,unsigned char minterm_size)
{
		/* declarations */
	classlist next_level;
	Class *upper_class,*lower_class;
	term *upper_term,*lower_term;
	termlist temp_termlist;
	char *temp_term;

		/* initialize the list "lext_level" for future use */
	initialize(next_level);

	if (lower_class = first(current_level))
		while(next(lower_class))
		{
			upper_class = lower_class;
			lower_class = next(lower_class);
			if(abs(lower_class->ases-upper_class->ases) == 1)
			{
				initialize(temp_termlist);
				upper_term = content(first(upper_class));
				while (upper_term)
				{
					lower_term = content(first(lower_class));
					while(lower_term)
					{
						if (temp_term = simplify_terms(content(upper_term),content(lower_term),minterm_size))
						{
							if (!findterm(temp_term,temp_termlist))
							{
								addtostart(temp_term,temp_termlist,term);
								first(temp_termlist)->used = 0;
								first(temp_termlist)->represented = link_lists(upper_term->represented,lower_term->represented);
							}
							upper_term->used = 1;
							lower_term->used = 1;
						}
						lower_term = next(lower_term);
					}
					upper_term = next(upper_term);
				}
				if (temp_termlist)
				{
					addtostart(temp_termlist,next_level,Class);
					first(next_level)->ases = min(upper_class->ases,lower_class->ases);
				}
			}
		}
	return next_level;
}

termlist filter(levellist *levels)
{
	termlist filtered;
	Class *current_class;
	term *current_term;

		/* initialize the list "filtered" for future use */
	initialize(filtered);

		/*******************************************************************/
		/* the variables "current_class" and "current_term" are used here  */
		/* in favor of clarity as they allow us to avoid expressions like: */
		/* "content(first(content(first(content(first(levels))))))"        */
		/*******************************************************************/

	while (*levels)
	{
		current_class = first(content(first(*levels)));
		while (current_class)
		{
			current_term = first(content(current_class));
			while (current_term)
			{
				if (current_term->used)
				{
					while (current_term->represented)
						deletefirst(current_term->represented);
					free(current_term->content);
					deletefirst(content(current_class));
				}
				else
				{
					first(content(current_class)) = next(current_term);
					next(current_term) = first(filtered);
					first(filtered) = current_term;
				}
				current_term = first(content(current_class));
			}
			deletefirst(content(first(*levels)));
			current_class = first(content(first(*levels)));
		}
		deletefirst(*levels);
	}

	return filtered;
}

termlist find_implication_lists(termlist minterms,termlist prime_implicants)
{
	term *position;

	if(first(minterms))
	{
		while(first(prime_implicants))
		{
			while(first(first(prime_implicants)->represented))
			{
				if (position = findterm(content(first(first(prime_implicants)->represented)),minterms))
					addtostart(content(first(prime_implicants)),position->represented,plain_term);
				deletefirst(first(prime_implicants)->represented);
			}
			deletefirst(prime_implicants);
		}
	}
	return minterms;
}

plain_termlist choose_least_subset(termlist minterms,plain_termlist simplified)
{
	unsigned int number_of_minterms;
	unsigned int current_number_of_terms;
	unsigned int current_number_of_minus;
	unsigned int current;
	plain_term **combination;
	plain_termlist *implication_lists;
	unsigned int min_number_of_terms;
	unsigned int max_number_of_minus;
	plain_termlist optimal_combination;
	plain_termlist temp_combination;
	plain_term *current_term;

	
	lengh(number_of_minterms,minterms,termlist);
	if (number_of_minterms)
	{
		combination = malloc(number_of_minterms*sizeof(plain_term*));
		implication_lists = malloc(number_of_minterms*sizeof(plain_term*));

		current = 0;
		while(first(minterms))
		{
			*(implication_lists + current) = first(minterms)->represented;
			*(combination + current) = first(first(minterms)->represented);
			current++;
			deletefirst(minterms);
		}



		initialize(temp_combination);
		initialize(optimal_combination);
		min_number_of_terms = UINT_MAX;
		max_number_of_minus = 0;
		while(*(combination+number_of_minterms-1))
		{
			current_number_of_terms = 0;
			for(current=0;current<number_of_minterms;current++)
			{
				if(!findterm(content(*(combination + current)),(termlist)temp_combination))
				{
					addtostart(content(*(combination + current)),temp_combination,plain_term);
					current_number_of_terms++;
				}
			}
			if (current_number_of_terms<=min_number_of_terms)
			{
				current_number_of_minus = 0;
				current_term = first(temp_combination);
				while(current_term)
				{
					current_number_of_minus += count_minus(content(current_term));
					current_term = next(current_term);
				}
				if (current_number_of_terms<min_number_of_terms || current_number_of_minus>max_number_of_minus)
				{
					while(first(optimal_combination))
						deletefirst(optimal_combination);
					optimal_combination = temp_combination;
					min_number_of_terms = current_number_of_terms;
					max_number_of_minus = current_number_of_minus;
					initialize(temp_combination);
				}
			}
			while(first(temp_combination))
				deletefirst(temp_combination);
			*(combination) = next(*(combination));
			current = 0;
			while(!*(combination+current))
			{
				*(combination+current) = *(implication_lists+current);
				current++;
				*(combination+current) = next(*(combination+current));
				if(current==number_of_minterms-1) 
				{
					current =0;
				}
			}
		}
		while(first(optimal_combination))
		{
			addtostart(content(first(optimal_combination)),simplified,plain_term);
			deletefirst(optimal_combination);
		}
	}
	return simplified;
}
