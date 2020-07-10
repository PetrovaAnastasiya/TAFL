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

	//m_counter = 0;
}

Grammar::Grammar(int counter)
{
	m_counter = counter;
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
		out.close();
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
	sorted = {};
	for (size_t i = 0; i < m_grammar.size(); i++)
	{
		sorted.push_back(m_grammar[i].GetVector());
		for (size_t j = i + 1; j < m_grammar.size(); j++)
		{
			if (m_grammar[i].GetVector()[1] == m_grammar[j].GetVector()[1])
			{
				sorted.push_back(m_grammar[j].GetVector());
			}
		}
	}
	m_grammar = sorted;
}

string Grammar::neterminalCount(Expression expression, int i)
{
	string str, count;
	str = expression.GetVector()[0];
	count = to_string(m_counter + i);
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
	if (tail.GetSize() < 1)
		tail.AddSymbol("@");
	
	return tail;
}

void Grammar::Factorize(int step)
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
			/*std::cout << factorExpression.GetVector()[i] + "||";
			std::cout << tmp.GetVector()[i] << endl;*/
			if (savedCommonPart.GetSize() == 0)
				commonPart.AddSymbol(factorExpression.GetVector()[i]);
			else
			{
				commonPart = savedCommonPart;
			}
			i++;
		}
		
		if (commonPart.GetSize() > 0)
		{
			bool equal = false;

			equal = Equal(commonPart, savedCommonPart);
			if (equal)
			{
				addedElem.AddSymbol(neterminalCount(m_grammar[j], step));
				//addedElem.AddSymbol("-");

				tail = FindTail(commonPart, tmp);
				//addedElem.AddSymbol("|");
				for (auto k = 0; k < tail.GetSize(); k++)
				{
					addedElem.AddSymbol(tail.GetVector()[k]);
				}
				m_factorizeGrammar.push_back(addedElem);
				//savedCommonPart = commonPart;

			}
			else
			{
				m_counter++;
				addedElem.AddSymbol(m_grammar[j].GetVector()[0]);
				//addedElem.AddSymbol("-");

				for (auto k = 0; k < commonPart.GetSize(); k++)
				{
					addedElem.AddSymbol(commonPart.GetVector()[k]);
				}

				addedElem.AddSymbol(neterminalCount(m_grammar[j], step));
				m_factorizeGrammar.push_back(addedElem);
				addedElem = {};

				tail = {};
				addedElem.AddSymbol(neterminalCount(m_grammar[j], step));
				//addedElem.AddSymbol("-");

				tail = FindTail(commonPart, factorExpression);
				for (auto k = 0; k < tail.GetSize(); k++)
				{
					addedElem.AddSymbol(tail.GetVector()[k]);
				}
				m_factorizeGrammar.push_back(addedElem);
				addedElem = {};

				//addedElem.AddSymbol("|");

				tail = {};
				addedElem.AddSymbol(neterminalCount(m_grammar[j], step));
				//addedElem.AddSymbol("-");
				tail = FindTail(commonPart, tmp);
				for (auto k = 0; k < tail.GetSize(); k++)
				{
					addedElem.AddSymbol(tail.GetVector()[k]);
				}
				m_factorizeGrammar.push_back(addedElem);

				savedCommonPart = commonPart;
			}
		}
		else
		{
			if (savedCommonPart.GetSize() == 0)
				m_factorizeGrammar.push_back(m_grammar[j]);
			savedCommonPart = {};
		}
		j++;
	}
	if (savedCommonPart.GetSize() == 0)
		m_factorizeGrammar.push_back(m_grammar[j]);
	if (m_factorizeGrammar.size() != 0)
		m_grammar = m_factorizeGrammar;
}

int Grammar::getSize()
{
	return m_grammar.size();
}

Expression Grammar::getExpression(int index)
{
	return m_grammar[index];
}

void Grammar::setExpression(int index, Expression added)
{
	m_grammar[index] = added;
}

void Grammar::DeleteDuplicate()
{
	for (size_t i = 0; i < m_grammar.size(); i++)
	{
		for (size_t j = i + 1; j < m_grammar.size(); j++)
		{
			if (Equal(m_grammar[i], m_grammar[j]))
			{
				m_grammar.erase(m_grammar.begin() + j);
			}
		}
	}
}

void Grammar::DeleteDuplicateRepeat()
{
	int size = m_grammar.size();
	DeleteDuplicate();
	if (size != m_grammar.size())
	{
		DeleteDuplicate();
	}
}

void Grammar::AddParts(Grammar smallGrammar)
{
	for (size_t i = 0; i < smallGrammar.getSize(); i++)
	{
		m_grammar.push_back(smallGrammar.getExpression(i));
	}
}

int Grammar::getCounter()
{
	return m_counter;
}

void Grammar::setCounter(int i)
{
	m_counter = i;
}
