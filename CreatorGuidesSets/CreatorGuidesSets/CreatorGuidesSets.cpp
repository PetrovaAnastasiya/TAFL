#include "Grammar.h"

int main()
{
	Grammar grammar("input.txt");
	grammar.SortGrammar();
	grammar.SortByIndex();
	grammar.PrintGrammar("output.txt");
	return 0;
}