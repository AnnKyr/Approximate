#pragma once
#define OUT
#include <vector>
#include <string>
#include <functional>

enum class op_type
{
	param, sum, dif, prod, div, pow, sin, cos, tan, cot, log, lgn, num
};

class expression_tree
{
	
	struct operation
	{
		std::vector<operation*> operands;
		std::function<double(const std::vector<operation*>&)> func;
		double get();
		void add(operation*);
	};

	static double param (const std::vector<operation*>&);
	static double sum   (const std::vector<operation*>&);
	static double dif   (const std::vector<operation*>&);
	static double prod  (const std::vector<operation*>&);
	static double div   (const std::vector<operation*>&);
	static double pow   (const std::vector<operation*>&);
	static double sin   (const std::vector<operation*>&);
	static double cos   (const std::vector<operation*>&);
	static double tan   (const std::vector<operation*>&);
	static double cot   (const std::vector<operation*>&);
	static double log   (const std::vector<operation*>&);
	static double lgn   (const std::vector<operation*>&);
	

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
	static std::function<double(const std::vector<operation*>&)> operations[12];
	op_type get_func_type(const std::string& token);
};