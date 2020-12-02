/*
 * LSYS_PARA.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: gips
 */
#include "LSYS_PARA.h"
string file2string(string dir){
	ifstream file(dir);
	string input,in_fu;
	while(file>>input){
		in_fu+=input;
	}
	return in_fu;
}
size_t findNth(string s1,string s2,unsigned int i){
	size_t firstLoc,nthLoc=0;
	string Temp=s1;
	for(unsigned int j=0;j<i;j++){
		firstLoc=Temp.find(s2);
		if(firstLoc==Temp.npos){
			invalid_argument("n exceed the string number of substring occurrences");
			return s1.npos;
		}else{
			Temp=Temp.substr(firstLoc+1);
			nthLoc+=firstLoc+1;
		}

	}
	return nthLoc-1;
}
/*Variable definition*/
variable::variable(void){
	this->name="";
	this->value=0;
}
variable::variable(string Name){
	this->name=Name;
	this->value=0;
}
variable::variable(string Name,double Value){
	this->name=Name;
	this->value=Value;
}
void variable::SetName(string Name){this->name=Name;}
void variable::SetValue(double Value){this->value=Value;}
string variable::GetName(){return this->name;}
double variable::GetValue(){return this->value;}
/*End of variable definition*/

/*Expression definition*/
expression::expression(){
	equation="";
}
expression::expression(vector <variable> Variables,string tmplt){
	this->equation=tmplt;
	variables=Variables;
}
expression::expression(vector <string> Names,vector <double> values,string tmplt){
	this->equation=tmplt;
	SetVariables(Names, values);
}
void expression::SetVariables(vector <variable> Variables){
	vector <variable> var1(Variables);
	variables=var1;
}
void expression::SetVariables(vector <string> Names,vector <double> values){
	vector<string>::iterator t1;
	vector<double>::iterator t2;
	for(t1=Names.begin(),t2=values.begin();((t1<Names.end())&&(t2<values.end()));t1++,t2++){
		variable v(*t1,*t2);
		variables.push_back(v);
	}
}
expression::expression(string s){
	size_t t_v,t_s;
	t_v=s.find("@");
	if(t_v!=s.npos){
		if(t_v!=0){
			invalid_argument("Bad expression syntax");
			terminate();
		}else{
			if(s.find("@{")==s.npos){
				variable v(s.substr(t_v+1,s.find(" ")));
				variables.push_back(v);
				equation=s.substr(s.find(" "));
			}else{
				t_s=s.find("}");
				if(t_s==s.npos){
					invalid_argument("Bad expression syntax");
					terminate();
				}
				equation=s.substr(t_s+1);
				string temp=s.substr(t_v+2,t_s-t_v-2);
				size_t t_p;
				while (!temp.empty()){
					t_p=temp.find(",");
					if(t_p!=temp.npos){
						variable v(temp.substr(0,t_p));
						variables.push_back(v);
						temp=temp.substr(t_p+1);
					}else{
						variable v(temp);
						variables.push_back(v);
						temp="";
					}

				}
			}
		}
	}else{
		equation=s;
	}


}
string expression::GetExpression(){
	return this->equation;
}
/*End of expression definition*/

