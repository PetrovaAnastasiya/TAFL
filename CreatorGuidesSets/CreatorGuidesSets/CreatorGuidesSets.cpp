#include "Grammar.h"

int main()
{
	Grammar grammar("input.txt");
	grammar.Sort();
	grammar.Factorize();
	grammar.PrintGrammar("output.txt");

	return 0;
}