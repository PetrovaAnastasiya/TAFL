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
	for (size_t i = 0; i < currentGrammar.getSize(); i++)
	{
		//cout << "111111111111111111111111" << endl;

		partGrammar = currentGrammar.getElem(i);
		partGrammar.Sort();
		partGrammar.DeleteDuplicate();
		partGrammar.DeleteDuplicateRepeat();
		
		//partGrammar.PrintGrammar("part" + to_string(step) + ".txt");

		Grammar a = partGrammar;
		Grammar b = partGrammar;
		
		a = a.getAGrammar();
		if (a.getSize() > 0)
		{
			b = b.getBGrammar();
			a.modifyAGrammar();
			b.modifyBGrammar();
		}
		else
		{
			a = partGrammar;
			b = {};
		}

		//a.PrintGrammar("a" + to_string(step) + ".txt");
		//b.PrintGrammar("b" + to_string(step) + ".txt");

		//cout << "222222222222222222222222" << endl;

		//partGrammar.getM_Grammar().clear();
		partGrammar = {};

		a.Factorize(step);
		for (size_t i = 0; i < a.getSize(); i++)
		{
			grammar.AddExpression(a.getExpression(i));
		}
		//cout << "333333333333333333333333" << endl;

		if (b.getSize() > 0)
		{
			b.Factorize(step);
			for (size_t i = 0; i < b.getSize(); i++)
			{
				grammar.AddExpression(b.getExpression(i));
			}
		}
		//partGrammar.PrintGrammar("part.txt");
		//grammar.PrintGrammar("grammar" + to_string (step) +".txt");


		//grammar.AddParts(partGrammar);
	}
	return grammar;
}



