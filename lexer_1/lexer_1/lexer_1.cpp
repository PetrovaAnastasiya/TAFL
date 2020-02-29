#include <fstream>
#include <iostream>
#include <string>
#include <map>

using namespace std;
const string FILE_OUT_NAME = "output.txt";

enum state {
	START,
	PLUS,
	MINUS,
	MULTIPLICATION,
	DIVISION,
	EXP,
	DOT,
	COMMA,
	COLON,
	SEMI_COLON,
	SMALLER,
	MORE,
	EQUAL,
	LEFT_CURLY_BRACE,
	RIGHT_CURLY_BRACE,
	LEFT_SQUARE_BRACKET,
	RIGHT_SQUARE_BRACKET,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	COMPARISON,
	SMALLER_EQUAL,
	MORE_EQUAL,
	NOT_EQUAL,
	LOGICAL_NEGATION,
	LOGICAL_AND,
	LOGICAL_OR,
	ONE_LINE_COMMENT,
	MULTILINE_COMMENT,
	STRING,
	IDENTIFICATOR,
	ERROR,
	IF,
	ELSE,
	WHILE,
	FOR
};

map<state, const char* > info = {
	{START, "START"},
	//{INT, "INT"},
	//{DOUBLE, "DOUBLE"},
	//{VOID, "VOID"},
	//{VAR, "VAR"},
	//{STRING_TYPE, "STRING_TYPE"},
	//{BOOL, "BOOL"},
	//{CHAR, "CHAR"},
	{IF, "IF"},
	{ELSE, "ELSE"},
	{WHILE, "WHILE"},
	{FOR, "FOR"},
	//{READ, "READ"},
	//{WRITE, "WRITE"},
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
	{IDENTIFICATOR, "IDENTIFICATOR"}
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

int main()
{
	const string FILE_IN_NAME = "input.txt";
	ifstream fileForWork;
	bool is_opened = openFile(fileForWork, FILE_IN_NAME);
	int numLine = 0;
	string str, result = "";
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

				if (isalpha(ch))
				{
					result = "";
					for (auto j = i; j < str.size(); j++)
					{
						i = j;
						ch = str[i];
						if (!checkIdent(ch))
							break;
						result += ch;
					}
					cout << result << endl;
					if (result == "if")
						currState = IF;
					if (result == "else")
						currState = ELSE;
					if (result == "while")
						currState = WHILE;
					if (result == "for")
						currState = FOR;
				}

				else
				switch (ch)
				{
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
						getline(fileForWork, str);
						numLine++;
						i = 0;
						result = '#';
						currState = ONE_LINE_COMMENT;
						break;
					}

					case '%':
					{
						int numLineOut = numLine;
						int position = i;
						i++;
						ch = str[i];
						for (auto j = i; j < str.size(); j++)
						{
							ch = str[j];
							i = j;
							if (ch == '%')
								break;
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
									break;
							}
						}
						i++;
						result = "%some text%";
						currState = MULTILINE_COMMENT;
						cout << "(" << numLineOut << "," << position << ") - (" << numLine << "," << i << ") " << info.at(currState) << " " << result << endl;
						result = "";
						break;
					}

					case '"':
					{
						int numLineOut = numLine;
						int position = i;
						i++;
						ch = str[i];
						result = '"';
						for (auto j = i; j < str.size(); j++)
						{
							ch = str[j];
							result += ch;
							i = j;
							if (ch == '"')
								break;
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
									break;
							}
						}
						i++;
						currState = STRING;
						cout << "(" << numLineOut << "," << position << ") - (" << numLine << "," << i << ") " << info.at(currState) << " " << result << endl;
						break;
					}

					case '$':
					{
						i++;
						int position = i;
						result = "$";
						for (auto j = i; j < str.size(); j++)
						{
							ch = str[j];
							i = j;
							if (!checkIdent(ch))
								break;
							result += ch;
						}
						if (result.size() < 256)
						{
							currState = IDENTIFICATOR;
							cout << "(" << numLine << "," << position << ") - (" << numLine << "," << i << ") " << info.at(currState) << " " << result << endl;
						}
						else
							currState = ERROR;
						break;
					}

					default:
						

						currState = START;
										
					break;
				}
								
				i++;

				if ((currState != START) && (currState != MULTILINE_COMMENT) && (currState != STRING) && (currState != IDENTIFICATOR))
					cout << "(" << numLine << "," << i << ") " << info.at(currState) << " " << result << endl;
			}
		}
	fileForWork.close();
}