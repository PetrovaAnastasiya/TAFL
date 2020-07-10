#include "GrammarEnum.h"

GrammarEnum::GrammarEnum(Grammar grammar)
{
	Grammar smallGrammar;
	string currNeterminal;
	currNeterminal = grammar.getExpression(0).GetVector()[0];
	smallGrammar.AddExpression(grammar.getExpression(0));
	for (size_t i = 1; i < grammar.getSize(); i++)
	{
		//std::cout << grammar.getExpression(i).GetVector()[0] << " ";
		/*std::cout << grammar.getExpression(i).GetVector()[0] << " " ;
		std::cout << currNeterminal << endl;*/

		if (grammar.getExpression(i).GetVector()[0] == currNeterminal)
		{
			smallGrammar.AddExpression(grammar.getExpression(i));
			//smallGrammar.PrintGrammar(to_string(i) + "if.txt");
		}
		else
		{
			m_grammarEnum.push_back(smallGrammar);
			currNeterminal = grammar.getExpression(i).GetVector()[0];
			smallGrammar = {};
			smallGrammar.AddExpression(grammar.getExpression(i));
			//smallGrammar.PrintGrammar(to_string(i) + "else.txt");
		}
	}
	m_grammarEnum.push_back(smallGrammar);
}

Grammar GrammarEnum::getElem(int index)
{
	return m_grammarEnum[index];
}

int GrammarEnum::getSize()
{
	return m_grammarEnum.size();
}


Grammar GrammarEnum::AlgorythmFactorize(Grammar gr, int step)
{
	Grammar grammar("input.txt");

	if (gr.getSize() != 0)
	{
		grammar = gr;
	}
	GrammarEnum currentGrammar(grammar);
	grammar = {};
	Grammar partGrammar;
	Grammar del;
	for (size_t i = 0; i < currentGrammar.getSize(); i++)
	{
		partGrammar = currentGrammar.getElem(i);
		partGrammar.Sort();
		partGrammar.DeleteDuplicate();
		partGrammar.DeleteDuplicateRepeat();
		
		del = partGrammar.DeleteLeftRec();
		//for (size_t i = 0; i < del.size(); i++)
		//{
		//	partGrammar.setExpression(i, del[i]);

		//}
		//partGrammar.Factorize(step);
		grammar.AddParts(del);
	}
	return grammar;
	//grammar.PrintGrammar("out.txt");
}



