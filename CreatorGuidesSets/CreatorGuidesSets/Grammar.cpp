#include "Grammar.h"

Grammar::Grammar(string fileName)
{
	ifstream in;
	try {
		in.open(fileName);
	}
	catch (exception err)
	{
		cout << FILE_OPEN_ERROR;
	}
	if (in.is_open())
	{
		while (!in.eof())
		{
			Expression expression =  Expression(in);
			m_grammar.push_back(expression);
		}

		in.close();
	}
	m_factorizeGrammar = {};

	m_counter = 0;
}

void Grammar::PrintGrammar(string fileName)
{
	ofstream out;
	try {
		out.open(fileName);
	}
	catch (exception err)
	{
		cout << FILE_OPEN_ERROR;
	}
	if (out.is_open())
	{
		for (size_t i = 0; i < m_grammar.size(); i++)
		{
			m_grammar[i].PrintExpression(out);
		}
	}
}

void Grammar::PrintGrammarF(string fileName)
{
	ofstream out;
	try {
		out.open(fileName);
	}
	catch (exception err)
	{
		cout << FILE_OPEN_ERROR;
	}
	if (out.is_open())
	{
		for (size_t i = 0; i < m_factorizeGrammar.size(); i++)
		{
			m_factorizeGrammar[i].PrintExpression(out);
		}
	}
}

void Grammar::AddExpression(Expression expression) 
{
	m_grammar.push_back(expression);
}
void Grammar::AddFactorizeExpression(Expression expression)
{
	m_factorizeGrammar.push_back(expression);
}

Expression Grammar::Less(Expression a, Expression b, int& minelementIndex, int k)
{
	if (a.GetSize() <= b.GetSize())
		return a;
	else
		if (a.GetSize() == b.GetSize())
		{
			int i = 1;
			while (i <= a.GetSize())
			{

				if (a.GetVector()[i] <= b.GetVector()[i])
				{
					return a;
				}
				else
				{
					minelementIndex = k;
					return b;
				}
				i++;
			}
		}
		else 
		{
			minelementIndex = k;	
			return b;
		}
}

void Grammar::Sort()
{
	vector<Expression> sorted{};
	Expression minElement = {};
	

	while (m_grammar.size() > 0) 
	{
		minElement = m_grammar[0];
		int index = 0;
		for (auto i = 1; i < m_grammar.size(); i++)
		{
			minElement = Less(minElement, m_grammar[i].GetVector(), index, i);
		}
		sorted.push_back(minElement);
		m_grammar.erase(m_grammar.begin() + index);
	}
	m_grammar = sorted;
}

string Grammar::neterminalCount(Expression expression)
{
	string str, count;
	str = expression.GetVector()[0];
	count = to_string(m_counter);
	str.insert(str.size() - 1 , count);
	return str;
}

bool Grammar::Equal(Expression a, Expression b)
{
	if (a.GetSize() != b.GetSize())
	{
		return false;
	}
	int i = 0;
	while (i < a.GetSize())
	{
		if (a.GetVector()[i] != b.GetVector()[i])
		{
			return false;
		}
		i++;
	}
	return true;
}

Expression Grammar::FindTail(Expression commonPart, Expression b)
{
	Expression tail = {};
	for (size_t i = commonPart.GetSize() + 1; i < b.GetSize(); i++)
	{
		tail.AddSymbol(b.GetVector()[i]);
	}
	return tail;
}


void Grammar::Factorize() 
{
	Expression savedCommonPart = {};
	Expression factorExpression = {};
	int i;
	auto j = 0;

	while (j < m_grammar.size() - 1)
	{
		Expression commonPart = {};
		Expression addedElem = {};
		Expression tail = {};

		factorExpression = m_grammar[j];
		Expression tmp = m_grammar[j + 1];
		i = 1;
		while ((i < factorExpression.GetSize()) && (factorExpression.GetVector()[i] == tmp.GetVector()[i]))
		{
			std::cout << factorExpression.GetVector()[i] + "||";
			std::cout << tmp.GetVector()[i] << endl;

			commonPart.AddSymbol(factorExpression.GetVector()[i]);
			i++;
		}

		if (commonPart.GetSize() > 0)
		{
			bool equal = false;

			equal = Equal(commonPart, savedCommonPart);
			if (equal)
			{
				addedElem.AddSymbol(neterminalCount(m_grammar[j]));
				tail = FindTail(commonPart, tmp);
				for (auto k = 0; k < tail.GetSize(); k++)
				{
					addedElem.AddSymbol(tail.GetVector()[k]);
				}
				m_factorizeGrammar.push_back(addedElem);
				addedElem = {};
			}
			else 
			{
				m_counter++;
				addedElem.AddSymbol(m_grammar[j].GetVector()[0]);

				for (auto k = 0; k < commonPart.GetSize(); k++)
				{
					addedElem.AddSymbol(commonPart.GetVector()[k]);
				}

				addedElem.AddSymbol(neterminalCount(m_grammar[j]));
				m_factorizeGrammar.push_back(addedElem);
				addedElem = {};

				tail = {};
				addedElem.AddSymbol(neterminalCount(m_grammar[j]));
				tail = FindTail(commonPart, factorExpression);
				for (auto k = 0; k < tail.GetSize(); k++)
				{
					addedElem.AddSymbol(tail.GetVector()[k]);
				}
				m_factorizeGrammar.push_back(addedElem);
				addedElem = {};

				tail = {};
				addedElem.AddSymbol(neterminalCount(m_grammar[j]));
				tail = FindTail(commonPart, tmp);
				for (auto k = 0; k < tail.GetSize(); k++)
				{
					addedElem.AddSymbol(tail.GetVector()[k]);
				}
				m_factorizeGrammar.push_back(addedElem);
				addedElem = {};
				
				savedCommonPart = commonPart;
			}
		}
		j++;
	}
}