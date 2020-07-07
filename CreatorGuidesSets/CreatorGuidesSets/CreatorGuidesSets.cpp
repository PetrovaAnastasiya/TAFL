#include "GrammarEnum.h"

int main()
{
	
	Grammar grammar("input.txt");
	GrammarEnum currentGrammar(grammar);
	Grammar partGrammar;
	for (size_t i = 0; i < currentGrammar.getSize(); i++)
	{
		partGrammar = currentGrammar.getElem(i);
		//partGrammar.Sort();
		partGrammar.DeleteDuplicate();
		partGrammar.Factorize();
		partGrammar.PrintGrammar("Split" + to_string(i) + ".txt");

		//currentGrammar.getElem(i).PrintGrammar("Split" + to_string(i) + ".txt");
	}


	grammar.Sort();
	
	partGrammar = grammar;
	//partGrammar.SplitGrammar();
	partGrammar.Factorize();

	/*partGrammar.PrintGrammar("output.txt");
	grammar.PrintGrammarF("output1.txt");*/

	return 0;
}