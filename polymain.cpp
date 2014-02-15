#include "polynomial.h"
#include <iostream>
#include <stdio.h>
#include <UnitTest++/UnitTest++.h>

TEST(NullConstructor){
	Polynomial p;
	CHECK_CLOSE(0, p.getDegree(), 0.01);
	CHECK_CLOSE(0, p.getCoeffs()[0], 0.01);
}

TEST(Addition){
	std::vector<double> p1,p2,p3;
	p1.push_back(1),p1.push_back(4),p1.push_back(10);
	p2.push_back(10),p2.push_back(12),p2.push_back(0),p2.push_back(15);
	p3.push_back(1),p3.push_back(5),p3.push_back(8),p3.push_back(0);
	p3.push_back(5);
	
	Polynomial pl1(p1,3),pl2(p2,4),pl3(p3,5);
	
	std::vector<double> v1,v2,v3;
	v1.push_back(12),v1.push_back(21),v1.push_back(18),v1.push_back(15);
	v1.push_back(5);
	Polynomial vo1(v1,5);
	
	v2.push_back(11),v2.push_back(16),v2.push_back(10),v2.push_back(15);
	Polynomial vo2(v2,4);
	
	v3.push_back(2),v3.push_back(9),v3.push_back(18),v3.push_back(0);
	v3.push_back(5);
	
	Polynomial vo3(v3,5);
	
	CHECK((pl1+pl2+pl3).equals(vo1));
	CHECK((pl1+pl2).equals(vo2));
	CHECK((pl1+pl3).equals(vo3));
}

TEST(Multiplication){
	std::vector<double> v1,v2,v3;
	v1.push_back(1),v1.push_back(5);
	v2.push_back(3),v2.push_back(10);
	v3.push_back(2),v3.push_back(1),v3.push_back(5);
	Polynomial p1(v1,1),p2(v2,1),p3(v3,2);
	
	std::vector<double> a1,a2,a3;
	a1.push_back(3),a1.push_back(25),a1.push_back(50);
	a2.push_back(6),a2.push_back(23),a2.push_back(25),a2.push_back(50);
	a3.push_back(6),a3.push_back(53),a3.push_back(140),a3.push_back(175);
	a3.push_back(250);
	Polynomial al1(a1,2),al2(a2,3),al3(a3,4);
	
	CHECK((p1*p2).equals(al1));
	CHECK((p2*p3).equals(al2));
	CHECK((p1*p2*p3).equals(al3));
}

int main(void){
	return UnitTest::RunAllTests();
}
