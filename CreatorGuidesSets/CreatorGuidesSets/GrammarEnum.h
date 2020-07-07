#pragma once
#include "Grammar.h"

using namespace std;

class GrammarEnum
{
	//В 0 элементе вектора хранится левая часть, в остальных правая
private:
	vector<Grammar> m_grammarEnum;
public:
	GrammarEnum(vector<Grammar> grammar = {}) : m_grammarEnum(grammar)
	{
	};
	GrammarEnum(Grammar grammar);
};