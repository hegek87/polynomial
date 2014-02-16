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

TEST(SyntheticDivision){
	std::vector<double> v1,v2,v3;
	v1.push_back(-1),v1.push_back(1);
	v2.push_back(1),v2.push_back(5),v2.push_back(4),v2.push_back(10);
	v3.push_back(1),v3.push_back(1);
	Polynomial p1(v1,1),p2(v2,3),p3(v3,1);
	CHECK((p1*p2).syntheticDiv(1).equals(p2));
	CHECK((p1*p3).syntheticDiv(1).equals(p3));
	CHECK((p2*p3).syntheticDiv(-1).equals(p2));
}

TEST(CheckZero){
	std::vector<double> v1(10,0),v2(5,0),v3,v4;
	v3.push_back(1);
	v4.push_back(0),v4.push_back(0),v4.push_back(0),v4.push_back(25);
	Polynomial p1(v1,9),p2(v2,4),p3(v3,0),p4(v4,3);
	CHECK(p1.zero());
	CHECK(p2.zero());
	CHECK(!p3.zero());
	CHECK(!p4.zero());
}

TEST(SolveLinear){
	std::vector<double> v1,v2,v3,v4;
	v1.push_back(1),v1.push_back(10);
	v2.push_back(-50),v2.push_back(10);
	v3.push_back(-13),v3.push_back(100);
	v4.push_back(1.0986),v4.push_back(139.1434);
	
	Polynomial p1(v1,1),p2(v2,1),p3(v3,1),p4(v4,1);
	CHECK_CLOSE(-(1.0/10.0),p1.solveLinear()[0],0.01);
	CHECK_CLOSE(5,p2.solveLinear()[0],0.01);
	CHECK_CLOSE(13.0/100.0,p3.solveLinear()[0],0.01);
	CHECK_CLOSE(-(1.0986/139.1434),p4.solveLinear()[0],0.01);
}

TEST(SolveQuadratic){
	std::vector<double> v1,v2,v3,v4,v5,v6,v7,v8;
	v1.push_back(2),v1.push_back(1);
	v2.push_back(4),v2.push_back(2);
	
	v3.push_back(5),v3.push_back(1);
	v4.push_back(10),v4.push_back(5);
	
	v5.push_back(4.8),v5.push_back(1);
	v6.push_back(8.12),v6.push_back(12);
	
	v7.push_back(12),v7.push_back(1);
	v8.push_back(16),v8.push_back(4);
	
	Polynomial p1(v1,1),p2(v2,1),p3(v3,1),p4(v4,1);
	Polynomial p5(v5,1),p6(v6,1),p7(v7,1),p8(v8,1);
	
	CHECK_CLOSE(p1.solveLinear()[0],(p1*p2).solveQuadratic()[0],0.01);
	CHECK_CLOSE(p2.solveLinear()[0],(p1*p2).solveQuadratic()[0],0.01);
}

TEST(Derivative){
	std::vector<double> v1,v2,v3,v4;
	v1.push_back(1);
	v2.push_back(1),v2.push_back(5);
	v3.push_back(0),v3.push_back(0),v3.push_back(2),v3.push_back(4);
	v4.push_back(0),v4.push_back(1),v4.push_back(0),v4.push_back(2);
	
	Polynomial p1(v1,0),p2(v2,1),p3(v3,3),p4(v4,3);
	
	std::vector<double> e1,e2,e3,e4;
	e1.push_back(0);
	e2.push_back(5);
	e3.push_back(0),e3.push_back(4),e3.push_back(12);
	e4.push_back(1),e4.push_back(0),e4.push_back(6);
	Polynomial q1(e1,0),q2(e2,0),q3(e3,2),q4(e4,2);
	
	CHECK(p1.derivative().equals(q1));
	CHECK(p2.derivative().equals(q2));
	CHECK(p3.derivative().equals(q3));
	CHECK(p4.derivative().equals(q4));
}

TEST(Evaluate){
	std::vector<double> v1,v2,v3,v4;
	v1.push_back(10);
	v2.push_back(1),v2.push_back(3);
	v3.push_back(0),v3.push_back(0),v3.push_back(5);
	v4.push_back(1),v4.push_back(0),v4.push_back(3),v4.push_back(2);
	
	Polynomial p1(v1,0),p2(v2,1),p3(v3,2),p4(v4,3);
	
	CHECK_CLOSE(10,p1.evaluate(5),0.01);
	CHECK_CLOSE(10,p1.evaluate(1000),0.01);
	CHECK_CLOSE(19,p2.evaluate(6),0.01);
	CHECK_CLOSE(301,p2.evaluate(100),0.01);
	CHECK_CLOSE(11.2,p2.evaluate(3.4),0.01);
	CHECK_CLOSE(125,p3.evaluate(5),0.01);
	CHECK_CLOSE(245,p3.evaluate(7),0.01);
	CHECK_CLOSE(500,p3.evaluate(10),0.01);
	CHECK_CLOSE(29,p4.evaluate(2),0.01);
	CHECK_CLOSE(82,p4.evaluate(3),0.01);
}

TEST(NewtonRaphson){
	std::vector<double> v1,v2,v3,v4;
	v1.push_back(-10),v1.push_back(1);
	v2.push_back(-4),v2.push_back(0),v2.push_back(1);
	v3.push_back(-8),v3.push_back(0),v3.push_back(0),v3.push_back(1);
	v4.push_back(-8),v4.push_back(-2),v4.push_back(1);
	
	Polynomial p1(v1,1),p2(v2,2),p3(v3,3),p4(v4,2);
	
	CHECK_CLOSE(10,p1.newtonRaphson(1.0),0.01);
	CHECK_CLOSE(2,p2.newtonRaphson(1.0),0.01);
	CHECK_CLOSE(2,p3.newtonRaphson(1.0),0.01);
	CHECK_CLOSE(4,p4.newtonRaphson(1.0),0.01);
	// (x^2-2x-8)=(x-4)(x+2)
}

int main(void){
	return UnitTest::RunAllTests();
}
