#include <cmath>
#include <string>
#include <stdio.h>
#include "polynomial.h"

Polynomial::Polynomial(){
	degree = 0;
	coeffs = new double[1];
	coeffs[0] = 0;
}

Polynomial::Polynomial(double *poly, int degree){
	this->degree = degree;
	coeffs = new double[degree+1];
	for(int i = 0; i < degree+1; ++i){
		coeffs[i] = poly[i];
	}
}

Polynomial::~Polynomial(){
	delete[] coeffs;
}

Polynomial::Polynomial(const Polynomial& poly){
	degree = poly.degree;
	coeffs = poly.coeffs;
}
	
Polynomial Polynomial::operator+(const Polynomial& poly){
	int maxDegree = (degree > poly.degree) ? degree : poly.degree;
	double *temp = new double[maxDegree+1];
	for(int i = 0; i < maxDegree+1; ++i){
		temp[i] = coeffs[i] + poly.coeffs[i];
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
	double temp[divDegree+1];
	for(int i = 0; i < divDegree+1; ++i){ temp[i] = 0; }
	temp[divDegree] = this->coeffs[this->degree];
	std::cout << temp[divDegree] << std::endl;
	for(int i = divDegree-1; i >= 0; --i){
		temp[i] = (root*temp[i+1]) + this->coeffs[i+1];
	}
	return Polynomial(temp, divDegree);
}
/*
Polynomial Polynomial::operator/(const Polynomial& poly){
	// poly / this
	int divDegree = this->degree - poly.degree;
}
*/
	
Polynomial Polynomial::operator*(const Polynomial& poly){ 
	const int prodDegree = degree + poly.degree;
	double temp[prodDegree+1];
	//initialize to zero
	for(int i = 0; i < prodDegree+1; ++i){ temp[i] = 0; }
	for(int i = 0; i < degree+1; ++i){
		for(int j = 0; j < poly.degree+1; ++j){
			double t = coeffs[i] * poly.coeffs[j];
			temp[i+j] += t;
		}
	}
	return Polynomial(temp, prodDegree);
}
	
double *Polynomial::solve(){ return 0;}

bool Polynomial::zero(){
	for(int i = 0; i < this->degree+1; ++i){
		if(this->coeffs[i] != 0){
			return false;
		}
	}
	return true;
}

// Assuming degree == 1. It is really important that the
// return value of this function is delete[]'d after being
// called.
double *Polynomial::solveLinear(){
	if(coeffs[1] == 0){ return NULL; }
	double *x = new double[1];
	x[0] = -coeffs[0] / coeffs[1];
	return x;
}

// Assuming degree == 2. We must call delete[] on the return
// value of this function after it is no longer needed.
double *Polynomial::solveQuadratic(){
	if(coeffs[2] == 0){ return solveLinear(); }
	double a = coeffs[2], b = coeffs[1], c = coeffs[0];
	double d = b*b - 4*a*c;
	if(d < 0){ return NULL; }
	if(!d){
		double *x = new double[1];
		*x = -b / (2*a);
		return x;
	}
	double *x = new double[2];
	*x = (-b + sqrt(d))/ (2*a);
	*(x+1) = (-b - sqrt(d))/ (2*a);
	return x;
}
	
	
double *Polynomial::solveCubic(){
	if(coeffs[3] == 0){
		return solveQuadratic();
	}
	if(coeffs[1] == 0 && coeffs[2] == 0){
		double *x = new double[1];
		*x = cbrt(-coeffs[0] / coeffs[3]);
		return x;
	}
	if(coeffs[0] == 0){
		double temp[3] = {coeffs[1], coeffs[2], coeffs[3]};
		Polynomial p(temp, 2);
		double *x = p.solveQuadratic();
		double *y = new double[3];
		*y = 0, *(y+1) = *x, *(y+2) = *(x+1);
		return y;
	}
	double a = coeffs[3], b = coeffs[2], c = coeffs[1], d = coeffs[0];
	double k, p, q;
	if(b != 0){
		k = -b / (3*a);
		p = (3*a*c-b*b)/(-3*a*a);
		q = (2*b*b*b-9*a*b*c+27*a*a*d)/(-27*a*a*a);
}

int Polynomial::getDegree() const{ return degree; }
double *Polynomial::getCoeffs() const{ return coeffs; }

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
		
//std::ostream& Polynomial::operator<<(std::ostream& os, const Polynomial& p){}

int main(void){
	double temp[4] = {24, -2, -5, 1};
	Polynomial p(temp, 3);
	p.print();
	double *x = p.solveCubic();
	for(int i = 0; i < 3; ++i){
		std::cout << "Root ";
		std::cout << i+1;
		std::cout << ": ";
		std::cout << *x;
		std::cout << ", ";
	}
	std::cout << std::endl;
/*
	double temp[3] = {-4, 0, 1};
	Polynomial p(temp, 2);
	//p.print();
	double temp2[2] = {-2,1};
	Polynomial p2(temp2, 1);
	//p2.print();
	
	Polynomial p3 = p/p2;*/
/*
	double temp[2] = {1,2};
	double temp2[3] = {2,-3, 0};
	Polynomial p1(temp, 1);
	p1.print();

	double *solSet = p1.solveLinear();
	std::cout << *solSet << std::endl;
	delete[] solSet;

	Polynomial p2(temp2, 2);
	p2.print();
	
	Polynomial p3 = p1*p2;
	p3.print();
	
	double t3[3] = {6,-5,1};
	Polynomial p4(t3, 2);
	double *ans = p4.solveQuadratic();
	std::cout<<"Root 1: "<<*ans<<", Root 2: "<<*(ans+1)<<std::endl;
	delete[] ans;
	*/
	return 0;
}
