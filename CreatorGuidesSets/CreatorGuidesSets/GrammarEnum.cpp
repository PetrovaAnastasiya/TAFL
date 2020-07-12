#include "GrammarEnum.h"

GrammarEnum::GrammarEnum(Grammar grammar)
{
	Grammar smallGrammar;
	string currNeterminal;
	currNeterminal = grammar.getExpression(0).GetVector()[0];
	smallGrammar.AddExpression(grammar.getExpression(0));
	for (size_t i = 1; i < grammar.getSize(); i++)
	{

		if (grammar.getExpression(i).GetVector()[0] == currNeterminal)
		{
			smallGrammar.AddExpression(grammar.getExpression(i));
		}
		else
		{
			m_grammarEnum.push_back(smallGrammar);
			currNeterminal = grammar.getExpression(i).GetVector()[0];
			smallGrammar = {};
			smallGrammar.AddExpression(grammar.getExpression(i));
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
		partGrammar = currentGrammar.getElem(i);
		partGrammar.Sort();
		partGrammar.DeleteDuplicate();
		partGrammar.DeleteDuplicateRepeat();
		
		Grammar a = partGrammar;
		Grammar b = partGrammar;
		Grammar c;

		a = a.getAGrammar();
		c = a;
		if (a.getSize() > 0)
		{
			a.modifyAGrammar();
			b = b.getBGrammar();
			if (b.getSize() == 0)
			{
				a = c;
				a.modifyAGrammarExcept();
			}
			if (b.getSize() > 0)
				b.modifyBGrammar();
		}
		else
		{
			a = partGrammar;
			b = {};
		}

		partGrammar = {};

		if (b.getSize() > 0)
		{
			if ((b.getSize() == 1) && b.getExpression(0).GetVector()[1] == "@")
			{
				b = {};
				a = c;
				a.modifyAGrammarExcept();
			}
			else
			{
				b.Factorize(step);
				for (size_t i = 0; i < b.getSize(); i++)
				{
					grammar.AddExpression(b.getExpression(i));
				}
			}
		} 
		//else
		//{
		//	a = c;
		//	a.modifyAGrammarExcept();
		//}

		a.Factorize(step);
		for (size_t i = 0; i < a.getSize(); i++)
		{
			grammar.AddExpression(a.getExpression(i));
		}
	}
	return grammar;
}



