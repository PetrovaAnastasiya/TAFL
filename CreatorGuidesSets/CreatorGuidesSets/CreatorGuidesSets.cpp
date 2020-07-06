#include "Grammar.h"

int main()
{
	Grammar grammar("input1.txt");
	grammar.Sort();
	grammar.Factorize();
	grammar.PrintGrammar("output.txt");
	grammar.PrintGrammarF("output1.txt");

	return 0;
}