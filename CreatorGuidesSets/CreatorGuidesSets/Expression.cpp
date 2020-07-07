#include "Expression.h"

Expression::Expression(std::istream& in) 
{
	string str, del;
	if (!in.eof())
	{
		getline(in, str);
		regex regex{ R"([\s]+)" }; // split on space 
		sregex_token_iterator it{ str.begin(), str.end(), regex, -1 };
		vector<std::string> words{ it, {} };
		m_symbol = words;
		m_symbol.erase(m_symbol.begin() + 1);
	}

}

void Expression::PrintExpression(ofstream& out)
{
	copy(m_symbol.begin(), m_symbol.end(), ostream_iterator<string>(out, " "));
	out << endl;
}

void Expression::PrintExpression(ostream& out)
{
	copy(m_symbol.begin(), m_symbol.end(), ostream_iterator<string>(out, " "));
	out << endl;
}

int Expression::GetSize()
{
	return m_symbol.size();
}

vector<string> Expression::GetVector()
{
	return m_symbol;
}

void Expression::AddSymbol(string symbol)
{
	m_symbol.push_back(symbol);
}
