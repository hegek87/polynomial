#include <cmath>
#include <string>
#include <stdio.h>
#include "polynomial.h"

Polynomial::Polynomial() : degree(0), coeffs(1,0) {}

Polynomial::Polynomial(std::vector<double> coeffs, int degree):
	degree(degree), 
	coeffs(coeffs) {}

		
Polynomial Polynomial::operator+(const Polynomial& poly){
	int maxDegree = (degree > poly.degree) ? degree : poly.degree;
	std::vector<double> temp;
	for(int i = 0; i < maxDegree+1; ++i){
		temp.push_back(coeffs[i] + poly.coeffs[i]);
	}
	return Polynomial(temp, maxDegree);
}
/* 
*  Only handles the case where poly evenly divides this. That
*  is poly = (this) * h(x) for some polynomial h of degree
*  poly.degree - this->degree. Uses synthetic division
*/
Polynomial Polynomial::syntheticDiv(double root){
	int divDegree = this->degree - 1;
	std::vector<double> temp(divDegree+1,0);
	temp[divDegree] = this->coeffs[this->degree];
	for(int i = divDegree-1; i >= 0; --i){
		temp[i] = (root*temp[i+1]) + this->coeffs[i+1];
	}
	return Polynomial(temp, divDegree);
}
	
Polynomial Polynomial::operator*(const Polynomial& poly){ 
	const int prodDegree = degree + poly.degree;
	std::vector<double> temp(prodDegree+1,0);
	//initialize to zero
	for(int i = 0; i < degree+1; ++i){
		for(int j = 0; j < poly.degree+1; ++j){
			double t = coeffs[i] * poly.coeffs[j];
			temp[i+j] += t;
		}
	}
	return Polynomial(temp, prodDegree);
}
	
std::vector<double> Polynomial::solve(){ 
	if(this->degree == 1){ return this->solveLinear(); }
	else if(this->degree == 2){ return this->solveQuadratic(); }
	//else if(this->degree == 3){ return this->solveCubic(); }
	//else if(this->degree == 4){ return this->solveQuartic(); }
	else{
		/* this->degree > 4 not implemented yet */
		return std::vector<double>(1,0);
	}
}

bool Polynomial::zero(){
	for(int i = 0; i < this->degree+1; ++i){
		if(this->coeffs[i] != 0){
			return false;
		}
	}
	return true;
}

// Degree == 1
std::vector<double> Polynomial::solveLinear(){
	if(coeffs[1] == 0){ return std::vector<double>(); }
	return std::vector<double>(1, -coeffs[0]/coeffs[1]);
}

// Assuming degree == 2. 
std::vector<double> Polynomial::solveQuadratic(){
	if(coeffs[2] == 0){ return solveLinear(); }
	double a = coeffs[2], b = coeffs[1], c = coeffs[0];
	double d = b*b - 4*a*c;
	if(d < 0){ return std::vector<double>(); }
	if(!d){
		return std::vector<double>(1, -b/(2*a));
	}
	double solSet[] = { (-b+sqrt(d))/(2*a), (-b-sqrt(d))/(2*a) };
	return std::vector<double>(solSet, solSet+(2*sizeof(double)));
}

// degree == 3
std::vector<double> Polynomial::solveCubic(){
	if(coeffs[3] == 0){
		return solveQuadratic();
	}
	if(coeffs[1] == 0 && coeffs[2] == 0){
		return std::vector<double>(1,cbrt(-coeffs[0]/coeffs[3]));
	}
	if(coeffs[0] == 0){
		std::vector<double> temp;
		temp.push_back(coeffs[1]),temp.push_back(coeffs[2]);
		temp.push_back(coeffs[3]);
		Polynomial p(temp,2);
		std::vector<double> retVal = p.solveQuadratic();
		retVal.push_back(0);
		return retVal;
	}
	double firstRoot = this->newtonRaphson(1.0);
	Polynomial quad = this->syntheticDiv(firstRoot);
	std::vector<double> temp = quad.solveQuadratic();
	std::vector<double> retVal;
	retVal.push_back(temp[0]);
	retVal.push_back(temp[1]);
	retVal.push_back(firstRoot);
	return retVal;
}
/*
std::vector<double> Polynomial::solveCubic(){
        if(coeffs[3] == 0){}
        if(coeffs[1] == 0 && coeffs[2] == 0){
                return std::vector<double>(1,cbrt(-coeffs[0]/coeffs[3]));
        }
        if(coeffs[0] == 0){
        	
                double temp[3] = {coeffs[1], coeffs[2], coeffs[3]};
                Polynomial p(temp, 2);
                double *x = p.solveQuadratic();
                double *y = new double[3];
                *y = 0, *(y+1) = *x, *(y+2) = *(x+1);
                return y;
        }
        double firstRoot = this->newtonRaphson(1.0);
        Polynomial quad = this->syntheticDiv(firstRoot);
        double *x = quad.solveQuadratic();
        double *retval = new double[3];
        retval[0] = firstRoot, retval[1] = *x, retval[2] = *(x+1);
        return retval;
}*/
/*
double *Polynomial::solveQuartic(){
	double firstRoot = this->newtonRaphson(1.0);
	Polynomial cubic = this->syntheticDiv(firstRoot);
	double *x = cubic.solveCubic();
	double *retval = new double[4];
	retval[0] = firstRoot, retval[1] = *x, retval[2] = *(x+1);
	retval[3] = *(x+2);
	return retval;
}*/

