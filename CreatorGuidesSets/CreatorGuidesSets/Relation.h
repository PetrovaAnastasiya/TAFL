#pragma once

#include <vector>
#include <map>
#include "Grammar.h"

#define neterminal string

using namespace std;

class Relation 
{
	map<string, int> columnNum;
	vector<map<neterminal, vector<bool>>> relation;
};