/*paraString definition*/
string paraString::ignoreIt(string s,string ignore){
	for(unsigned int i=0;i<ignore.length();i++){
		s.erase(remove(s.begin(), s.end(), ignore[i]), s.end());
	}
	return s;
}
void paraString::ParseTemplate(){
	namesClean="";
	numOfVars="";
	variables.clear();
	string tempName,SubTemp=Template,varsTemp,VarName;
	size_t varCounter,i;
	size_t t1=0,t2,t3;
	int p_num=1;
	if(Template.find("[")==Template.npos){
		numOfVars="_0";
		namesClean="_"+Template;
	}else{
		while(t1<Template.length()){
			t2=SubTemp.find("[");
			if(t2==SubTemp.npos){
				namesClean+="_";
				namesClean+=SubTemp;
				t1=Template.npos;
			}else{
				namesClean+="_";
				namesClean+=SubTemp.substr(0,t2);
				t3=SubTemp.find("]");
				varCounter=0;
				if (t2+1<t3){
					varsTemp=SubTemp.substr(t2+1,t3-t2-1);
					varCounter=1;
					i=varsTemp.find(",");
					while(i!=varsTemp.npos){
						varCounter++;
						VarName=varsTemp.substr(0,i);
						try
						{
							double value = stod(VarName);
							variable V_temp("p"+to_string(p_num++),value);
							this->variables.push_back(V_temp);
						}
						catch(std::exception& e)
						{
							variable V_temp(VarName);
							this->variables.push_back(V_temp);
						}

						varsTemp=varsTemp.substr(i+1);
						i=varsTemp.find(",");
					}
					VarName=varsTemp;
					try
					{
						double value = stod(VarName);
						variable V_temp("p"+to_string(p_num++),value);
						this->variables.push_back(V_temp);
					}
					catch(std::exception& e)
					{
						variable V_temp(VarName);
						this->variables.push_back(V_temp);
					}
				}
			}
			numOfVars+="_";
			numOfVars+=to_string(varCounter);
			varCounter=0;
			if(t1!=Template.npos)t1=t1+t3+1;
			if(t1<Template.length())SubTemp=Template.substr(t1);
		}
		if(numOfVars.empty())numOfVars="0";}
}
paraString::paraString(){
	Template="";
	numOfVars="";
	namesClean="";
}
paraString::paraString(string tmplt){
	Template=tmplt;
	namesClean="";
	numOfVars="";
	ParseTemplate();
}
string paraString::GetTemplate(){
	return Template;
}
string paraString::GetNumOfVars(){
	return numOfVars;
}
string paraString::GetNamesClean(){
	return namesClean;
}
vector <variable> paraString::GetVariables(){
	return variables;
}
void paraString::SetTemplate(string	tmplt){
	Template=tmplt;
	ParseTemplate();
}
void paraString::SetVariables(vector <variable> Variables){
	vector<variable> vars1(Variables);
	this->variables.clear();
	this->variables= vars1;
}

bool paraString::Parafit(paraString pS){// checks if a parastring format is identical to the specific parastring
	bool b1=this->numOfVars==pS.numOfVars,b2=this->namesClean==pS.namesClean;
	return b1&&b2;
}
vector <variable> paraString::GetVariablesWithValues(paraString pSymb,paraString pNum){
	vector <variable> vs,vSy=pSymb.GetVariables(),vN=pNum.GetVariables();
	vector <variable>::iterator tV1,tV2;
	if(vSy.size()==vN.size()){
		for(tV1=vSy.begin(),tV2=vN.begin();tV1!=vSy.end();tV1++,tV2++){
			variable v(tV1->name,tV2->value);
			vs.push_back(v);
		}
	}else{
		cout << "Variables doesn't fit, the program now will terminate" << endl;
		terminate();
	}

	return vs;
}

int paraString::numOfAtomParaString(){
	string s=this->namesClean;
	return count(s.begin(),s.end(), '_');
}

paraString paraString::SubParaString(int t_i,int t_e){
	/*gets location of first and last atomic Parastrings (atomic index, not char index, and returning
	 * the suitable subParastring.*/
	string firstAtom,afterLastAtom,subTemp;
	int n=numOfAtomParaString();
	if((t_i>=n)||(t_e<t_i)){
		cout << "Invalid input, the program now will terminate" << endl;
		terminate();
	}
	if (t_e==n){
		paraString psSub(Template);
		return psSub;
	}
	int n_i=findNth(namesClean, "_", t_i);
	int n_e;
	firstAtom=namesClean.substr(n_i);
	n_e=findNth(firstAtom, "_", t_i+1);
	firstAtom=firstAtom.substr(0,n_e);
	n_i=findNth(numOfVars, "_", t_i);
	n_e=findNth(numOfVars, "_", t_i+1);
	n_i=findNth(namesClean, "_", t_e+1);
	n_e=findNth(namesClean, "_", t_e+2);
	if(n_i==-1){
		subTemp=Template.substr(Template.find(firstAtom));
		paraString psSub(subTemp);
		return psSub;
	}
	if(n_e==-1){
		afterLastAtom=namesClean.substr(n_i);
		subTemp=Template.substr(Template.find(firstAtom),Template.rfind(afterLastAtom)-Template.find(firstAtom));
		paraString psSub(subTemp);
		return psSub;
	}
	afterLastAtom=namesClean.substr(n_i, n_e-n_i-1);
	subTemp=Template.substr(Template.find(firstAtom),Template.rfind(afterLastAtom)-Template.find(firstAtom));
	paraString psSub(subTemp);
	return psSub;
}

