/*
 * main.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: gips
 */
#include <stdio.h>
#include "LSYS_PARA.h"


int main(){
	string s="A(()())B((()())())";

//	string s="A(@{x,y}x*y,@{z}z^2):0.5,[B(@{x,y}x+y,@{z}z-3)+C(@{x,y}x-y,@{z}1/z)]:0.25,G(@{q}sin(q)):0.25";
//	size_t x=CloseLoc(s, ',',0);
//	successorsSpace pS(s);
//	char c=')';
//	size_t CL=s.rfind(c);
//	cout<< CL <<endl;
//	size_t OL=CloseLoc(s, c, CL);
//	cout<< OL <<endl;
//	cout<< s.substr(OL,CL) <<endl;
		string L_st=file2string("../LSYS_EXPRTK_STO/models/model1_9.txt");
	LSYS L(L_st);
	L.propagate();
	cout<<L.current<< endl;
	L.propagate();
	cout<<L.current<< endl;
	L.propagate();
	cout<<L.current<< endl;
	L.propagate();
	cout<<L.current<< endl;
//	unsigned int n=50;
//	L.simulate(n);
//	cout<<L.current<< endl;
	return 0;
}
