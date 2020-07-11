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
	

	Expression outExp;
	for (size_t i = 0; i < gr.getSize(); i++)
	{
		outExp = gr.getExpression(i);
		outExp.Insert();
		gr.setExpression(i, outExp);
	}
	gr.PrintGrammar("output.txt");

	gr.PrintGrammarWithSeparator(gr);
}