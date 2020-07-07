#include "Grammar.h"

int main()
{
	Grammar grammar("input.txt");
	grammar.Sort();
	Grammar partGrammar;
	partGrammar = grammar;
	partGrammar.SplitGrammar();
	partGrammar.Factorize();

	partGrammar.PrintGrammar("output.txt");
	grammar.PrintGrammarF("output1.txt");

	return 0;
}