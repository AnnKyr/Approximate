#include <iostream>
#include <cmath>
#include <string>
#include "ExpressionParser.h"
#include "Differentiate.h"
#include "Integration.h"

int main()
{
	std::string str1 = "log(sin(2*x)+cos(3*x)^3,sqr(x))/(5+4)";
	std::string str = "lgn(cot (x^3) +  1 ) ";
	//std::cin >> str;
	expression_tree* tree = new expression_tree(str, 'x');
	std::cout << tree->calculate(1) << "\n";
	std::cout << calculate(0, 1, str);
}