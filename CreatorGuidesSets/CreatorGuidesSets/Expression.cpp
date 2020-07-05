#include "Expression.h"

Expression::Expression(std::istream& in) 
{
	string str, del;
	getline(in, str);
	del = " -";
	size_t found = str.find(del);
	if (found != std::string::npos) {
		cout << GRAMMAR_ERROR;
		return;
	}
	str.replace(found, REPLACE_NUM, " ");

}