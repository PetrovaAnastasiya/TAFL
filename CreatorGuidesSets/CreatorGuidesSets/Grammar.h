#pragma once
#include <string>
#include <vector>
#include <map>
#include "Expression.h"

using namespace std;

const string  FILE_OPEN_ERROR = "File open ERROR";

class Grammar 
{
	//� 0 �������� ������� �������� ����� �����, � ��������� ������
private:
	vector<Expression> m_grammar;
	vector<Expression> m_factorizeGrammar;

	int m_counter;

public:
	Grammar(vector<Expression> grammar = {}, int counter = 0) : m_grammar(grammar), m_factorizeGrammar(grammar), m_counter(counter)
	{
	};
	Grammar(string fileName);
	void PrintGrammar(string fileName);
	void PrintGrammarF(string fileName);
	void AddExpression(Expression expression);
	void AddFactorizeExpression(Expression expression);
	Expression Less(Expression a, Expression b, int& minelementIndex, int k);
	void Sort();
	string neterminalCount(Expression expression);
	bool Equal(Expression a, Expression b);
	Expression FindTail(Expression commonPart, Expression b);
	void Factorize();
	//void FactorizeRepeat();
	int getSize();
	Expression getExpression(int index);
	void DeleteDuplicate();
	void AddParts(Grammar smallGrammar);
}; 