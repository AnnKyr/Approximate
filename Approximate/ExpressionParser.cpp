#include "ExpressionParser.h"
#include <stack>
#include <cmath>

expression_tree::FUNC* expression_tree::operations[10] { param, sum, prod, pow, sin, cos, tan, cot, log, ln };
double expression_tree::param_value;

void expression_tree::preprocess(std::string& token)
{	
	int i = token.size() - 1;
	std::string prev_token = parse_token(token, i);
	while (i > 0)
	{
		std::string current_token = parse_token(token, i);
		if (current_token == "-")
		{
			prev_token = "(-1)*" + prev_token;
			current_token = "+";
		}
	}
}

std::string expression_tree::parse_token(const std::string& str, int& a)
{
	std::string token;

	if (str[a] == ')')
	{
		std::stack<bool> s;
		s.push(true);

		while (!s.empty())
		{
			token.push_back(str[a]);
			if (str[a] == '(') s.pop();
			else if (str[a] == ')') s.push(true);
		}
	}

	while (true)
	{
		token.push_back(str[a]);
		if (a == 0 || is_terminator(str[a]) || is_terminator(str[a - 1])) { a++;  break; }
		a++;
	}

	return token;
}

bool expression_tree::is_terminator(char c)
{
	return (c == '+' || c == '*' || c == '^' || c == ',');
}

double expression_tree::param(const std::vector<operation*>&)
{
	return param_value;
}

double expression_tree::sum(const std::vector<operation*>& n)
{
	double result = 0;
	for (auto&& t : n) result += t->get();
	return result;
}

double expression_tree::prod(const std::vector<operation*>& n)
{
	double result = 0;
	for (auto&& t : n) result *= t->get();
	return result;
}

double expression_tree::pow(const std::vector<operation*>& n)
{
	if (n.size() != 2) throw;
	return std::pow(n[0]->get(), n[1]->get());
}

double expression_tree::sin(const std::vector<operation*>& n)
{
	if (n.size() != 1) throw;
	return std::sin(n[0]->get());
}

double expression_tree::cos(const std::vector<operation*>& n)
{
	if (n.size() != 1) throw;
	return std::cos(n[0]->get());
}

double expression_tree::tan(const std::vector<operation*>& n)
{
	if (n.size() != 1) throw;
	return std::tan(n[0]->get());
}

double expression_tree::cot(const std::vector<operation*>& n)
{
	if (n.size() != 1) throw;
	return 1 / std::tan(n[0]->get());
}

double expression_tree::log(const std::vector<operation*>& n)
{
	if (n.size() != 2) throw;
	return std::log(n[0]->get()) / std::log(n[1]->get());
}

double expression_tree::ln(const std::vector<operation*>& n)
{
	if (n.size() != 1) throw;
	return std::log(n[0]->get());
}
