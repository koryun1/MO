#pragma once
#include<vector>

#include "method.h"

class Fibonacci :public Method
{
public:
	Fibonacci(double a, double b, std::function<double(double)> func,
		double eps = 0.01, double delt = 0.1) : Method(a, b, func, delt, eps)
	{

		F.push_back(1);
		F.push_back(1);
	}

	void compute() override
	{
		size_t N = find_N();
		double fd;
		fd = static_cast<double>(F[N - 1]) / static_cast<double>(F[N]);
		double fib_coef = (m_b - m_a)*fd;

		double x = m_b - fib_coef;
		double y = m_a + fib_coef;
		double Qx = m_func_r1(x);
		double Qy = m_func_r1(y);
		m_counter++;
		for (size_t i = 1; i < N - 2; i++)
		{
			m_counter++;
			if (Qx < Qy)
			{
				m_b = y;
				y = x;
				Qy = Qx;
				fd = static_cast<double>(F[N - i - 2]) / static_cast<double>(F[N - i]);
				x = y - (y - m_a)*fd;
				Qx = m_func_r1(x);
			}
			else
			{
				m_a = x;
				x = y;
				Qx = Qy;
				fd = static_cast<double>(F[N - i - 2]) / static_cast<double>(F[N - i]);
				y = x + (m_b - x)*fd;
				Qy = m_func_r1(y);
			}
			//std::cout << "interval =[" << m_a << "," << m_b << "] " << "interval length = " << (m_b - m_a) << std::endl;
		}

		m_counter++;
		if (Qx < Qy)
		{
			m_b = y;
			y = x;
			Qy = Qx;
			x = y - m_eps;
			Qx = m_func_r1(x);
		}
		else
		{
			m_a = x;
			x = y;
			Qx = Qy;
			y = x + m_eps;
			Qy = m_func_r1(y);
		}
		//std::cout << "interval =[" << m_a << "," << m_b << "] " << "interval length = " << (m_b - m_a) << std::endl;
		if (Qx < Qy)
		{
			m_b = y;
		}
		else {
			m_a = x;
		}
		//std::cout << "interval =[" << m_a << "," << m_b << "] " << "interval length = " << (m_b - m_a) << std::endl;
	}

private:
	int find_N()
	{
		int i = 0;
		double d = (m_b - m_a);
		if (d / F[i] + m_eps <= m_delt) { return i; }
		i++;
		while (d / F[i] + m_eps > m_delt)
		{
			i++;
			F.push_back(F[i - 1] + F[i - 2]);
		}
		return i;
	}

	std::vector<size_t> F;
};

