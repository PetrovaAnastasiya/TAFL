#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

const string GRAMMAR_ERROR = "Grammar Error";
const int REPLACE_NUM = 3;

class Expression 
{
private:
	vector<string> m_symbol;

public:
	Expression(vector<string> symbol = {}) : m_symbol(symbol) 
	{
	};
	Expression(std::istream& in);

	void PrintExpression(ofstream& out);
	void PrintExpression(ostream& out);
	int GetSize();
	vector<string> GetVector();
	void AddSymbol(string symbol);
	void Insert();
};