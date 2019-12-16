#pragma once
#define SUM sum += 1;
double calculate(double left, double right, double (*func)(double), int n = 10) 
{
	double h = (right - left) / n;
	double sum = (func(left) + func(right)) / 2;

	for (int i = 1, double x = left+h; i < n; i++, x += h) 
	{
		sum += func(x);
	}

	return h * sum;
}

double calculate(double left, double right, double* values, int n) 
{
	return calculate((right - left) / n, values, n);
}

double calculate(double h, double* values, int n)
{
	double sum = (values[0] + values[n-1]) / 2;

	for (int i = 1; i < n - 1; i++) 
	{
		sum += values[i];
	}

	return h * sum;
}