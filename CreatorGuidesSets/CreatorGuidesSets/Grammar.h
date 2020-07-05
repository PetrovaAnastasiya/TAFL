#pragma once
#include <string>
#include <vector>
#include <map>
#include "Expression.h"

#define neterminal string

using namespace std;

const string  FILE_OPEN_ERROR = "File open ERROR";

class Grammar 
{
	//В 0 элементе вектора хранится левая часть, в остальных правая
private:
	vector<Expression> m_grammar;
	vector<Expression> m_factorizeGrammar;

public:
	Grammar(vector<Expression> grammar = {}) : m_grammar(grammar), m_factorizeGrammar(grammar)
	{
	};
	Grammar(string fileName);
	void PrintGrammar(string fileName);
	void AddExpression(Expression expression);
	//void SortGrammar();
	//void SortByIndex();
	Expression Less(Expression a, Expression b, int& minelementIndex, int k);
	void Sort();
	void Factorize();
}; 