#pragma once
#include "Grammar.h"

using namespace std;

class GrammarEnum
{
	//� 0 �������� ������� �������� ����� �����, � ��������� ������
private:
	vector<Grammar> m_grammarEnum;
public:
	GrammarEnum(vector<Grammar> grammar = {}) : m_grammarEnum(grammar)
	{
	};
	GrammarEnum(Grammar grammar);
};