void paraString::resetParaString(string s){
	Template=s;
	namesClean="";
	numOfVars="";
	variables.clear();
	ParseTemplate();
}
/*End of paraString definition*/

/*successor definition*/
successor::successor(){
	Input="";
	Template="";
	numOfExp="";
	namesClean="";
}
successor::successor(string tmplt){
	Template=tmplt;
	namesClean="";
	numOfExp="";
	expressions.clear();
	string tempName,SubTemp=Template,varsTemp,VarName;
	size_t varCounter,i;
	size_t t1=0,t2,t3;
	if(Template.find("[")==Template.npos){
		numOfExp="_0";
		namesClean="_"+Template;
	}else{
		while(t1<Template.length()){
			t2=SubTemp.find("[");
			if(t2==SubTemp.npos){
				namesClean+="_";
				namesClean+=SubTemp;
				numOfExp+="_0";
				t1=t1+SubTemp.length();
			}else{
				namesClean+="_";
				namesClean+=SubTemp.substr(0,t2);
				t3=SubTemp.find("]");
				varCounter=0;
				if (t2+1<t3){
					varsTemp=SubTemp.substr(t2+1,t3-t2-1);
					varCounter=1;
					i=varsTemp.find("#");
					while(i!=varsTemp.npos){
						varCounter++;
						VarName=varsTemp.substr(0,i);
						expression p_temp(VarName);
						this->expressions.push_back(p_temp);
						varsTemp=varsTemp.substr(i+1);
						i=varsTemp.find("#");
					}
					VarName=varsTemp;
					expression p_temp(VarName);
					this->expressions.push_back(p_temp);
				}
				numOfExp+="_";
				numOfExp+=to_string(varCounter);
				varCounter=0;
				t1=t1+t2+t3;
				if(t1<Template.length())SubTemp=Template.substr(t1);
			}
		}
		if(numOfExp.empty())numOfExp="0";}
}

vector<expression> successor::GetExpressions(){
	return this->expressions;
}

string successor::GetCleanNames(){
	return namesClean;
}

string successor::GetExpNums(){
	return numOfExp;
}

string	successor::GetTemplate(){
	return Template;
}
/*End of successor:paraString definition*/
/*SuccessorSpace*/

successorsSpace::successorsSpace(){
}

successorsSpace::successorsSpace(string St){
	size_t dol,tp;
	string temp;
	dol=St.find("$");
	tp=St.find(":");
	if((dol==St.npos)&&(tp==St.npos)){
		s.push_back(St);
		p.push_back(1.0);
	}else{
		while(!St.empty()){

			if(dol!=St.npos){
				temp=St.substr(0,tp);
				successor sc(temp);
				s.push_back(sc);
				temp=St.substr(0,dol);
				temp=temp.substr(tp+1);
				p.push_back(stod(temp));
				St=St.substr(dol+1);
				dol=St.find("$");
				tp=St.find(":");
			}else{
				successor sc(St.substr(0,tp));
				s.push_back(sc);
				temp=St.substr(tp+1);
				p.push_back(stod(temp));
				St="";
			}
		}
	}
}

