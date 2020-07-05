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
	//� 0 �������� ������� �������� ����� �����, � ��������� ������
private:
	vector<Expression> m_grammar;
public:
	Grammar(vector<Expression> grammar = {}) : m_grammar(grammar)
	{
	};
	Grammar(string fileName);
	void PrintGrammar(string fileName);
	void AddExpression(Expression expression);
	void SortGrammar();
	void SortByIndex();
}; 