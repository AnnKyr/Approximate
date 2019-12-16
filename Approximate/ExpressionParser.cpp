#include "ExpressionParser.h"
#include <stack>

std::string expression_tree::parse_token(int& a)
{
	std::string token;

	if (expression[a] == ')')
	{
		std::stack<bool> s;
		s.push(true);

		while (!s.empty())
		{
			token.push_back(expression[a]);
			if (expression[a] == '(') s.pop();
			else if (expression[a] == ')') s.push(true);
		}
	}

	while (true)
	{
		token.push_back(expression[a]);
		if (a == 0 || is_terminator(expression[a]) || is_terminator(expression[a - 1])) { a++;  break; }
		a++;
	}

	return token;
}

bool expression_tree::is_terminator(char c)
{
	return (c == '+' || c == '*' || c == '^' || c == ',');
}
