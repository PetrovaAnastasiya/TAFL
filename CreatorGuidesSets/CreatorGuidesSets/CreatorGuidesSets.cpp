#include "GrammarEnum.h"
#include "FileWork.h"

int main()
{
	GrammarEnum ge;
	Grammar gr;
	int size = 0;
	gr = ge.AlgorythmFactorize(gr);
	do 
	{
		size = gr.getSize();
		gr = ge.AlgorythmFactorize(gr);
	} while (size != gr.getSize());
	gr.PrintGrammar("output.txt");
}