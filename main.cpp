/*
 * main.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: gips
 */
#include <stdio.h>
#include "LSYS_PARA.h"


int main(){
	string L_st=file2string("../LSYS_EXPRTK_STO/apex.txt");
	LSYS L(L_st);
	L.propagate();
	cout<<L.current<< endl;
	L.propagate();
	cout<<L.current<< endl;
	L.propagate();
	cout<<L.current<< endl;
	unsigned int n=50;
	L.simulate(n);
	cout<<L.current<< endl;
	return 0;
}
