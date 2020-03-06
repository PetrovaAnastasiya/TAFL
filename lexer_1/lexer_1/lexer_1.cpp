#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <regex>

using namespace std;
const string FILE_OUT_NAME = "output.txt";

enum state {
	START,
	PLUS, //
	MINUS, //
	MULTIPLICATION,//
	DIVISION, //
	EXP, //
	DOT,
	COMMA,
	COLON,
	SEMI_COLON, // 
	SMALLER, // 
	MORE, //
	EQUAL, //
	LEFT_CURLY_BRACE, //
	RIGHT_CURLY_BRACE, //
	LEFT_SQUARE_BRACKET,
	RIGHT_SQUARE_BRACKET,
	LEFT_PARENTHESIS, //
	RIGHT_PARENTHESIS, //
	COMPARISON, //
	SMALLER_EQUAL, //
	MORE_EQUAL,//
	NOT_EQUAL, //
	LOGICAL_NEGATION,
	LOGICAL_AND, //
	LOGICAL_OR, //
	ONE_LINE_COMMENT,//
	MULTILINE_COMMENT,//
	STRING,//
	IDENTIFICATOR,//
	ERROR,//
	IF,//
	ELSE,//
	WHILE, //
	FOR,//
	INT,//
	FLOAT,
	DOUBLE,//
	VOID, 
	VAR, //
	STRING_TYPE, // 
	BOOL, //
	CHAR, //
	READ, //
	WRITE, //
	NUMBER
};

map<state, const char* > info = {
	{START, "START"},
	{INT, "INT"},
	{DOUBLE, "DOUBLE"},
	{FLOAT, "FLOAT"},
	{VOID, "VOID"},
	{VAR, "VAR"},
	{STRING_TYPE, "STRING_TYPE"},
	{BOOL, "BOOL"},
	{CHAR, "CHAR"},
	{IF, "IF"},
	{ELSE, "ELSE"},
	{WHILE, "WHILE"},
	{FOR, "FOR"},
	{READ, "READ"},
	{WRITE, "WRITE"},
	{STRING, "STRING"},
	{PLUS, "PLUS"},
	{MINUS, "MINUS"},
	{MULTIPLICATION, "MULTIPLICATION"},
	{DIVISION, "DIVISION"},
	{EXP, "EXP"},
	{DOT, "DOT"},
	{COMMA, "COMMA"},
	{COLON, "COLON"},
	{SEMI_COLON, "SEMI_COLON"},
	{SMALLER, "SMALLER"},
	{MORE, "MORE"},
	{SMALLER_EQUAL, "SMALLER_EQUAL"},	
	{MORE_EQUAL, "MORE_EQUAL"},
	{NOT_EQUAL, "NOT_EQUAL"},
	{EQUAL, "EQUAL"},
	{COMPARISON, "COMPARISON"},
	{LEFT_CURLY_BRACE, "LEFT_CURLY_BRACE"},
	{RIGHT_CURLY_BRACE, "RIGHT_CURLY_BRACE"},
	{LEFT_SQUARE_BRACKET, "LEFT_SQUARE_BRACKET"},
	{RIGHT_SQUARE_BRACKET, "RIGHT_SQUARE_BRACKET"},
	{LEFT_PARENTHESIS, "LEFT_PARENTHESIS"},
	{RIGHT_PARENTHESIS, "RIGHT_PARENTHESIS"},
	{ONE_LINE_COMMENT, "ONE_LINE_COMMENT"},
	{MULTILINE_COMMENT, "MULTILINE_COMMENT"},
	{ERROR, "ERROR"},
	{LOGICAL_NEGATION, "LOGICAL_NEGATION"},
	{LOGICAL_AND, "LOGICAL_AND"},
	{LOGICAL_OR, "LOGICAL_OR"},
	{IDENTIFICATOR, "IDENTIFICATOR"},
	{NUMBER, "NUMBER"}
};

bool openFile(ifstream& file, string fileName)
{
	file.open(fileName);
	if (file.is_open())
		return true;
	else
	{
		return false;
	}
}

bool checkIdent(char ch)
{
	if (isdigit(ch) || isalpha(ch))
		return true;
	return false;
}

