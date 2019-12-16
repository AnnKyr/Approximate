#pragma once
#include <vector>
#include <string>


std::string input_processed;

class expression_tree
{
	struct operation;

	struct op_type_base 
	{
		virtual double execute(operation* ...args) = 0;
	};

	struct op_type_sum : op_type_base 
	{
		double execute(operation* ...args) override;
	};

	struct op_type_prod : op_type_base
	{
		double execute(operation* ...args) override;
	};

	struct op_type_trig : op_type_base 
	{
		virtual double execute(operation* arg) override;
	};

	struct op_type_sin : op_type_trig
	{
		double execute(operation* arg) override;
	};

	struct operation
	{
		std::vector<operation*> operands;
		//op_type op;
		double get();
		void add(operation*);
	};

public:
	expression_tree(std::string input);
	double calculate(double);
private:
	operation* parse_subexpr(int a);
	std::string parse_token(int& a);
	bool is_terminator(char);
	double param_value;
	std::string expression;
	operation* root;
	
};