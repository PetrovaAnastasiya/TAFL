#include "GrammarEnum.h"

GrammarEnum::GrammarEnum(Grammar grammar)
{
	Grammar smallGrammar;
	string currNeterminal;
	currNeterminal = grammar.getExpression(0).GetVector()[0];
	for (size_t i = 0; i < grammar.getSize(); i++)
	{
		std::cout << grammar.getExpression(i).GetVector()[0] << " ";
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
			//smallGrammar.PrintGrammar(to_string(i) + "else.txt");
		}
		if ((i>1)&&(grammar.getExpression(i).GetVector()[0] == grammar.getExpression(i-1).GetVector()[0]))
		{
			smallGrammar.AddExpression(grammar.getExpression(i-1));
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