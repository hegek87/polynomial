#ifndef POLY_H
#define POLY_H
#include <iostream>
#include <vector>

class Polynomial{
	private:
		int degree;
		std::vector<double> coeffs;
	public:
		Polynomial();
		Polynomial(std::vector<double>, int);
		~Polynomial();
		Polynomial(const Polynomial&);
		
		Polynomial operator+(const Polynomial&);
		Polynomial operator*(const Polynomial&);
		//Polynomial operator/(const Polynomial&);
		Polynomial syntheticDiv(double);
		
		std::vector<double> solve();
		std::vector<double> solveLinear();
		std::vector<double> solveQuadratic();
		std::vector<double> solveCubic();
		std::vector<double> solveQuartic();
		
		Polynomial derivative();
		
		double newtonRaphson(double);
		double evaluate(double);
		
		int getDegree() const;
		const std::vector<double> getCoeffs() const;
		bool zero();
		
		bool equals(const Polynomial&);
		
		void print();
		
		friend std::ostream& operator<<(std::ostream&,const Polynomial&);
};
#endif
		
		