successor successorsSpace::RandomSuccessor(){
	random_device rd;
	mt19937 gen(rd());
	vector<successor>::iterator Sc=this->s.begin();
	discrete_distribution<> d(p.begin(),p.end()--);
	int sucNum=d(gen);

	for(int i=1;i<sucNum+1;i++)Sc++;

	successor suc(Sc->GetTemplate());
	return suc;

}
/*word definition */
/*L<P>R:@{var1,var2...}term1#@{var1,var2...}term2....#@(var1,var2...)termN->S1:P1$S2:P2;*/
word::word(){
	paraString L,P,R;
	successorsSpace S;
	vector <expression> t;
	this->l=L;
	this->stWord="";
	this->p=P;
	this->r=R;
	this->s=S;
}
word::word(string STWORD){
	/*SCL<pred>SCR:@(var1,var2...)term1#@(var1,var2...)term2....#@(var1,var2...)termN->Successor:@(var1,var2...)sucVar1#@(var1,var2...)sucVar2#...#@(var1,var2...)sucVarM;*/
	paraString L,P,R;
	successorsSpace S;
	vector <expression> t;
	this->l=L;
	this->stWord=STWORD;
	this->p=P;
	this->r=R;
	this->s=S;
	size_t t_p,t_l,t_r,t_t,t_e,t_i;
	string temp_s;
	t_p=STWORD.find("->");
	temp_s=STWORD.substr(0, t_p);
	t_t=temp_s.find(":");
	temp_s=temp_s.substr(0, t_t);
	// side term left
	t_l=temp_s.find("<");
	if(t_l!=temp_s.npos){
		sideConLeft temp(temp_s.substr(0,t_l));
		l=temp;
	}

	// side term right

	t_r=temp_s.find(">");
	if((t_r!=temp_s.npos)&&(t_r<t_t)){
		t_e=min(t_t,t_p);
		sideConRight temp(temp_s.substr(t_r+1,t_e-t_r-1));
		r=temp;
	}

	// predecessor

	t_e=min(t_r,min(t_t,t_p));
	t_i=(t_l+1)*(t_l!=temp_s.npos);
	predecessor temp(temp_s.substr(t_i,t_e-t_i));
	p=temp;

	//terms

	if(t_t!=temp_s.npos){
		string tempTerms=STWORD.substr(t_t+1,t_p-t_t-1);
		ParseTerms(tempTerms);
	}
	//successorSpace
	temp_s=STWORD.substr(t_p+2);
	t_t=temp_s.find(":");
	successorsSpace temp_ss(temp_s);
	s=temp_ss;

}
void word::ParseTerms(string S){
	size_t t_i;
	t_i=S.find("#");
	while(!S.empty()){
		if(t_i!=S.npos){
			expression e(S.substr(0,t_i));
			t.push_back(e);
			S=S.substr(t_i+1);
			t_i=S.find("#");
		}else{
			expression e(S);
			t.push_back(e);
			S="";
		}
	}
}


/*Debugged successfully*/

/*End of word definition*/

/*LSYS definition
WORDS:
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
 * IGNORE:;
 * {complete it afterwards:(now just a simple version)}
 * CONSTANTS:
 * C1=..;
 * C2=...;
 * C3=...;
 * dt=...;
 * GLOBAL VAIRABLES*/


