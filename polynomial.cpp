#include <cmath>
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
	std::cout << "DELETING" << std::endl;
	delete coeffs;
	std::cout << "DELETED" << std::endl;
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
	
Polynomial Polynomial::operator*(const Polynomial& poly){ 
	int prodDegree = degree + poly.degree;
	double temp[prodDegree+1];
	for(int i = 0; i < degree+1; ++i){
		for(int j = 0; j < poly.degree+1; ++j){
			double t = coeffs[i] * poly.coeffs[j];
			//std::cout << t << std::endl;
			temp[i+j] += t;
			//std::cout << "IN t "<<temp[i+j]<<std::endl;
		}
	}
	//delete temp;
	return Polynomial(temp, prodDegree);
}
	
double *Polynomial::solve(){ return 0;}
//Assume that degree == 1
double *Polynomial::solveLinear(){
	if(coeffs[1] == 0){ return NULL; }
	double *x = new double[1];
	*x = -coeffs[0] / coeffs[1];
	return x;
}

// Assuming degree == 2
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
		double temp[3] = {coeffs[1], coeffs[2], coeffs[3]);
		Polynomial p(temp, 2);
		double *x = p.solveQuadratic();
		double *y = new double[3];
		*y = 0, *(y+1) = *x, *(y+2) = *(x+1);
		return y;
	}
	double a = coeffs[3], b = coeffs[2], c = coeffs[1], d = coeffs[0];
	double p = -b / (3*a), q = (p*p*p)+((b*c-3*a*d)/(6*a*a));
	double r = c / (3*a);
	double *x = new double[2];
	*x = cbrt(q + sqrt(q*q+((r-p*p)*(r-p*p)*(r-p*p))));
	*x += cbrt(q-sqrt(q*q+((r-p*p)*(r-p*p)*(r-p*p))));
	*x -= p;
	*(x+1) = 1;
	//now divide our by (z-*x) and solve the remaining quadratic equation
	Polynomial sol(x, 1);
	Polynomial quad = this / sol;
	double *y = solveQuadratic(quad);
	double *retval = new double[3];
	*retval = *x, *(retval+1) = *y, *(retval+2) = *(y+1);
	return retval;
}

int Polynomial::getDegree() const{ return degree; }
double *Polynomial::getCoeffs() const{ return coeffs; }
		
//std::ostream& Polynomial::operator<<(std::ostream& os, const Polynomial& p){}

int main(void){
	double temp[2] = {1,2};
	double temp2[2] = {2,3};
	Polynomial p1(temp, 1);
	std::cout << *p1.solveLinear() << std::endl;
	Polynomial p2(temp2, 1);
	Polynomial p3 = p1*p2;
	std::cout << "Polynomial is of degree: " << p3.getDegree() << std::endl;
	double *data = p3.getCoeffs();
	for(int i = 0; i < p3.getDegree()+1; ++i){
		std::cout << *(data+i) << " ";
	}
	std::cout <<std::endl;
	
	double t3[3] = {6,-5,1};
	Polynomial p4(t3, 2);
	double *ans = p4.solveQuadratic();
	std::cout << "Root 1: " << *ans << ", Root 2: " << *(ans+1) << std::endl;
/*
	double temp[6] = {1,2,3,4,5,6};
	Polynomial p = Polynomial(temp, 5);
	Polynomial p2 = Polynomial(temp, 5);
	Polynomial p3 = p + p2;
	std::cout << "Polynomial is of degree: " << p3.getDegree() << std::endl;
	double *data = p3.getCoeffs();
	for(int i = 0; i < p3.getDegree()+1; ++i){
		std::cout << *(data+i) << " ";
	}
	std::cout << std::endl;
	*/
	/*
	double temp2[4] = {2,3,4,1};
	Polynomial p2 = Polynomial(temp2, 3);
	std::cout << "Polynomial is of degree: " << p.getDegree() << std::endl;
	double *data = p.getCoeffs();
	for(int i = 0; i < p.getDegree()+1; ++i){
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "Polynomial is of degree: " << p2.getDegree() << std::endl;
	data = p2.getCoeffs();
	for(int i = 0; i < p2.getDegree()+1; ++i){
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	
	Polynomial p3 = p+p2;
	std::cout << "Polynomial is of degree: " << p3.getDegree() << std::endl;
	data = p3.getCoeffs();
	for(int i = 0; i < p3.getDegree()+1; ++i){
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	*/
	return 0;
}
