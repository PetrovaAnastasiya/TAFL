#include "GrammarEnum.h"
#include "FileWork.h"

int main()
{
	GrammarEnum ge;
	Grammar gr;
	int size = 0;
	int step = 0;
	gr = ge.AlgorythmFactorize(gr, step);
	do 
	{
		step++;
		size = gr.getSize();
		gr = ge.AlgorythmFactorize(gr, step);
	} while (size != gr.getSize());
	gr.PrintGrammar("output.txt");
}