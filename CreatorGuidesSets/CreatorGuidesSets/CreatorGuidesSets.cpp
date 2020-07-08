#include "GrammarEnum.h"

int main()
{
	
	Grammar grammar("input.txt");
	GrammarEnum currentGrammar(grammar);
	grammar = {};
	Grammar partGrammar;
	for (size_t i = 0; i < currentGrammar.getSize(); i++)
	{
		partGrammar = currentGrammar.getElem(i);
		partGrammar.Sort();
		partGrammar.DeleteDuplicate();
		partGrammar.DeleteDuplicateRepeat();

		//partGrammar.Factorize();
		partGrammar.PrintGrammar("Split" + to_string(i) + ".txt");
		//partGrammar.PrintGrammarF("F" + to_string(i) + ".txt");

		grammar.AddParts(partGrammar);
		//currentGrammar.getElem(i).PrintGrammar("Split" + to_string(i) + ".txt");
	}

	grammar.PrintGrammar("output.txt");

	return 0;
}