LSYS::LSYS(string s){
	size_t ti,te;
	string Stword;
	s.erase(remove(s.begin(), s.end(), ' '), s.end());


	/*axiom parse*/
	ti=s.find("AXIOM:");
	if(ti==s.npos){
		cout << "system's axiom is missing" << endl;
		terminate();
	}
	Stword=s.substr(ti+6);
	te=Stword.find("endAXIOM;");
	if(te==Stword.npos){
		cout << "system's axiom end-statement is missing" << endl;
		terminate();
	}
	Stword=Stword.substr(0,te);
	axiom=Stword;
	history.push_back(axiom);
	current=axiom;
	/*WORDS PARSE*/

	ti=s.find("WORDS:");
	if(ti==s.npos){
		cout << "WARNING :THERE ARE NO WORDS DEFINED" << endl;
	}else{
		Stword=s.substr(ti+6);
		te=Stword.find("endWORDS;");
		if(te==Stword.npos){
			cout << "system's words end-statement is missing" << endl;
			terminate();
		}
		Stword=Stword.substr(0,te);
		while (!Stword.empty()){
			te=Stword.find(";");
			if(te!=Stword.npos){
				word w(Stword.substr(0, te));
				words.push_back(w);
				Stword=Stword.substr(te+1);
			}else{
				Stword="";
			}
		}

	}
	/*non-obligatories*/
	/*IGNORE*/
	ti=s.find("IGNORE:");
	if(ti==s.npos){
		cout << "WARNING :THERE IS NO IGNORE STRING DEFINED" << endl;
	}else{
		Stword=s.substr(ti+7);
		te=Stword.find("endIGNORE;");
		if(te==Stword.npos){
			cout << "system's IGNORE end-statement is missing" << endl;
			terminate();
		}
		ignore=Stword.substr(0,te);
	}
	/*PARAMETERS
	 * only Parameter name and value (to be parsed in the expressions*/
	ti=s.find("GPARAMETERS:");
	if(ti==s.npos){
		cout << "WARNING :THERE ARE NO GLOBAL PARAMETERS STRINGS DEFINED" << endl;
	}else{
		Stword=s.substr(ti+12);
		te=Stword.find("endGPARAMETERS;");
		if(te==Stword.npos){
			cout << "system's GLOBAL PARAMETERS end-statement is missing" << endl;
			terminate();
		}
		ParseGP(Stword.substr(0,te));
	}
	/*GLOBAL VARIABLES
	 * variable name, value, and propagation rule {A WORD structure for each variable} {e.g. - time, physio time. more important - get values as inputs, so the propagation rule is to stay the same unless input is given*/
	ti=s.find("GVARIABLES:");
	if(ti==s.npos){
		cout << "WARNING :THERE ARE NO GLOBAL VARIABLES STRINGS DEFINED" << endl;
	}else{
		Stword=s.substr(ti+11);
		te=Stword.find("endGVARIABLES;");
		if(te==Stword.npos){
			cout << "system's GLOBAL VARIABLES end-statement is missing" << endl;
			terminate();
		}
	}
	ParseGV(Stword.substr(0,te));
}
void LSYS::ParseGP(string s){
	this->GlobalParameters.clear();
	string val,name,temp;
	size_t eq,semicol;
	temp=s;
	semicol=temp.find(";");
	eq=temp.find("=");

	while(semicol<temp.length()-1){
		variable v(temp.substr(0,eq),stod(temp.substr(eq+1,semicol)));
		GlobalParameters.push_back(v);
		temp=temp.substr(semicol+1);
		semicol=temp.find(";");
		if(semicol==temp.npos){
			cout << "BAD SYNTEX ';' missing" << endl;
			terminate();
		}
		eq=temp.find("=");
		if(eq==temp.npos){
			cout << "BAD SYNTEX '=' missing" << endl;
			terminate();
		}
	}
	if(semicol==temp.npos){
		cout << "BAD SYNTEX ';' missing" << endl;
		terminate();
	}
	if(eq==temp.npos){
		cout << "BAD SYNTEX '=' missing" << endl;
		terminate();
	}
	variable v(temp.substr(0,eq),stod(temp.substr(eq+1,semicol)));
	GlobalParameters.push_back(v);
}

