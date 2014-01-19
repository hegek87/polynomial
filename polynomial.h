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
		Polynomial syntheticDiv(const Polynomial&, double);
		
		double *solve();
		double *solveLinear();
		double *solveQuadratic();
		double *solveCubic();
		
		int getDegree() const;
		double *getCoeffs() const;
		bool zero();
		
		void print();
		
		//std::ostream& operator<< (std::ostream&, const Polynomial&);
};
#endif
		
		
