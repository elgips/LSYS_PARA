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
//	LSYS L("AXIOM: A[0.5] endAXIOM;"
//			"WORDS: J[a,b,c]<A[d]B[e]>C:@{a,c}a+c>0.001#@{b}b^2<5->B[@{a} sqrt(a+1)]J[@{b}b^2#@{c}cos(c^2)#@{a}a^2];"
////			"c[x,y]->g[@{x,y}x*y];"
//			"A[x]->A[@{x} x+0.1]B[@{x} x];"
//			"A[z]B[x]B[y]->C[@{x,y,z}z*sin(y+x)];"
//			"H<AB>C->Q;"
//			"endWORDS;"
//			"IGNORE: @=-+;:'{}*&אבג endIGNORE;");
		LSYS L("AXIOM: B[-1]AF endAXIOM;"
				"WORDS: A->AB[1];"
				"F->FF;"
				"FF->FFF;"
//				"c[x,y]->g[@{x,y}x*y];"
				"AB[x]->AB[@{x}x+1+t]A;"
				"B[x]A->B[@{x}x+t]AC[@{x} x+dt];"
				"C[x]:@{x} x>=1->Q[@{x} x^2];"
				"Q[x]:@{x} x>3-> -LEAF-;"//A[z]B[x]B[y]->C[@{x,y,z}z*sin(y+x)];"
//				"H<AB>C->Q;"
				"endWORDS;"
				"IGNORE: @=+-;:'{}*&אבג endIGNORE;"
				"GPARAMETERS:"
				"t0=0.1;"
				"dt=0.5;"
				"g=9.81;"
				"r=1.45;"
				"endGPARAMETERS;"
				"GVARIABLES:"
				"t=0:@{t,dt} t+dt;"
				"AS=0.123:@{AS,t,r} AS+t*r;"
				"endGVARIABLES;");
//	size_t t_i;
//	t_i=35;
	L.propagate();
	cout<<L.current<< endl;
	L.propagate();
	cout<<L.current<< endl;
	L.propagate();
	cout<<L.current<< endl;
	unsigned int n=10;
	L.simulate(n);
	cout<<L.current<< endl;
//	L.propagate();
//	cout<<L.current<< endl;
//	L.propagate();
//	cout<<L.current<< endl;
//	L.propagate();
//	cout<<L.current<< endl;
//	L.propagate();
//	cout<<L.current<< endl;
//	L.propagate();
//	cout<<L.current<< endl;
//	L.propagate();
//	cout<<L.current<< endl;
//	L.propagate();
//	cout<<L.current<< endl;
	return 0;
}