void LSYS::ParseGV(string s){
	/*A=A0:F[...];*/
	this->GlobalVaribles.clear();
	this->GlobalVariblesPropagators.clear();
	string equa,name,temp,init;
	double val;
	size_t eq,tp,semicol;
	temp=s;
	semicol=temp.find(";");
	eq=temp.find("=");
	tp=temp.find(":");

	while(semicol<temp.length()-1){
		try{
			variable v(temp.substr(0,eq),stod(temp.substr(eq+1,tp-eq-1)));
			GlobalVaribles.push_back(v);
		}
		catch(const std::invalid_argument& ia)
		{
			expression_e.release();
			SymTab.clear();
			LoadGlob();
			expression_e.register_symbol_table(SymTab);
			init=temp.substr(eq+1,tp-eq-1);
			parser_e.compile(init,expression_e);
			val=expression_e.value();
			variable v(temp.substr(0,eq),val);
			GlobalVaribles.push_back(v);
		}
		equa=temp.substr(0,semicol);
		equa=equa.substr(tp+1);
		expression e(equa);
		GlobalVariblesPropagators.push_back(e);
		temp=temp.substr(semicol+1);

		semicol=temp.find(";");
		if(semicol==temp.npos){
			cout << "BAD SYNTEX ';' missing" << endl;
			terminate();
		}
		eq=temp.find("=");
		if(eq==temp.npos){
			cout << "BAD SYNTEX '=' missing" << endl;
			terminate();
		}
		tp=temp.find(":");
		if(tp==temp.npos){
			cout << "BAD SYNTEX ':' missing" << endl;
			terminate();
		}
	}
	if(semicol==temp.npos){
		cout << "BAD SYNTEX ';' missing" << endl;
		terminate();
	}
	if(eq==temp.npos){
		cout << "BAD SYNTEX '=' missing" << endl;
		terminate();
	}
	if(tp==temp.npos){
		cout << "BAD SYNTEX ':' missing" << endl;
		terminate();
	}
	try
	{
		variable v(temp.substr(0,eq),stod(temp.substr(eq+1,tp-eq-1)));
		GlobalVaribles.push_back(v);
	}
	catch(const std::invalid_argument& ia)
	{
//		expression_e.release();
//		SymTab.clear();
		LoadGlob();
		expression_e.register_symbol_table(SymTab);
		init=temp.substr(eq+1,tp-eq-1);
		parser_e.compile(init,expression_e);
		val=expression_e.value();
		variable v(temp.substr(0,eq),val);
		GlobalVaribles.push_back(v);
	}
	equa=temp.substr(0,semicol);
	equa=equa.substr(tp+1);
	expression e(equa);
	GlobalVariblesPropagators.push_back(e);
}
void LSYS::Gpropagate(){
	string temp;
	expression_e.release();
	SymTab.clear();
	LoadGlob();

	expression_e.register_symbol_table(SymTab);
	vector<variable>::iterator v_it;
	v_it=GlobalVaribles.begin();
	for(vector<expression>::iterator e_it=GlobalVariblesPropagators.begin();e_it!=GlobalVariblesPropagators.end();e_it++){
		temp=e_it->GetExpression();
		parser_e.compile(temp,expression_e);
		v_it->SetValue(expression_e.value());
		v_it++;
	}
}

