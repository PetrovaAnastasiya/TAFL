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
	int m_counter;

public:
	Grammar(vector<Expression> grammar = {}, int counter = 0) : m_grammar(grammar), m_factorizeGrammar(grammar), m_counter(m_counter)
	{
	};
	Grammar(string fileName);
	void PrintGrammar(string fileName);
	void PrintGrammarF(string fileName);
	void AddExpression(Expression expression);
	void AddFactorizeExpression(Expression expression);

	//void SortGrammar();
	//void SortByIndex();
	Expression Less(Expression a, Expression b, int& minelementIndex, int k);
	void Sort();
	string neterminalCount(Expression expression);
	void Factorize();

}; 