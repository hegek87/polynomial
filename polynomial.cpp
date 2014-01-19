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

Polynomial::Polynomial(int deg){
	std::cout << "CREATING" << std::endl;
	this->degree = deg;
	coeffs = new double[deg];
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
	Polynomial sum(maxDegree);
	for(int i = 0; i < maxDegree+1; ++i){
		sum.coeffs[i] = coeffs[i] + poly.coeffs[i];
	}
	return sum;
}
	
Polynomial Polynomial::operator*(const Polynomial& poly){ 
	return Polynomial();
}
	
int *Polynomial::solve(){ return 0;}
int *Polynomial::solveLinear(){ return 0;}
int *Polynomial::solveQuadratic(){return 0;}
int *Polynomial::solveCubic(){return 0;}

int Polynomial::getDegree() const{ return degree; }
double *Polynomial::getCoeffs() const{ return coeffs; }
		
//std::ostream& Polynomial::operator<<(std::ostream& os, const Polynomial& p){}

int main(void){
	double temp[6] = {1,2,3,4,5,6};
	Polynomial p = Polynomial(temp, 5);
	Polynomial p2 = Polynomial(temp, 5);
	Polynomial p3 = p + p2;
	std::cout << "Polynomial is of degree: " << p3.getDegree() << std::endl;
	double *data = p3.getCoeffs();
	for(int i = 0; i < p3.getDegree()+1; ++i){
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
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
