#pragma once
#include <string>
#include <vector>
#include <map>
#include "Expression.h"

#define neterminal string

using namespace std;

class Grammar 
{
	//В 0 элементе вектора хранится левая часть, в остальных правая
	vector<Expression> grammar;
}; 