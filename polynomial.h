#ifndef POLY_H
#define POLY_H
#include <iostream>

class Polynomial{
	private:
		int degree;
		double *coeffs;
	public:
		Polynomial();
		Polynomial(double *, int);
		~Polynomial();
		Polynomial(const Polynomial&);
		
		Polynomial operator+(const Polynomial&);
		Polynomial operator*(const Polynomial&);
		//Polynomial operator/(const Polynomial&);
		Polynomial syntheticDiv(double);
		
		double *solve();
		double *solveLinear();
		double *solveQuadratic();
		double *solveCubic();
		double *solveQuartic();
		
		Polynomial derivative();
		
		double newtonRaphson(double);
		double evaluate(double);
		
		int getDegree() const;
		double *getCoeffs() const;
		bool zero();
		
		void print();
		
		friend std::ostream& operator<<(std::ostream&,const Polynomial&);
};
#endif
		
		
