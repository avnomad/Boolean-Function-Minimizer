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

#ifndef _definitions_
#define _definitions_

	/* includes */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

	/******************************************************************/
	/* definitions for the various types of lists used in the program */
	/******************************************************************/

	/* The plain_termlists are used throughout the program in cases   */
	/* where all the information we need is the minterms.             */

typedef struct plain_term_tag
{
	char *content;
	struct plain_term_tag *next;
	
} plain_term;
typedef plain_term *plain_termlist;

	/* The termlists are more complex versions of plain_termlists.    */
	/* Used as well throughout the program, they contain information  */
	/* concerning the contained minterm like whether it is used or    */
	/* not and other minterms it represents or it is represented by   */

typedef struct term_tag
{
	char *content;
	struct term_tag *next;
	unsigned char used;
	plain_term *represented;	
} term;
typedef term *termlist;

	/* The classlists are used in the first phase of the minimization */
	/* process in order to represent the classes of minterms with     */
	/* equal number of '1's. In order to avoid unnecessary            */
	/* calculations, the number of '1's is kept in the 'ases' field   */
	/* and calculated in the creation process without the need of any */
	/* countings.                                                     */

typedef struct class_tag
{
	term *content;
	struct class_tag *next;
	unsigned char ases;
} Class;
typedef Class *classlist;

	/* The levellists are used in the first phase of the minimization */
	/* process, holding the levels of minimization. The logic is that */
	/* each level has classes, which contain terms, each of which     */
	/* will, in general, represent a number of initial minterms and   */
	/* be marked as used or not                                       */

typedef struct level_tag
{
	Class *content;
	struct level_tag *next;
} level;
typedef level *levellist;


	/***********************************************/
	/* universal macros for manipulating the lists */
	/***********************************************/

	/* NOTE: The position of a node is a pointer to it */

#define initialize(list) ((list) = 0)						/* Initializes the list for future use */
#define first(list) (list)									/* Returns the position of the first node in the list or NULL if there isn't any */
#define next(position) ((position)->next)					/* Returns the position of the next node in the list assuming there is one */
#define empty(list) ((list) == 0)							/* Returns 1 if the list has at least one element or 0 is it's empty */
#define content(position) ((position)->content)				/* Returns the information in the field "content" of the node designated by "position". This can be an object of any type e.g. a list*/
#define put(data,position) ((position)->content = data)		/* Puts the information "data" in the field "content" of the node designated by "position" */


	/**********************************************************/
	/* Adds a new node of type "nodetype" at the start of the */
	/* list named "list" containing the information "data" in */
	/* it's content field.If there is not enough memory for   */
	/* the new node it terminates the program.                */
	/**********************************************************/

#define addtostart(data,list,nodetype) \
{\
	nodetype *______6;\
	if (______6 = malloc(sizeof(nodetype)))\
	{\
		______6->content = data;\
		______6->next = (list);\
		(list) = ______6;\
	}\
	else\
	{\
		fprintf(stderr,"Not enough memory. Terminating...");\
		system("PAUSE");\
		exit(1);\
	}\
}

	/***********************************************************/
	/* Adds a new node of type "nodetype" right after the node */
	/* designated by "position". The new node contains "data"  */
	/* in it's "content" field. If there is not enough memory  */
	/* for the new node it terminates the program.             */
	/***********************************************************/

#define add(data,position,nodetype) \
{\
	nodetype *______6;\
	if (______6 = malloc(sizeof(nodetype)))\
	{\
		______6->content = data;\
		______6->next = (position)->next;\
		(position)->next = ______6;\
	}\
	else\
	{\
		fprintf(stderr,"Not enough memory. Terminating...\n");\
		system("PAUSE");\
		exit(1);\
	}\
}

	/************************************************************/
	/* Adds a new node of type "nodetype" right before the node */
	/* designated by "position". The new node contains "data"   */
	/* in it's "content" field. "position" now point to the     */
	/* newly created node. If there is not enough memory for    */
	/* the new node it terminates the program.                  */
	/************************************************************/

#define addbefore(data,position,nodetype) \
{\
	nodetype *______6;\
	if (______6 = malloc(sizeof(nodetype)))\
	{\
		______6->content = (position)->content;\
		______6->next = (position)->next;\
		(position)->next = ______6;\
		(position)->content = data;\
	}\
	else\
	{\
		fprintf(stderr,"Not enough memory. Terminating...\n");\
		system("PAUSE");\
		exit(1);\
	}\
}

	/****************************************************************/
	/* Deletes the first node of the list "list" freing the memory. */
	/* It assumes there is a first element.                         */
	/****************************************************************/

#define deletefirst(list) \
{\
	void *______6;\
	______6 = (list);\
	(list) = (list)->next;\
	free(______6);\
}

	/*******************************************************************/
	/* Deletes the node right after the node designated by "position". */
	/* It assumes there is a next element.                             */
	/*******************************************************************/

#define deletenext(position,nodetype) \
{\
	nodetype *______6;\
	______6 = (position)->next;\
	(position)->next = ______6->next;\
	free(______6);\
}

	/************************************************************************/
	/* Prints the information in the "content" field of every node in the   */
	/* list "list" which is of type "listtype" starting at the begining of  */
	/* the list and finishing at the end. This is done under the control of */
	/* the "format" string.                                                 */
	/************************************************************************/

#define printlist(format,list,listtype) \
{\
	listtype ______6 = (list);\
	while (______6)\
	{\
		printf(format,______6->content);\
		______6 = ______6->next;\
	}\
}

	/************************************************************************/
	/* Calculates the lengh of the list "list" wich is of type "listtype"   */
	/* and puts it in counter wich should be an integer type of suficient   */
	/* size.                                                                */
	/************************************************************************/

#define lengh(counter,list,listtype) \
{\
	listtype ______6 = (list);\
	counter = 0;\
	while (______6)\
	{\
		counter++;\
		______6 = ______6->next;\
	}\
}

	/******************************/
	/* simple mathimatical macros */
	/******************************/

#define abs(A) ((A)>=0?(A):-(A))
#undef min
#define min(A,B) ((A)<(B)?(A):(B))
#endif