Polynomial Polynomial::derivative(){
	int derivDegree = (this->degree == 0) ? 0 : this->degree-1;
	std::vector<double> temp(derivDegree+1,0);
	for(int i = 0; i < derivDegree+1; ++i){
		temp[i] = (i+1)*this->coeffs[i+1];
	}
	return Polynomial(temp, derivDegree);
}

double Polynomial::newtonRaphson(double guess){
	Polynomial deriv = this->derivative();
	double nextGuess = guess;
	double fVal = this->evaluate(nextGuess);
	while(std::abs(fVal) > .000000001){
		if(0 == deriv.evaluate(nextGuess)){ nextGuess += 1; }
		nextGuess -= (fVal)/(deriv.evaluate(nextGuess));
		fVal = this->evaluate(nextGuess);
	}
	return nextGuess;
}

double Polynomial::evaluate(double val){
	double temp = this->coeffs[0];
	for(int i = 1; i < this->degree+1; ++i){
		temp += this->coeffs[i] * pow(val, i);
	}
	return temp;
}


int Polynomial::getDegree() const{ return degree; }
const std::vector<double> Polynomial::getCoeffs() const{ return coeffs; }

bool Polynomial::equals(const Polynomial& other){
	if(this->degree != other.degree){ return false; }
	for(int i = 0; i < this->degree; ++i){
		if(std::abs(this->coeffs[i]-other.coeffs[i]) > 0.01){
			return false;
		}
	}
	return true;
}


void Polynomial::print(){
	std::cout << "Polynomial is of degree: " << degree << std::endl;	
	for(int i = 0; i < degree+1; ++i){
		if(coeffs[i] < 0){
			if(i == 0){
				std::cout << coeffs[i];
			}
			else{
				std::cout << " - ";
				if(coeffs[i] == -1){ std::cout << ""; }
				else{ std::cout << (-1 * coeffs[i]); }
				std::cout << "x";
				if(i == 1){ std::cout << ""; }
				else{ std::cout << "^"; std::cout << i; }
			}
		}
		else if(coeffs[i] == 0){ continue; }
		else{
			if(i == 0){ std::cout << coeffs[i]; }
			else{
				std::cout << " + ";
				if(coeffs[i] == 1){ std::cout << ""; }
				else{ std::cout << coeffs[i]; }
				std::cout << "x";
				if(i == 1){ std::cout << ""; }
				else{ std::cout << "^"; std::cout << i; }
			}
		}
	}
	std::cout << std::endl;
}
		
std::ostream& operator<<(std::ostream& os, const Polynomial& p){
	os << "Polynomial is of degree: " << p.degree << std::endl;	
	for(int i = 0; i < p.degree+1; ++i){
		if(p.coeffs[i] < 0){
			if(i == 0){
				os << p.coeffs[i];
			}
			else{
				os << " - ";
				if(p.coeffs[i] == -1){ os << ""; }
				else{ os << (-1 * p.coeffs[i]); }
				os << "x";
				if(i == 1){ os << ""; }
				else{ os << "^"; os << i; }
			}
		}
		else if(p.coeffs[i] == 0){ continue; }
		else{
			if(i == 0){ os << p.coeffs[i]; }
			else{
				os << " + ";
				if(p.coeffs[i] == 1){ os << ""; }
				else{ os << p.coeffs[i]; }
				os << "x";
				if(i == 1){ os << ""; }
				else{ os << "^"; os << i; }
			}
		}
	}
	return os;
}

