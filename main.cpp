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
#include <cstdio>
#include <string>

//#include "exprtk.hpp"
using namespace std;


int main(){
//	cout<< stod(s);
//	const char *vinit[] = {"X", "Y", "Z","W"};
//	vector<string> s(vinit, end(vinit));;
//	vector<double> val{1.0,1.0,0.0,0.0};
//	expression e("@(X,Y,Z,W) X+Y+Z*W");
//	term t(s,val,"X+Y+Z*W");
//	cout << t.evalVal()<<endl;
//	e.SetVariables(s, val);
//	string s1="bo[2]bog[1]bob[0.1,0.2,0.3]DODO[0.2,0.3]A[]B[]X[0.1,0.3,0.4,0.8]",s2="bobobob[x,y,z]";
//	paraString ps1(s1),st;//,ps2(s2);
//	cout<< ps1.numOfAtomParaString();
//	st=ps1.SubParaString(3,5);
//	unsigned int a=2;
//	vector<variable> vs=ps1.GetVariablesWithValues(ps2, ps1);
//	cout <<  <<endl ;
//	paraString p("A[0.25,Xb]BAG[c,1]");
//	predecessor p1;
//	double x= 1.5;
//	variable v(s,x);
//	vector <variable> Vs(p.GetVariables());
//	p.SetTemplate("X2(a,b,c,d,e)");
////	expression e;
//////	v.SetName(s);
//////	v.SetValue(x);
//	cout << p.GetNumOfVars() << endl;
//	word w("G[x,y]<A[x,r]B[]>W[y,q]:@{x,y} x+y<=3#@{t,j} t*j>=8#@{z} z=1->K[@x x^2#@{r,y} r-y]U[@{q} sin(q)]W[]");
//	word w1("A->B");
//	word w2("A[x]->A[@x x+1]");
//	word w3("D<A>C:@w w==8->B");
//	successor s("A[@{x} x+2+x^2,@{y} 3*y]E[@j sin(j)]");
	LSYS L("AXIOM: P[0.01,0.002]J[0.01,0.002,0.004]ABC endAXIOM;"
			"WORDS: J[a,b,c]<A>B->B;"
//			"c[x,y]->g[@{x,y}x*y];"
			"B->C;"
			"C->A;"
			"H<AB>C->Q;"
			"endWORDS;"
			"IGNORE: @=-+;:'{}*&אבג endIGNORE;");
	size_t t_i;
	t_i=32;
	cout<<L.GetNewWord(&t_i) << endl;
	return 0;
}
