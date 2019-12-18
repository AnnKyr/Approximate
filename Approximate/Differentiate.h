#pragma once
#include <string>
#include "ExpressionParser.h"

double colculate(std::string token, double x0, double dx)
{
	double a, b;

	expression_tree* func = new expression_tree(token);
	a = func->calculate(x0 - dx);
	b = func->calculate(x0 + dx);
	
	return ((b-a) / (2*dx));
}