bool checkNumber(string result)
{
	std::regex re(R"(^[-+]?0b([01]+)|^[-+]?([0-9]+)$|^[-+]?([0-9]+\.[0-9]+)$|^[-+]?0x([0-9A-F]+)$)");
	if (regex_match(result.begin(), result.end(), re))
		return true;
	return false;
}

int main()
{
	const string FILE_IN_NAME = "input.txt";
	ifstream fileForWork;
	bool is_opened = openFile(fileForWork, FILE_IN_NAME);
	int numLine = 0;
	string str, result = "", errorText = "";
	enum state currState = START;
	char ch, nextCh;
	if (is_opened)
		while (getline(fileForWork, str))
		{
			numLine++;
			int i = 0;
			while (i < str.length())
			{
				ch = str[i];
				if (i < str.size() - 1)
					nextCh = str[i + 1];
				else
					nextCh = ch;
				if (isdigit(ch)) {
					result = "";
					int j = i;
					while (j != str.size())
					{
						ch = str[j];
						if ((ch == ' ') || (ch == ';') || (ch == ',') || (ch == '}') || (ch == ']') || (ch == ')'))
							break;
						result += ch;
						i = j;
						j++;
					}
					currState = START;
					
					if (result.size() < 11)
					{
						if (checkNumber(result))
							currState = NUMBER;
					}
					else
					{
						currState = ERROR;
						errorText = "Out of range";
					}
					if (currState == START)
					{
						currState = ERROR;
						errorText = "invalid data " + result;
					}
				}
				else if (isalpha(ch))
				{
					result = "";
					int j = i;
					while(j != str.size())
					{
						ch = str[j];
						if (!isalpha(ch))
							break;
						result += ch;
						i = j;

						j++;
					}
					currState = START;
					if (result == "if")
						currState = IF;
					if (result == "else")
						currState = ELSE;
					if (result == "while")
						currState = WHILE;
					if (result == "for")
						currState = FOR;
					if (result == "int")
						currState = INT;
					if (result == "double")
						currState = DOUBLE;
					if (result == "float")
						currState = FLOAT;
					if (result == "void")
						currState = VOID;
					if (result == "var")
						currState = VAR;
					if (result == "string")
						currState = STRING_TYPE;
					if (result == "bool")
						currState = BOOL;
					if (result == "char")
						currState = CHAR;
					if (result == "read")
						currState = READ;
					if (result == "write")
						currState = WRITE;
					if (currState == START)
					{
						currState = ERROR;
						errorText = "invalid data " + result;
					}
				}
				else
				switch (ch)
				{
					case '$':
					{
						i++;
						int position = i;
						result = "$";
						int j = i;
						
						while (j != str.size())
						{
							ch = str[j];
							j++;
							if (!checkIdent(ch))
								break;
							result += ch;
							i = j;
						}
						i -= 1;
						if (result.size() < 257)
						{
							currState = IDENTIFICATOR;
							cout << "(" << numLine << "," << position << ") - (" << numLine << "," << i+1 << ") " << info.at(currState) << " " << result << endl;
						}
						else 
						{
							currState = ERROR;
							errorText = "Out of range";
						}
						break;
					}

					case '+':
					{
						result = '+';
						currState = PLUS;
						break;
					}

					case '-':
					{
						result = '-';
						currState = MINUS;
						break;
					}

					case '*':
					{
						result = '*';
						currState = MULTIPLICATION;
						break;
					}

					case '/':
					{
						result = '/';
						currState = DIVISION;
						break;
					}

					case '^':
					{
						result = '^';
						currState = EXP;
						break;
					}

					case '.':
					{
						result = '.';
						currState = DOT;
						break;
					}

					case ',':
					{
						result = ',';
						currState = COMMA;
						break;
					}

					case ':':
					{
						result = ':';
						currState = COLON;
						break;
					}

					case ';':
					{
						result = ';';
						currState = SEMI_COLON;
						break;
					}

					case '=':
					{
						if (nextCh == '=')
						{
							result = "==";
							currState = COMPARISON;
							i++;
						}
						else
						{
							result = '=';
							currState = EQUAL;
						}
						break;
					}

					case '<':
					{
						if (nextCh == '=')
						{
							result = "<=";
							currState = SMALLER_EQUAL;
							i++;
						}
						else
						{
							result = '<';
							currState = SMALLER;
						}
						break;
					}

					case '>':
					{
						if (nextCh == '=')
						{
							result = ">=";
							currState = MORE_EQUAL;
							i++;
						}
						else
						{
							result = '>';
							currState = MORE;
						}
						break;
					}

					case '{':
					{
						result = '{';
						currState = LEFT_CURLY_BRACE;
						break;
					}

					case '}':
					{
						result = '}';
						currState = RIGHT_CURLY_BRACE;
						break;
					}

					case '[':
					{
						result = '[';
						currState = LEFT_SQUARE_BRACKET;
						break;
					}

					case ']':
					{
						result = ']';
						currState = RIGHT_SQUARE_BRACKET;
						break;
					}

					case '(':
					{
						result = '(';
						currState = LEFT_PARENTHESIS;
						break;
					}

					case ')':
					{
						result = ')';
						currState = RIGHT_PARENTHESIS;
						break;
					}

					case '!':
					{
						if (nextCh == '=')
						{
							result = "!=";
							currState = NOT_EQUAL;
							i++;
						}
						else
						{
							result = "!";
							currState = LOGICAL_NEGATION;
						}
						break;
					}

					case '&':
					{
						if (nextCh == '&')
						{
							result = "&&";
							currState = LOGICAL_AND;
							i++;
						}
						break;
					}

					case '|':
					{
						if (nextCh == '|')
						{
							result = "||";
							currState = LOGICAL_OR;
							i++;
						}
						break;
					}

					case '#':
					{
						int position = i + 1;
						getline(fileForWork, str);
						numLine++;
						i = 0;
						result = '#';
						currState = ONE_LINE_COMMENT;
						cout << "(" << numLine-1 << "," << position << ") " << info.at(currState) << " " << result << endl;

						break;
					}

					case '%':
					{
						currState = ERROR;
						int numLineOut = numLine;
						i++;
						int position = i;

						ch = str[i];
						for (auto j = i; j < str.size(); j++)
						{
							ch = str[j];
							i = j;
							if (ch == '%')
							{
								currState = MULTILINE_COMMENT;
								break;
							}
						}
						while (ch != '%')
						{
							getline(fileForWork, str);
							numLine++;
							i = 0;
							for (auto j = i; j < str.size(); j++)
							{
								ch = str[j];
								i = j;
								if (ch == '%')
								{
									currState = MULTILINE_COMMENT;
									break;
								}									
							}
							if (fileForWork.eof())
								ch = '%';
						}
						if (currState == MULTILINE_COMMENT)
						{
							result = "%some text%";
							cout << "(" << numLineOut << "," << position << ") - (" << numLine << "," << i << ") " << info.at(currState) << " " << result << endl;
						}
						else 
						{
							cout << "(" << numLineOut << "," << position << ")-";
							errorText = "Comment not closed";
						}
						break;
					}

					case '"':
					{
						currState = ERROR;
						int numLineOut = numLine;
						i++;
						int position = i;
						ch = str[i];
						result = '"';
						for (auto j = i; j < str.size(); j++)
						{
							ch = str[j];
							result += ch;
							i = j;
							if (ch == '"')
							{
								currState = STRING;
								break;
							}
						}
						while (ch != '"')
						{
							result += "\n";
							getline(fileForWork, str);
							numLine++;
							i = 0;
							for (auto j = i; j < str.size(); j++)
							{
								ch = str[j];
								result += ch;
								i = j;
								if (ch == '"')
								{
									currState = STRING;
									break;
								}
							}

							if (fileForWork.eof())
								ch = '"';
						}
						if (currState == STRING)
							cout << "(" << numLineOut << "," << position << ") - (" << numLine << "," << i+1 << ") " << info.at(currState) << " " << result << endl;
						else
						{
							cout << "(" << numLineOut << "," << position << ")-";
							errorText = "String not closed";
						}
						break;
					}
				
					default:
						currState = START;
						break;
				}
							
				i++;

				if ((currState != START) && (currState != MULTILINE_COMMENT) && (currState!= ONE_LINE_COMMENT) && (currState != STRING) && (currState != IDENTIFICATOR) && (currState != ERROR))
					cout << "(" << numLine << "," << i << ") " << info.at(currState) << " " << result << endl;
				if (currState == ERROR)
					cout << "(" << numLine << "," << i << ") " << info.at(currState) << " " << errorText << endl;
			}
		}
	cout << "end of file" << endl;
	fileForWork.close();
}