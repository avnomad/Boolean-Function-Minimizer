#include "high_level.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	plain_termlist minterm_list;

	puts("---------------------------------------------------");
	puts(" Wellcome to the Boolean Function Minimizirer v1.0 ");
	puts("---------------------------------------------------");
	puts("Copyright(c) 2006 Anogeianakis Baptistis.\n");
	puts("                            All Rights Reserved.\n\n");
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