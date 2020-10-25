/*
 * main.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: gips
 */
#include <stdio.h>
#include <chrono>
//#include <muParser.h>
#include "LSYS_PARA.h"
#include <iostream>
using namespace std;
//using namespace mu;

int main(){

	string s="bobo",s1="b";
	paraString p("A(Xa,Xb)BAG(c,Sf)");
	double x= 1.5;
	variable v(s,x);
	vector <variable> Vs(p.GetVariables());
	p.SetTemplate("X2(a,b,c,d,e)");
//	expression e;
////	v.SetName(s);
////	v.SetValue(x);
	cout << p.GetNumOfVars() << endl;
//	return 0;
}