void LSYS::LoadGlob(){
	for(vector<variable>::iterator v_it=GlobalParameters.begin();v_it!=GlobalParameters.end();v_it++){
		SymTab.add_variable(v_it->name,v_it->value);
	}
	for(vector<variable>::iterator v_it=GlobalVaribles.begin();v_it!=GlobalVaribles.end();v_it++){
		SymTab.add_variable(v_it->name,v_it->value);
	}
}
string LSYS::ignoreIt(string s){
	for(unsigned int i=0;i<this->ignore.length();i++){
		s.erase(remove(s.begin(), s.end(), this->ignore[i]), s.end());
	}
	return s;
}
string LSYS::GetPnumfromPtempRev(string LTemplate,size_t t){
	string Lnum="";
	size_t Temp_t=LTemplate.length(),t_num=t,t_sym=Temp_t;
	while((t_sym>0)&&(t_num>0)){
		if(LTemplate[t_sym]==']'){
			while(current[--t_num]!='[');
			//		t_num--;
			while(LTemplate[--t_sym]!='[');
			//		t_sym--;
		}else{
			t_sym--;
			t_num--;
		}
	}
	Lnum=current.substr(t_num, t-t_num);
	return Lnum;
}
string LSYS::ParsSuccessor(successor s){
	expression_e.register_symbol_table(SymTab);
	string SucNum="";
	string SucSym=s.GetTemplate();
	vector <expression> SucExp=s.GetExpressions();
	unsigned int t;
	vector <expression>::iterator e_it;
	e_it=SucExp.begin();
	for(t=0;t<SucSym.length();t++){
		if(SucSym[t]=='['){
			SucNum+="[";
			while(SucSym[t++]!=']'){
				if(SucSym[t]=='#'){
					parser_e.compile(e_it->GetExpression(),expression_e);
					SucNum+=to_string(expression_e.value())+",";
					e_it++;
				}
				if(SucSym[t]==']'){
					if(SucSym[t-1]!='['){
						parser_e.compile(e_it->GetExpression(),expression_e);
						SucNum+=to_string(expression_e.value())+"]";
						e_it++;}
				}
			}
			t--;}else{
				SucNum+=SucSym[t];
			}
	}
	return SucNum;
}
int LSYS::propagate(){
	//propagate global variables

	/* CLEAN FROM IGNORE EXPRESSIONS*/
	string newString="";
	size_t t_i=0;
	while(t_i<current.length()){
		newString+=GetNewWord(&t_i);
	}
	history.push_back(newString);
	current=newString;
	Gpropagate();
	return 0;
}
int LSYS::simulate(unsigned int n){
	for(unsigned int i=0;i!=n;i++){
		propagate();
	}
	return 0;
}
/*remarks - to enable partial word recognition (like only B from ABC[] , *t_i is a index in the
 * old sentance and not the number of word.
 * than I generate a parastring from the partial oldSentance and try to fit a word with all cons and terms */
