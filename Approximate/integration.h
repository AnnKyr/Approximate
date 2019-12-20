#pragma once
#define SUM sum += 1;
double calculate(double left, double right, std::string expression, int n = 10)
{
	expression_tree* tree = new expression_tree(expression, 'x');
	double h = (right - left) / n;
	double sum = (tree->calculate(left) + tree->calculate(right)) / 2;
	double x = left + h;

	for (int i = 1; i < n; i++, x += h)
	{
		sum += tree->calculate(x);
	}

	return h * sum;
}

double calculate(double h, double* values, int n)
{
	double sum = (values[0] + values[n - 1]) / 2;

	for (int i = 1; i < n - 1; i++)
	{
		sum += values[i];
	}

	return h * sum;
}


double calculate(double left, double right, double* values, int n)
{
	return calculate((right - left) / static_cast<double>(n), values, n);
}

