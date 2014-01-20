#include "polynomial.h"
#include <iostream>
#include <stdio.h>

int main(void){
/*
	double temp[4] = {48848.8,-1828.8,-132.6,1};
	Polynomial p(temp, 3);
	p.print();
	double *x = p.solveCubic();
	double y = p.newtonRaphson(1.0);
	std::cout << "ROOT: ";
	std::cout << y << std::endl;
	std::cout << p.evaluate(y) << std::endl;
	
	double t1[2]={-*x,1},t2[2]={-*(x+1),1},t3[2]={-*(x+2),1};
	Polynomial p1(t1,1),p2(t2,1),p3(t3,1);
	p1.print();
	p2.print();
	p3.print();
	Polynomial p4 = p1*p2*p3;
	p4.print();*/

	double temp[5] = {644804,24708.6,-3579.12,-119.4,1};
	Polynomial p(temp, 4);
	double *res = p.solveQuartic();
	p.print();
	printf("Root 1: %f, Root 2: %f, Root 3: %f, Root 4: %f\n", 
		*res,*(res+1),*(res+2),*(res+3));
	double t1[2]={-*res,1},t2[2]={-*(res+1),1},t3[2]={-*(res+2),1};
	double t4[2]={-*(res+3),1};
	Polynomial p1(t1,1),p2(t2,1),p3(t3,1),p4(t4,1);
	Polynomial p5 = p1*p2*p3*p4;
	p1.print(); p2.print(); p3.print(); p4.print();
	p5.print();
	
	return 0;
}
