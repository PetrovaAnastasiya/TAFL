#include "Grammar.h"

int main()
{
	Grammar grammar("input.txt");
	grammar.Sort();
	grammar.Factorize();
	grammar.PrintGrammarF("output.txt");

	return 0;
}