#pragma once
#define OUT
#include <vector>
#include <string>


std::string input_processed;

enum class op_type
{
	param, sum, prod, pow, sin, cos, tan, cot, log, ln
};

class expression_tree
{
	
	struct operation
	{
		std::vector<operation*> operands;
		double (*func) (const std::vector<operation*>&) = nullptr;
		double get();
		void add(operation*);
	};

	typedef double FUNC (const std::vector<operation*>&);

	static double param (const std::vector<operation*>&);
	static double sum   (const std::vector<operation*>&);
	static double prod  (const std::vector<operation*>&);
	static double pow   (const std::vector<operation*>&);
	static double sin   (const std::vector<operation*>&);
	static double cos   (const std::vector<operation*>&);
	static double tan   (const std::vector<operation*>&);
	static double cot   (const std::vector<operation*>&);
	static double log   (const std::vector<operation*>&);
	static double ln    (const std::vector<operation*>&);

public:
	expression_tree(std::string input);
	double calculate(double);
private:
	char param_name;
	operation* parse_subexpr(std::string token);
	void preprocess(std::string& token);
	std::string parse_token(const std::string& str, int& a);
	bool is_terminator(char);
	void parse_func(std::string token, OUT operation*);
	static double param_value;
	std::string expression;
	operation* root;
	static FUNC* operations[10];
};