#include "GrammarEnum.h"

GrammarEnum::GrammarEnum(Grammar grammar)
{
	Grammar smallGrammar;
	string currNeterminal;
	currNeterminal = grammar.getExpression(1).GetVector()[0];
	for (size_t i = 0; i < grammar.getSize(); i++)
	{
		if (grammar.getExpression(i).GetVector()[0] == currNeterminal)
			smallGrammar.AddExpression(grammar.getExpression(i));
		else
		{
			m_grammarEnum.push_back(smallGrammar);
		}
	}
	m_grammarEnum.push_back(smallGrammar);
}