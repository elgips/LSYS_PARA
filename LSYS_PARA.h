/*
 * MyClass.h
 *
 *  Created on: Oct 13, 2020
 *      Author: gips
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
//#include <muParser.h>
using namespace std;

#ifndef LSYS_PARA_H_
#define LSYS_PARA_H_

class variable{
public:
	string name;
	double value;
	variable		();
	variable		(string Name);
	variable		(string Name,double Value);

	void 	SetValue(double Name);
	void	SetName	(string Value);

	double 	GetValue();
	string 	GetName();

};

//class expression{
//protected:
//
//	vector	<variable>	variables;
//	string				Template;
//	mu	::	Parser 		p;
//
//public:
//			expression	();
//			expression	(string tmplt);
//			expression	(vector <variable> Variables,string tmplt);
//
//	void 	SetVariables(vector <variable> Variables);
//	void 	ParseVariables();
//	void 	SetTemplet	(string tmplt);

//};
//
//class term:expression{
//public:
//
//	bool evalVal();
//
//};
//
//class sucVar:expression{
//
//public:
//
//	double evalVal();
//
//};
//
class paraString{
protected:
	string				Input;
	string				Template;
	string				numOfVars;
	string				namesClean;
	vector	<variable>	variables;
	void ParseTemplate();
	string ignoreIt(string s,string ignore);

public:
	paraString();
	paraString(string tmplt);
//	paraString(string tmplt,vector <variable> Variables);

	string 				GetTemplate		();
	string				GetNumOfVars	();
	string				GetNamesClean	();
	vector	<variable>	GetVariables	();

	void	SetTemplate	(string	tmplt);
	void	SetVariables(vector <variable> Variables);


};
//class predecessor:paraString{
//protected:
//
//	vector	<term>	terms;
//
//public:
//
//	predecessor();
//	predecessor(string tmplt,vector	<term>	Terms);
//	predecessor(string tmplt,vector	<term>	Terms,vector <variable> Variables);
//};
//class successor:paraString{
//protected:
//
//	vector	<sucVar> sucVars;
//
//public:
//
//	successor();
//	successor(string tmplt,vector	<sucVar> SucVars);
//	successor(string tmplt,vector	<sucVar> SucVars,vector <variable> Variables);
//
//};
////typedef paraString predecessor;/*a Parastring - a substring at the previous step*/
////typedef paraString successor;/*the evolution of that sub string in the current step*/
//typedef predecessor sideConLeft;/*a string which is a left side condition for a certain evolution*/
//typedef predecessor sideConRight;/*a string which is a right side condition for a certain evolution*/
//class word{
//public:
//	string stWord;
//	predecessor p;
//	successor s;
//	sideConLeft l;
//	sideConRight r;
//	word();
//	word(string StWord);
//	word(sideConLeft L,successor S,predecessor P,sideConRight R);
//};
//class LSYS{
//public:
//	string axiom;
//	string ignore;
//	vector<word> words;
//	vector<string> history;
//	int timestep;
//	LSYS(string s);
//	//	~LSYS();
//	string ignoreIt(string s);
//	bool leftCon(string oldword,size_t t,sideConLeft left);
//	bool rightCon(string oldword,size_t t,sideConRight right);
//	int propagate();
//};
#endif /* LSYSCON2S_H_ */
