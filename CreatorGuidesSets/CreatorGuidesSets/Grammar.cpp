#include "Grammar.h"

//bool comp(Expression a, Expression b) {
//	int sizeA, sizeB;
//	sizeA = a.GetSize();
//	sizeB = b.GetSize();
//
//	//Expression shortExpression, longExpression;
//	//shortExpression = (sizeA < sizeB) ? a : b;
//	//longExpression = (sizeA >= sizeB) ? a : b;
//	//for (int i = 0; i < shortExpression.GetSize(); i++)
//	//{
//	//	if (shortExpression.GetVector()[i] > longExpression.GetVector()[i])
//	//		return false;
//	//}
//	return sizeA < sizeB;
//}
//
//bool compIndex(Expression a, Expression b) {
//	
//	//Expression shortExpression, longExpression;
//	//shortExpression = (sizeA < sizeB) ? a : b;
//	//longExpression = (sizeA >= sizeB) ? a : b;
//	/*for (int i = 0; i < shortExpression.GetSize(); i++)
//	{
//		if (shortExpression.GetVector()[i] > longExpression.GetVector()[i])
//			return false;
//	}*/
//	return a.GetVector()[0] < b.GetVector()[0];
//}

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
			m_grammar.push_back(expression);/*
			m_grammar[m_grammar.size() - 1]->PrintExpression(cout);*/
		}

		in.close();
	}
	m_factorizeGrammar = {};
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

void Grammar::AddExpression(Expression expression) 
{
	m_grammar.push_back(expression);
}

//void Grammar::SortGrammar()
//{
//	sort(m_grammar.begin(), m_grammar.end(), comp);
//}
//
//void Grammar::SortByIndex()
//{
//	sort(m_grammar.begin(), m_grammar.end(), compIndex);
//}

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
	/*minElement = Less(m_grammar[0].GetVector(), m_grammar[1].GetVector());
	minElement.PrintExpression(cout);*/
}

void Grammar::Factorize() 
{
	Expression factorExpression;
	//SortGrammar();
	//SortByIndex();
	
	
}