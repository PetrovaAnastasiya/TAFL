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
	ONE_LINE_COMMENT,
	MULTILINE_COMMENT
};

map<state, const char* > info = {
	{START, "START"},
	//{INT, "INT"},
	//{DOUBLE, "DOUBLE"},
	//{VOID, "VOID"},
	//{VAR, "VAR"},
	//{STRING, "STRING"},
	//{BOOL, "BOOL"},
	//{CHAR, "CHAR"},
	//{IF, "IF"},
	//{ELSE, "ELSE"},
	//{WHILE, "WHILE"},
	//{FOR, "FOR"},
	//{READ, "READ"},
	//{WRITE, "WRITE"},
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
	//{ERROR, "ERROR"},
	{LOGICAL_NEGATION, "LOGICAL_NEGATION"}
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
				switch (ch)
				{
				case '+':
					result = '+';
					currState = PLUS;
					break;

				case '-':
					result = '-';
					currState = MINUS;
					break;

				case '*':
					result = '*';
					currState = MULTIPLICATION;
					break;

				case '/':
					result = '/';
					currState = DIVISION;
					break;

				case '^':
					result = '^';
					currState = EXP;
					break;

				case '.':
					result = '.';
					currState = DOT;
					break;

				case ',':
					result = ',';
					currState = COMMA;
					break;

				case ':':
					result = ':';
					currState = COLON;
					break;

				case ';':
					result = ';';
					currState = SEMI_COLON;
					break;

				case '=':
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

				case '<':
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

				case '>':
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
	
				case '{':
					result = '{';
					currState = LEFT_CURLY_BRACE;
					break;

				case '}':
					result = '}';
					currState = RIGHT_CURLY_BRACE;
					break;

				case '[':
					result = '[';
					currState = LEFT_SQUARE_BRACKET;
					break;

				case ']':
					result = ']';
					currState = RIGHT_SQUARE_BRACKET;
					break;

				case '(':
					result = '(';
					currState = LEFT_PARENTHESIS;
					break;

				case ')':
					result = ')';
					currState = RIGHT_PARENTHESIS;
					break;

				case '!':
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

				case '#':
					getline(fileForWork, str);
					numLine++;
					i = 0;
					result = '#';
					currState = ONE_LINE_COMMENT;
					break;

				case '%':
					int numLineOut;
					numLineOut = numLine;
					int position;
					position = i;
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
					cout << "(" << numLineOut << "," << position << ") - (" << numLine << "," << i << ") "<< result << " " << info.at(currState) << endl;

					break;

				default:
					currState = START;
					break;
				}

				i++;

				if ((currState != START) && (currState != MULTILINE_COMMENT))
					cout << "(" << numLine << "," << i << ") " << result << " " << info.at(currState) << endl;
			}
		}
	fileForWork.close();
}