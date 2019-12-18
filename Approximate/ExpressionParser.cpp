#include "ExpressionParser.h"
#include <stack>
#include <cmath>

std::function<double(const std::vector<expression_tree::operation*>&)> expression_tree::operations[10] 
{ 
	param, sum, prod, pow, sin, cos, tan, cot, log, lgn 
};

double expression_tree::param_value;

expression_tree::expression_tree(std::string input)
{
	root = parse_subexpr(input);
}

double expression_tree::calculate(double x)
{
	expression_tree::param_value = x;
	return root->get();
}

expression_tree::operation* expression_tree::parse_subexpr(std::string token)
{
	expression_tree::operation* p = new expression_tree::operation();
	bool found = 0;
	preprocess(token);
	int i = token.size() - 1, j = i - 1;
	while(j>=0)
	{
		if (token[j] == '+') 
		{ 
			p->add(parse_subexpr(token.substr(j + 1, i - j)));
			i = j - 1; 
			j = i; 
			found = 1;
		}
		parse_token(token, j);
	}
	if (found)
	{
		p->add(parse_subexpr(token.substr(j + 1, i - j)));
		p->func = expression_tree::operations[static_cast<int>(op_type::sum)];
		return p;
	} 

	found = 0;
	i = token.size() - 1, j = i - 1;

	while (j >= 0)
	{
		if (token[j] == '*')
		{
			p->add(parse_subexpr(token.substr(j + 1, i - j)));
			i = j - 1;
			j = i;
			found = 1;
		}
		parse_token(token, j);
	}
	if (found)
	{
		p->add(parse_subexpr(token.substr(j + 1, i - j)));
		p->func = expression_tree::operations[static_cast<int>(op_type::prod)];
		return p;
	}


	parse_func(token, p);
	return p;
}


void expression_tree::preprocess(std::string& token)
{	
	
	std::string new_str;

	if (token.front() == '(' && token.back() == ')')
	{
		token.pop_back();
		token.erase(0, 1);
	}

	if (token == "-1") return;

	int i = token.size() - 1;
	std::string prev_token = parse_token(token, i);
	
	while (i >= 0)
	{
		std::string current_token = parse_token(token, i);
		if (current_token == "-")
		{
			new_str.insert(0, prev_token);
			if (i == -1) { new_str.insert(0, "(-1)*"); }
			else { new_str.insert(0, "+(-1)*"); }
			
		}
		else if (current_token == "/")
		{
			new_str.insert(0, prev_token);
			new_str.insert(0, ",-1)");
			new_str.insert(0, parse_token(token, i));
			new_str.insert(0, "*pow(" );
		} 
		else if (current_token == "^")
		{
			new_str.insert(0, ")");
			new_str.insert(0, prev_token);
			new_str.insert(0, ",");
			new_str.insert(0, parse_token(token, i));
			new_str.insert(0, "pow(");
		}
		else
		{
			new_str.insert(0, prev_token);
		}
		prev_token = parse_token(token, i);
	}

	new_str.insert(0, prev_token);
	
	token = new_str;
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
			a--;
		}
	}

	while (true)
	{
		token.push_back(str[a]);
		if (a == 0 || is_terminator(str[a]) || is_terminator(str[a - 1])) { a--;  break; }
		a--;
	}

	return token;
}

bool expression_tree::is_terminator(char c)
{
	return (c == '+' || c == '*' || c == '^' || c == ',');
}

void expression_tree::parse_func(std::string token, OUT operation* o)
{
	if (token.size() == 1 && token[0] == param_name)
	{
		o->func = expression_tree::operations[static_cast<int>(op_type::param)];
		return;
	}

	op_type type = get_func_type(token.substr(0, 3));

	if (token.size() < 6 || type == op_type::num)
	{
		double a = std::stod(token);
		o->func = [a](const std::vector<expression_tree::operation*>&) { return a; };
		return;
	}

	o->func = expression_tree::operations[static_cast<int>(type)];

	int i = token.size() - 2;
	int j = i - 1;

	while (j >= 4)
	{
		if (token[j] == ',')
		{
			o->add(parse_subexpr(token.substr(j + 1, i - j)));
			i = j - 1;
			j = i;
		}
		parse_token(token, j);
	}

	o->add(parse_subexpr(token.substr(j + 1, i - j)));

}

op_type expression_tree::get_func_type(const std::string& token)
{
	if (token == "pow")	return op_type::pow;
	if (token == "sin")	return op_type::sin;
	if (token == "cos")	return op_type::cos;
	if (token == "tan")	return op_type::tan;
	if (token == "cot")	return op_type::cot;
	if (token == "log")	return op_type::log;
	if (token == "lgn")	return op_type::lgn;
	return op_type::num;
}

double expression_tree::param(const std::vector<expression_tree::operation*>&)
{
	return param_value;
}

double expression_tree::sum(const std::vector<expression_tree::operation*>& n)
{
	double result = 0;
	for (auto&& t : n) result += t->get();
	return result;
}

double expression_tree::prod(const std::vector<expression_tree::operation*>& n)
{
	double result = 0;
	for (auto&& t : n) result *= t->get();
	return result;
}

double expression_tree::pow(const std::vector<expression_tree::operation*>& n)
{
	if (n.size() != 2) throw;
	return std::pow(n[0]->get(), n[1]->get());
}

double expression_tree::sin(const std::vector<expression_tree::operation*>& n)
{
	if (n.size() != 1) throw;
	return std::sin(n[0]->get());
}

double expression_tree::cos(const std::vector<expression_tree::operation*>& n)
{
	if (n.size() != 1) throw;
	return std::cos(n[0]->get());
}

double expression_tree::tan(const std::vector<expression_tree::operation*>& n)
{
	if (n.size() != 1) throw;
	return std::tan(n[0]->get());
}

double expression_tree::cot(const std::vector<expression_tree::operation*>& n)
{
	if (n.size() != 1) throw;
	return 1 / std::tan(n[0]->get());
}

double expression_tree::log(const std::vector<expression_tree::operation*>& n)
{
	if (n.size() != 2) throw;
	return std::log(n[0]->get()) / std::log(n[1]->get());
}

double expression_tree::lgn(const std::vector<expression_tree::operation*>& n)
{
	if (n.size() != 1) throw;
	return std::log(n[0]->get());
}

double expression_tree::operation::get()
{
	return func(operands);
}

void expression_tree::operation::add(expression_tree::operation* o)
{
	operands.push_back(o);
}
