#pragma once
#define OUT
#include <vector>
#include <string>
#include <functional>

enum class op_type
{
	param, sum, dif, prod, div, pow, sin, cos, tan, cot, log, lgn, num
};

op_type operator++(op_type& t) { return t = (op_type)(static_cast<int>(t) + 1); };

class expression_tree
{

	

	struct operation
	{
		std::pair<operation*, operation*> op;
		std::function<double(const  std::pair<operation*, operation*>)> func;
		double get();
		void add(operation*);
	};

	using operands = std::pair<operation*, operation*>;

	static double param (const operands&);
	static double sum   (const operands&);
	static double dif   (const operands&);
	static double prod  (const operands&);
	static double div   (const operands&);
	static double pow   (const operands&);
	static double sin   (const operands&);
	static double cos   (const operands&);
	static double tan   (const operands&);
	static double cot   (const operands&);
	static double log   (const operands&);
	static double lgn   (const operands&);
	

public:
	expression_tree(std::string input, char param = 'x');
	double calculate(double);
private:
	char param_name;
	operation* parse_subexpr(std::string token);
	void preprocess(std::string& token);
	std::string parse_token(const std::string& str, int& a);
	bool is_terminator(char);
	void parse_func(std::string token, OUT operation* o);
	static double param_value;
	std::string expression;
	operation* root;
	static char st[12];
	static std::function<double(const operands&)> operations[12];
	op_type get_func_type(const std::string& token);
};