string LSYS::GetNewWord(size_t* t_i){
	//	/*Find index of the current old sentence substring- fr both VarNum and CleanNames format*/
	string subOldSentance=current.substr(*t_i),leftCon;
	if(ignore.find(subOldSentance[0])!=ignore.npos){
		*t_i=*t_i+1;
		return subOldSentance.substr(0, 1);
	}
	string	tempVarNums="",choTempVarNums="",tempNamesClean="",choTempNamesClean="",leftResidual,rightResidual,tempTemplate;
	string subOldSentanceIG=ignoreIt(subOldSentance);
	paraString p1;
	string p1CleanNames;
	string p1VarNums;
	string BestSuc;
	string LeftnumIG;
	word best;
	string last;
	string Leftnum;
	unsigned int lastCount;
	bool	newWordFoundFlag=false;//boolean variable for the question - do we have yet a proper non default nominee
	bool	rightSideCon,leftSideCon,unitedTermsCon;// boolean variables for the Q's: does the right side condition meets? and same for left
	vector	<word>::		iterator	w_it;
	vector	<term>::		iterator	t_it;
	vector	<variable>::	iterator	v_it;
	vector	<variable> 					vars;
	size_t iVar,iNames,iTempName,iTempVar,t0,t2,t_best_temp,tpl;
	/* for loop all the possible words fit (maximal predecessor,keeping all terms) -so we got a simple function -
	 * gets the current maximal word length(parametric, no numbers), checking if the current predecessor fits the string head, after words calls for terms checking function, than
	 * if word length is maximal, then parsing, and holding the new one as the best, untill scanning all words, across the oldSubString. returning the current location in the old string, and the new parsed word for the new string
	 */
	for(w_it=words.begin();w_it!=words.end();w_it++){
		//Check predecessor fit,and maximal size
		tempVarNums=(w_it->p).GetNumOfVars();
		tempNamesClean=(w_it->p).GetNamesClean();
		tempTemplate=w_it->p.GetTemplate();
		last=tempTemplate.back();
		lastCount=count(tempTemplate.begin(),tempTemplate.end(),last.back());
		tpl=findNth(subOldSentanceIG, last, lastCount);
		if(tpl!=subOldSentanceIG.npos){
			p1.resetParaString(subOldSentanceIG.substr(0,tpl+1));
			p1CleanNames=p1.GetNamesClean();
			p1VarNums=p1.GetNumOfVars();
			iVar=p1VarNums.find(tempVarNums);
			iNames=p1CleanNames.find(tempNamesClean);
			//double fitting - clean names and number of variables in each function, at the start of the current location
			if((iVar==0)&&(iNames==0)){
				tempTemplate=w_it->p.GetTemplate();
				last=tempTemplate.back();
				lastCount=count(tempTemplate.begin(),tempTemplate.end(),last.back());
				t0=findNth(subOldSentance, last, lastCount);
				iTempName=tempNamesClean.length();
				iTempVar=tempVarNums.length();
				// clean names length greater then the best fit so far length of clean names
				if(iTempName>choTempNamesClean.length()){
					//right and left terms met
					rightSideCon=w_it->r.GetTemplate().empty();
					if(!rightSideCon){
						tempTemplate=w_it->r.GetTemplate();
						last=tempTemplate.back();
						lastCount=count(tempTemplate.begin(),tempTemplate.end(),last.back());
						t0=t0+findNth(subOldSentance.substr(t0),last,lastCount);
						rightResidual=p1CleanNames.substr(iTempName);
						rightSideCon=(rightResidual.find((w_it->r).GetNamesClean())==0);
						rightResidual=p1VarNums.substr(iTempVar);
						if(rightResidual=="")rightResidual="_0";
						rightSideCon=rightSideCon&&(rightResidual.find((w_it->r).GetNumOfVars())==0);
					}
					leftSideCon=w_it->l.GetTemplate().empty();
					if(!leftSideCon){
						paraString pl(ignoreIt(current.substr(0,*t_i)));
						leftCon=(w_it->l).GetNamesClean();
						t2=pl.GetNamesClean().rfind(leftCon);
						leftSideCon=(t2!=leftResidual.npos)&&(t2+leftCon.length()==pl.GetNamesClean().length());
						leftCon=(w_it->l).GetNumOfVars();
						t2=pl.GetNumOfVars().rfind(leftCon);
						leftSideCon=(t2!=leftResidual.npos)&&(t2+leftCon.length()==pl.GetNumOfVars().length());
						Leftnum=GetPnumfromPtempRev(w_it->l.GetTemplate(),*t_i);
						LeftnumIG=ignoreIt(Leftnum);
					}
					if(leftSideCon&&rightSideCon){
						paraString pSy(w_it->l.GetTemplate()+w_it->p.GetTemplate()+w_it->r.GetTemplate());
						paraString pNum(Leftnum+subOldSentance.substr(0,t0+1));
						// set variables names and values
						vars=p1.GetVariablesWithValues(pSy , pNum);
						// set in math parser
						unitedTermsCon=1;
						expression_e.release();
						SymTab.clear();
						LoadGlob();
						for(v_it=vars.begin();v_it!=vars.end();v_it++){
							SymTab.add_variable(v_it->name,v_it->value);
						}
						SymTab.add_constants();
						expression_e.register_symbol_table(SymTab);
						// checking that all the terms are met
						for(t_it=w_it->t.begin();t_it!=w_it->t.end();t_it++){
							parser_e.compile(t_it->GetExpression(), expression_e);
							unitedTermsCon=unitedTermsCon&&expression_e.value();
						}
						if(unitedTermsCon){
							newWordFoundFlag=true;
							choTempNamesClean=tempNamesClean;
							choTempVarNums=tempVarNums;
							BestSuc=ParsSuccessor(w_it->s.RandomSuccessor());
							t_best_temp=t0+1;
						}
					}
				}
			}
		}
	}
	if(!newWordFoundFlag){
		*t_i=*t_i+1;
		return subOldSentance.substr(0, 1);
	}
	else{
		*t_i=*t_i+t_best_temp;
		return BestSuc;
	}
	return "-1";
}
