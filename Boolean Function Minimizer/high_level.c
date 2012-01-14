#include "high_level.h"

plain_termlist getterms(void)
{
		/* Declarations */
	unsigned char counter,minterm_size;
	plain_termlist minterms;
	char *buffer;
	char temp;
	plain_term *current_node;

		/* initialize the list of minterms for future use */
	initialize(minterms);
		/* irint instractions to the user */
	printf("Give the minterms, one in each line.\n");
	printf("They must all have the same number of variables.\n");
	printf("Anything apart from \"0\"s and \"1\"s in a line will signal the end of input.\n");

		/* Note: minterms are kept in memory as strings. */
		

		/* Allocate an initial buffer to hold the first minterm. */
		/* The size is the number of bits used to represent a    */
		/* memory address and thus more than enough to hold a    */
		/* minterm of the fuction with the largest number of     */
		/* variables this machine can process to simplify        */


	if(!(buffer = malloc(8*sizeof(buffer))))
	{
			/* if there is not enough memory, terminate. */
		fprintf(stderr,"Not enough memory. Terminating...\n");
		system("PAUSE");
		exit(1);
	}

		/* read the first minterm and save it's size in memory */
		/* the next minterms should be of that size            */
	counter = 0;
	while ((temp = getchar()) == '1' || temp == '0')
		*(buffer + counter++) = temp;
	*(buffer + counter) = '\0';

	minterm_size = counter;

		/* if the first character is null the user didn't give any minterms. Possibly the zero funcion. */
	if (temp == '\n')
	{
			/* create the first node and but the given minterm in it. */
			/* then free the buffer. the new buffer will be smaller   */
		addtostart(malloc(minterm_size),minterms,plain_term);
		strcpy(content(first(minterms)),buffer);
		free(buffer);		
			/* put "current_node" at the start of the list */
		current_node = first(minterms);
		for(;;)
		{
				/* allocate memory for another minterm */
			if (!(buffer = malloc(minterm_size)))
			{
					/* if there is not enough memory, terminate. */
				fprintf(stderr,"Not enough memory. Terminating...\n");
				system("PAUSE");
				exit(1);
			}
				/* read another minterm */
			counter = 0;
			while ((temp = getchar()) == '1' || temp == '0')
				*(buffer + counter++) = temp;
			*(buffer + counter) = '\0';
				/* check for end of input */ 
				/* newline means another term is to be read */
			if (temp == '\n')
			{
					/* Note: the findterm is declared to take a termlist as it's */
					/* input, but because both structs have the same first two   */
					/* members it should work fine with a plain_termlist too.    */
				if (findterm(buffer,(termlist)minterms))
				{
						/* a minterm is given twice, notify he user */
					printf("The last minterm was ignored as it has already been given.\n");
				}
				else
				{
					/* add the term to the list */
				add(buffer,current_node,plain_term);
					/* move "current_node" to the newly created node,  */
					/* so that the next node will be inserted after it */
				current_node = next(current_node);
				}
			}
			else
			{
					/* the input has ended, so the last buffer wasn't used and it can be freed */
				free(buffer);
				break;
			}
		}			
	}
	else
		free(buffer);
	return minterms;
}

plain_termlist simplify(plain_termlist initial_list)
{
	levellist levels;
	plain_termlist simplified;
	classlist temp_classlist;
	level *current_level;
	Class *current_class;
	term *current_term;
	termlist used_initial_minterms;
	termlist unused_simplified_minterms;
	unsigned char minterm_size;

							/***********/
							/* Phase 1 */
							/***********/

		/* initialize the list "levels" for fututre use */
	initialize(levels);
		/* initialize the list "simplified" for future use */
	initialize(simplified);
		/* check the input for an empty list and return a likewise       */
		/* empty list as an answer as there can't be any simplifications */
	if (empty(initial_list)) return 0;
		/* count the number of variables. the size of a minterm in */
		/* memory will be that number plus 1 and will be needed by */
		/* the other functions.                                    */
	minterm_size = count_variables(content(first(initial_list))) + 1;
		/* divide the given list of minterms in classes of */
		/* increasing number of "1"s and add the list of   */
		/* classes as the first level.                     */
	addtostart(divide_in_classes(initial_list,minterm_size),levels,level);
		/* put "current_level" to point to the first level */
	current_level = first(levels);
		/* while new levels can be created... */
	while (temp_classlist = create_next_level(content(current_level),minterm_size))
	{
			/* add the new level to the "levels" list */
		add(temp_classlist,current_level,level);
			/* make "current_level" point to the newly added level */
		current_level = next(current_level);
	}

							/***********/
							/* Phase 2 */
							/***********/

		/* initialize the list "used_initial_minterms" for future use */
	initialize(used_initial_minterms);

		/*******************************************************************/
		/* the variables "current_class" and "current_term" are used here  */
		/* in favor of clarity as they allow us to avoid expressions like: */
		/* "content(first(content(first(content(first(levels))))))"        */
		/*******************************************************************/

		/* disperse the first level */
	current_level = first(levels);
	current_class = first(content(current_level));
	while (current_class)
	{
		current_term = first(content(current_class));
		while (current_term)
		{
			if (current_term->used)
			{
				addtostart(content(current_term),used_initial_minterms,term);
				first(used_initial_minterms)->used = 0;
				initialize(first(used_initial_minterms)->represented);
			}
			else
				addtostart(content(current_term),simplified,plain_term);
			current_term = next(current_term);
			deletefirst(content(current_class));
		}
		current_class = next(current_class);
		deletefirst(content(current_level));
	}
	current_level = next(current_level);
	deletefirst(levels);

		/* filter the minterms in all levels and keep only those who weren't used */
	unused_simplified_minterms = filter(&levels);



	{
		term *current_simplified_minterm;
		term *designated_for_deletion;
		plain_term *current_represented_minterm;
		termlist rest_initial_minterms;
		
			/* initialize the list "rest_initial_minterms" for future use */
		initialize(rest_initial_minterms);
		

		while (used_initial_minterms)
		{
			current_simplified_minterm = first(unused_simplified_minterms);
			while (current_simplified_minterm)
			{
				current_represented_minterm = first(current_simplified_minterm->represented);
				while (current_represented_minterm)
				{
					if  (!strcmp(content(first(used_initial_minterms)),content(current_represented_minterm)))
						if (first(used_initial_minterms)->represented)
						{
							addtostart(content(first(used_initial_minterms)),rest_initial_minterms,term);
							initialize(first(rest_initial_minterms)->represented); /* requires rest_initial_minterms to be a termlist */
							deletefirst(used_initial_minterms);
							goto label;
						}
						else
						{
							first(used_initial_minterms)->represented = (plain_termlist)current_simplified_minterm;
							break;
						}
					current_represented_minterm = next(current_represented_minterm);
				}
				current_simplified_minterm = next(current_simplified_minterm);
			}
			designated_for_deletion = (term*)first(used_initial_minterms)->represented;
			while (first(designated_for_deletion->represented))
			{
				deleteterm(content(first(designated_for_deletion->represented)),(plain_termlist*)&rest_initial_minterms);
				deleteterm(content(first(designated_for_deletion->represented)),(plain_termlist*)&used_initial_minterms);
				deletefirst(designated_for_deletion->represented);
			}
			addtostart(content(designated_for_deletion),simplified,plain_term);
			deleteterm(content(designated_for_deletion),(plain_termlist*)&unused_simplified_minterms);

label:		;
		}


	rest_initial_minterms = find_implication_lists(rest_initial_minterms,unused_simplified_minterms);

	simplified = choose_least_subset(rest_initial_minterms,simplified);

	}


	return simplified;
}
