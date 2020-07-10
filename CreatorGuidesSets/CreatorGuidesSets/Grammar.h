#pragma once
#include <string>
#include <vector>
#include <map>
#include "Expression.h"

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
	Grammar(vector<Expression> grammar = {}, int counter = 0) : m_grammar(grammar), m_factorizeGrammar(grammar), m_counter(counter)
	{
	};
	Grammar(string fileName);
	Grammar(int counter);

	void PrintGrammar(string fileName);
	void PrintGrammarF(string fileName);
	void AddExpression(Expression expression);
	void AddFactorizeExpression(Expression expression);
	Expression Less(Expression a, Expression b, int& minelementIndex, int k);
	void Sort();
	string neterminalCount(Expression expression, int i);
	bool Equal(Expression a, Expression b);
	Expression FindTail(Expression commonPart, Expression b);
	void Factorize(int step);
	int getSize();
	Expression getExpression(int index);
	void setExpression(int index, Expression added);
	void DeleteDuplicate();
	void DeleteDuplicateRepeat();
	void AddParts(Grammar smallGrammar);
	int getCounter();
	void setCounter(int i);
}; 