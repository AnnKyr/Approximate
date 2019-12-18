#include <iostream>
#include <cmath>
#include <string>
#include "ExpressionParser.h"
#include "Differentiate.h"
#include "Integration.h"

int main() 
{
	std::string str = "x^2";
	//std::cin >> str;
	expression_tree* tree = new expression_tree(str, 'x');
	std::cout << tree->calculate(2);
}