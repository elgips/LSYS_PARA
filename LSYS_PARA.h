/*
 * LSYS_PARA.h
 *
 *  Created on: Oct 13, 2020
 *      Author: Ela'd Gips
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <cstdio>
#include "exprtk.hpp"

using namespace std;

#ifndef LSYS_PARA_H_
#define LSYS_PARA_H_

typedef exprtk::symbol_table<double> symbol_table_d;
typedef exprtk::expression<double>     expression_d;
typedef exprtk::parser<double>             parser_d;

size_t findNth(string s1,string s2,unsigned int i);
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

class expression{
protected:

	vector	<variable>	variables;
	string				equation;
	//	symbol_table_d SymTab;
	//	expression_d expression_e;

	//
public:
	//	parser_d 						parser_e;
	//						expression(expression e);
	expression	();
	expression 	(string s);
	expression	(vector <variable> Variables,string tmplt);
	expression(vector <string> Names,vector <double> values,string tmplt);
	//	void				ParseTemplate();
	void 				SetVariables(vector <variable> Variables);
	void 				SetVariables(vector <string> Names,vector <double> values);
	string 				GetExpression();
	//	bool 				boolevalVal();
	//	double				evalVal();
	//	bool	CheckVariablesFormat(vector <variable> Variables);
	//
	//	void 	SetTemplet	(string tmplt);

};
typedef expression	term;

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
	int					numOfAtomParaString();// done, CHECKED
	string 				GetTemplate		();
	string				GetNumOfVars	();
	string				GetNamesClean	();
	vector	<variable>	GetVariables	();
	vector 	<variable> 	GetVariablesWithValues(paraString pSymb,paraString pNum);//done, checked
	paraString			SubParaString(int t_i,int t_e);//D&C
	void				SetTemplate	(string	tmplt);
	void				SetVariables(vector <variable> Variables);
	bool				Parafit(paraString pS);//done, checked
	void 				resetParaString(string s);
};
class successor{/*the evolution of that sub string in the current step*/
protected:
	string					Input;
	string 					Template;
	string					numOfExp;
	string					namesClean;
	vector	<expression>	expressions;
public:
	successor();
	successor(string tmplt);
	vector <expression>		GetExpressions();
	string					GetCleanNames();
	string					GetExpNums();
	string					GetTemplate();

	//	successor(string tmplt,vector	<expression> SucVars);
	//	successor(string tmplt,vector	<expression> SucVars,vector <variable> Variables);

};
typedef paraString predecessor;/*a Parastring - a substring at the previous step*/
typedef predecessor sideConLeft;/*a string which is a left side condition for a certain evolution*/
typedef predecessor sideConRight;/*a string which is a right side condition for a certain evolution*/
class word{
public:
	string stWord;
	/*SCL<pred>SCR:@(var1,var2...)term1#@(var1,var2...)term2....#@(var1,var2...)termN->Successor:@(var1,var2...)sucVar1#@(var1,var2...)sucVar2#...#@(var1,var2...)sucVarM;*/
	predecessor				p;
	successor				s;
	sideConLeft				l;
	sideConRight			r;
	vector	<expression>	t;
	word();
	word(string StWord);
	//	word(sideConLeft L,successor S,predecessor P,sideConRight R);
	////
	void ParseTerms(string S);
};
class LSYS{
public:
	/*WORDS:
	 * word1;
	 * word2;
	 * .
	 * .
	 * .
	 * word_n;
	 *
	 * AXIOM:
	 * axiom..;
	 *
	 * {not obligatory}
	 * CONSTANTS:
	 * C1=..;
	 * C2=...;
	 * C3=...;
	 * dt=...;
	 * endCONSTANTS
	 * GLOBALVARIABLES:
	 * A=F1(...) */
	symbol_table_d 		SymTab;
	expression_d 		expression_e;
	parser_d			parser_e;

	string 				axiom;
	string 				current;
//	paraString			p;
	string 				ignore;
	vector	<word> 		words;
	vector	<string>	history;
	vector	<variable>	GlobalParameters;
	vector	<variable>	GlobalVaribles;
	vector	<expression>	GlobalVariblesPropagators;
	LSYS(string s);
	////	//	~LSYS();
	string ignoreIt(string s);
	////	bool leftCon(string oldword,size_t t,sideConLeft left);
	////	bool rightCon(string oldword,size_t t,sideConRight right);
	int 	propagate();
	int		simulate(unsigned int n);
	string 	GetNewWord(size_t* t_i);
	string 	GetPnumfromPtempRev(string LTemplate,size_t t);
	string 	ParsSuccessor(successor s);
	void	ParseGP(string s);
	void	ParseGV(string s);
	void 	Gpropagate();
	void 	LoadGlob();
};
#endif /* LSYS_PARA_H_ */
