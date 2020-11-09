/*
 * LSYS_PARA.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: gips
 */
#include "LSYS_PARA.h"
size_t findNth(string s1,string s2,unsigned int i){
	size_t firstLoc,nthLoc=0;
	string Temp=s1;
	for(unsigned int j=0;j<i;j++){
		firstLoc=Temp.find(s2);
		if(firstLoc==Temp.npos){
			invalid_argument("n exceed the string number of substring occurrences");
			return -1;
		}else{
			Temp=Temp.substr(firstLoc+1);
			nthLoc+=firstLoc+1;
		}

	}
	return nthLoc;
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
		}else{
			if(s.find("@{")==s.npos){
				variable v(s.substr(t_v+1,s.find(" ")));
				variables.push_back(v);
				equation=s.substr(s.find(" "));
			}else{
				t_s=s.find("}");
				if(t_s==s.npos){
					invalid_argument("Bad expression syntax");
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
	}

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
		namesClean=Template;
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
					//					variable V_temp(VarName);
					//					this->variables.push_back(V_temp);
					//				varsTemp=varsTemp.substr(i+1);
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
	if(pSymb.Parafit(pNum)){
		for(tV1=vSy.begin(),tV2=vN.begin();tV1!=vSy.end();tV1++,tV2++){
			variable v(tV1->name,tV2->value);
			vs.push_back(v);
		}
	}else{
		cout << "Parawords doesn't fit, the program now will terminate" << endl;
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
	int nVarFirst,nVarLast;
	int n=numOfAtomParaString();
	if((t_i>=n)||(t_e<t_i)){
		cout << "Invalid input, the program now will terminate" << endl;
		terminate();
	}
	int n_i=findNth(namesClean, "_", t_i);
	int n_e=findNth(namesClean, "_", t_i+1);
	firstAtom=namesClean.substr(n_i, n_e-n_i-1);
	n_i=findNth(numOfVars, "_", t_i);
	n_e=findNth(numOfVars, "_", t_i+1);
	nVarFirst=stoi(numOfVars.substr(n_i, n_e-n_i-1));
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
	//	n_i=findNth(numOfVars, "_", t_e);
	//	n_e=findNth(numOfVars, "_", t_e+1);
	//	nVarLast=stoi(numOfVars.substr(n_i, n_e-n_i-1));
	subTemp=Template.substr(Template.find(firstAtom),Template.rfind(afterLastAtom)-Template.find(firstAtom));
	paraString psSub(subTemp);
	//	t_i=Template.find(firstAtom);
	//	t_e=Template.find(lastAtom)+;
	return psSub;
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
					//				varsTemp=varsTemp.substr(i+1);
				}
			}
			numOfExp+="_";
			numOfExp+=to_string(varCounter);
			varCounter=0;
			t1=t1+t2+t3;
			if(t1<Template.length())SubTemp=Template.substr(t1);
		}
		if(numOfExp.empty())numOfExp="0";}
}
/*End of successor:paraString definition*/

/*word definition */
/*SCL<pred>SCR:@(var1,var2...)term1,@(var1,var2...)term2....,@(var1,var2...)termN->Successor:@(var1,var2...)sucVar1,@(var1,var2...)sucVar2,...,@(var1,var2...)sucVarM;*/
word::word(){
	paraString L,P,R;
	successor S;
	vector <expression> t;
	this->l=L;
	this->stWord="";
	this->p=P;
	this->r=R;
	this->s=S;
}
//word::word(sideConLeft L,successor S,predecessor P,sideConRight R){
//	this->l=L;
//	this-stWord="";
//	this->p=P;
//	this->r=R;
//	this->s=S;
//}
word::word(string STWORD){
	/*SCL<pred>SCR:@(var1,var2...)term1#@(var1,var2...)term2....#@(var1,var2...)termN->Successor:@(var1,var2...)sucVar1#@(var1,var2...)sucVar2#...#@(var1,var2...)sucVarM;*/
	paraString L,P,R;
	successor S;
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
	// side term left
	t_l=temp_s.find("<");
	if(t_l!=temp_s.npos){
		sideConLeft temp(temp_s.substr(0,t_l));
		l=temp;
	}

	// side term right

	t_r=temp_s.find(">");
	if(t_r!=temp_s.npos){
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

	//successor variables
	if(t_t!=temp_s.npos){
		ParseTerms(temp_s.substr(t_t+1,t_p-1-t_t));
	}
	//successor
	temp_s=STWORD.substr(t_p+2);
	t_t=temp_s.find(":");
	if(t_t==temp_s.npos){
		successor temp(temp_s);
		s=temp;
	}else{
		successor temp(temp_s.substr(0,t_t-1));
		s=temp;
	}

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
	s.erase(remove(s.begin(), s.end(), ' '), s.end());


	/*axiom parse*/
	ti=s.find("AXIOM:");
	if(ti==s.npos){
		cout << "system's axiom is missing" << endl;
		terminate();
	}
	te=(s.substr(ti)).find("endAXIOM;");
	if(te==s.npos){
		cout << "system's axiom end-statement is missing" << endl;
		terminate();
	}
	axiom=s.substr(ti+6,te-ti-6);
	history.push_back(axiom);
	current=axiom;
	/*WORDS PARSE*/
	string Stword;
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
//		cout << Stword;
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
}

string LSYS::ignoreIt(string s){
	for(unsigned int i=0;i<this->ignore.length();i++){
		s.erase(remove(s.begin(), s.end(), this->ignore[i]), s.end());
	}
	return s;
}



//int LSYS::propagate(){
//	/* CLEAN FROM IGNORE EXPRESSIONS*/
//	string oldString=*(history.end()--),newString="";
//	size_t sub_word_i=0;
//	oldString=ignoreIt(oldString);
//	paraString psOldString(oldString);
//	string TempOldStr=oldString;
//	while(i!=psOldString.GetNamesClean().npos){
//		newString+=GetNewWord(psOldString,&sub_word_i);
//	}
//	history.push_back(newString);
//	current=newString;
//	return 0;
//}
/*remarks - to enable partial word recognition (like only B from ABC[] , *t_i is a index in the
 * old sentance and not the number of word.
 * than I generate a parastring from the partial oldSentance and try to fit a word with all cons and terms */
string LSYS::GetNewWord(size_t* t_i){
	//	/*Find index of the current old sentence substring- fr both VarNum and CleanNames format*/
	string subOldSentance=current.substr(*t_i),leftCon;
	string	tempVarNums="",choTempVarNums="",tempNamesClean="",choTempNamesClean="",leftResidual,rightResidual;
	paraString p1(subOldSentance);
	string p1CleanNames=p1.GetNamesClean();
	string p1VarNums=p1.GetNumOfVars();
	word best;
	bool	newWordFoundFlag=false;//boolean variable for the question - do we have yet a proper non default nominee
	bool	rightSideCon,leftSideCon,unitedTermsCon;// boolean variables for the Q's: does the right side condition meets? and same for left
	vector	<word>::	iterator w_it;
	vector	<term>::	iterator t_it;
	size_t iVar,iNames,iTempName,iTempVar,t2;
	/* for loop all the possible words fit (maximal predecessor,keeping all terms) -so we got a simple function -
	 * gets the current maximal word length(parametric, no numbers), checking if the current predecessor fits the string head, after words calls for terms checking function, than
	 * if word length is maximal, then parsing, and holding the new one as the best, untill scanning all words, across the oldSubString. returning the current location in the old string, and the new parsed word for the new string
	 */
	for(w_it=words.begin();w_it!=words.end();w_it++){
		//Check predecessor fit,and maximal size
						tempVarNums=(w_it->p).GetNumOfVars();
						tempNamesClean=(w_it->p).GetNamesClean();
						iVar=p1VarNums.find(tempVarNums);
						iNames=p1CleanNames.find(tempNamesClean);
						//double fitting - clean names and number of variables in each function, at the start of the current location
						if((iVar==0)&&(iNames==0)){
							iTempName=tempNamesClean.length();
							iTempVar=tempVarNums.length();
							// clean names length greater then the best fit so far length of clean names
							if(iTempName>choTempNamesClean.length()){
								//right and left terms met
								rightSideCon=w_it->r.GetTemplate().empty();
								if(!rightSideCon){
									rightResidual=p1CleanNames.substr(iTempName);
									rightSideCon=(rightResidual.find((w_it->r).GetNamesClean())==0);
									rightResidual=p1VarNums.substr(iTempVar);
									if(rightResidual=="")rightResidual="_0";
									rightSideCon=rightSideCon&&(rightResidual.find((w_it->r).GetNumOfVars())==0);

								}
								leftSideCon=w_it->l.GetTemplate().empty();
								if(!leftSideCon){
									paraString pl(current.substr(0,*t_i));
									leftCon=(w_it->l).GetNamesClean();
									t2=pl.GetNamesClean().rfind(leftCon);
									leftSideCon=(t2!=leftResidual.npos)&&(t2+leftCon.length()==pl.GetNamesClean().length());
									leftCon=(w_it->l).GetNumOfVars();
									t2=pl.GetNumOfVars().rfind(leftCon);
									leftSideCon=(t2!=leftResidual.npos)&&(t2+leftCon.length()==pl.GetNumOfVars().length());
//									leftSideCon=leftSideCon&&(t2!=leftResidual.npos)&&(t2+leftCon.length()==leftResidual.length());
								}
								if(leftSideCon&&rightSideCon){

									best=*w_it;
									choTempNamesClean=tempNamesClean;
								}
							}
	}
	}
		//	size_t oldNamLoc=findNth(oldString.GetNamesClean(), "_", *t_i);
		//	size_t oldVarNLoc=findNth(oldString.GetNumOfVars(), "_", *t_i);
		//	bool	newWordFoundFlag=false;//boolean variable for the question - do we have yet a proper non default nominee
		//	bool	rightSideCon,leftSideCon,unitedTermsCon=1;// boolean variables for the Q's: does the right side condition meets? and same for left
		//	string	chosenOldWord="",chosenParsedNewWord,leftCon;//chosenOldWord - the current old word string template,chosenParsedNewWord - the return value of parsed (with variable numeric values included
		//	string	oldVarNums=(oldString.GetNumOfVars()).substr(oldVarNLoc),oldCleanNames=(oldString.GetNamesClean()).substr(oldNamLoc);// current sub strings for the current sub sentence
		//	string	tempVarNums="",choTempVarNums="",tempNamesClean="",choTempNamesClean="",leftResidual,rightResidual;
		//	vector	<word>::	iterator w_it;
		//	vector	<term>::	iterator t_it;
		//	size_t iVar,iNames,iTempName,iTempVar,t2;
		//
		//	/* for loop all the possible words fit (maximal predecessor,keeping all terms) -so we got a simple function -
		//	 * gets the current maximal word length(parametric, no numbers), checking if the current predecessor fits the string head, after words calls for terms checking function, than
		//	 * if word length is maximal, then parsing, and holding the new one as the best, untill scanning all words, across the oldSubString. returning the current location in the old string, and the new parsed word for the new string
		//	 */
		//	for(w_it=words.begin();w_it!=words.end();w_it++){
		//		//Check predecessor fit,and maximal size
		//		tempVarNums=(w_it->p).GetNumOfVars();
		//		tempNamesClean=(w_it->p).GetNamesClean();
		//		iVar=oldVarNums.find(tempVarNums);
		//		iNames=oldCleanNames.find(tempNamesClean);
		//		//double fitting - clean names and number of variables in each function, at the start of the current location
		//		if((iVar==0)&&(iNames==0)){
		//			iTempName=tempNamesClean.length();
		//			iTempVar=tempVarNums.length();
		//			// clean names length greater then the best fit so far length of clean names
		//			if(iTempName>choTempNamesClean.length()){
		//				//right and left terms met
		//				rightSideCon=w_it->r.GetTemplate().empty();
		//				if(!rightSideCon){
		//					rightResidual=oldCleanNames.substr(iTempName);
		//					rightSideCon=(rightResidual.find((w_it->r).GetNamesClean())==0);
		//					rightResidual=oldVarNums.substr(iTempVar);
		//					rightSideCon=rightSideCon&&(rightResidual.find((w_it->r).GetNumOfVars())==0);
		//
		//				}
		//				leftSideCon=w_it->l.GetTemplate().empty();
		//				if(!leftSideCon){
		//									leftResidual=(oldString.GetNumOfVars()).substr(0,*t_i);
		//									leftCon=(w_it->l).GetNamesClean();
		//									t2=leftResidual.rfind(leftCon);
		//									leftSideCon=(t2!=leftResidual.npos)&&(t2+leftCon.length()==leftResidual.length());
		//									leftResidual=oldVarNums.substr(iTempVar);
		//									leftCon=(w_it->l).GetNumOfVars();
		//									t2=leftResidual.rfind(leftCon);
		//									leftSideCon=rightSideCon&&leftSideCon=(t2!=leftResidual.npos)&&(t2+leftCon.length()==leftResidual.length());
		//								}
		//				if(rightSideCon&&leftSideCon){
		//					//If both sides  conditions are met, we continue to checking the terms
		//					vector <variable> 	v;
		//					unsigned int NoS=count(tempVarNums.begin(),tempVarNums.end(),'_');
		//					unsigned int iSubOld=count(tempVarNums.begin(),tempVarNums.end(),'_');
		//					predecessor pTemp()
		//					// get predecessor variables
		//					// get the variables values
		//					if(!w_it->t.empty()){
		//						for(t_it=w_it->t.begin();t_it!=w_it->t.end();t_it++){
		//
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		////	*PartialOldString=OldStringResidual;
		//	return chosenParsedNewWord;
		return "-1";
	}
	/*making a complete and and value variables set from two variables set- 1) symbolic with no values, only param names,and one numeric with paramvalues but generic names
	 *  */
	//	//		input - standard LSYS formulation:
	//	//
	//	//		axiom: ####;
	//	//		words:
	//	//		#->#;
	//	//		#->#;
	//	//		#->#;
	//	//		endsys
	//	/*input may be any set of chars excluding ';'*/
	//	//Initialize simulation time
	//	timestep=0;
	//
	//	//Parsing the expression
	//	//	this->words = new vector<word>;
	//	//	this->ignore= new string;
	//	//	this->axiom=new string;
	//	string temp,temp_p,temp_s;
	//	size_t t1,t2;
	//	//	//step 1 - axiom
	//	t1=s.find("#ignore:");
	//	if(t1!=s.npos){
	//		t2=s.find(";");
	//		this->ignore=s.substr(t1+8,t2-t1-8);}
	//	t1=s.find("axiom:");
	//	if(t1==s.npos){
	//		cout << "system's axiom is missing" << endl;
	//		terminate();
	//	}
	//	t2=s.find(";words:");
	//	if(t2==s.npos){
	//		cout << "Illegal input -axiom footer or words header" << endl;
	//		terminate();
	//	}
	//	this->axiom=s.substr(t1+6,t2-t1-6);
	//	history.push_back(axiom);
	//	//step 2 - words
	//	s=s.substr(t2+7);
	//	t1=s.find(";");
	//	if(t1==s.npos){
	//		cout << "no legal words" << endl;
	//		terminate();
	//	}
	//	while(t1!=s.npos){
	//		word w;
	//		t1=s.find(";");
	//		temp=s.substr(0,t1);
	//		temp.erase(remove(temp.begin(), temp.end(), ';'), temp.end());
	//		t1=temp.find("->");
	//		if((t1!=temp.npos)&&(!(temp.substr(0,t1)).empty())){
	//			temp_p=temp.substr(0,t1);
	//			//			 if left term exist than extract it
	//			if(temp_p.find("<")!=temp_p.npos){
	//				size_t tl=temp_p.find("<");
	//				//				left term extraction
	//				w.l=temp_p.substr(0,tl);
	//				//					cout << w.l << endl;
	//				//Predecessor
	//				temp_p=temp_p.substr(tl+1);
	//				//					cout << temp_p << endl;
	//			}else w.l="";
	//			if(temp_p.find(">")!=temp_p.npos){
	//				size_t tl=temp_p.find(">");
	//				//left term extraction
	//				w.r=temp_p.substr(tl+1);
	//				//					cout << w.l << endl;
	//				//predeccessor
	//				temp_p=temp_p.substr(0,tl);
	//				//					cout << temp_p << endl;
	//			}else w.r="";
	//			//				cout<<temp<<endl;
	//			if(!((temp.substr(t1+2)).empty())){
	//				temp_s=temp.substr(t1+2);
	//			}else temp_s=temp_p;
	//			w.p=temp_p;
	//			//								cout << "pre:"<<w.p << endl;
	//			w.s=temp_s;
	//			//								cout << "suc:"<<w.s << endl;
	//			//			word *q=&w;
	//			this->words.push_back(w);
	//		}
	//		t1=s.find(";");
	//		s=s.substr(t1+1);
	//	}
	//	t1=s.find("endsys");
	//	if(t1==s.npos){
	//		cout << "footnote e 'endsys' is missing " << endl;
	//		terminate();
	//	}}
	////
	////
	////}
	////LSYS::~LSYS(){
	////	delete &(this->words);
	////}
	//string LSYS::ignoreIt(string s){
	//	for(unsigned int i=0;i<this->ignore.length();i++){
	//		s.erase(remove(s.begin(), s.end(), this->ignore[i]), s.end());
	//	}
	//	return s;
	//}
	////
	//bool LSYS::leftCon(string oldword,size_t t,string left){
	//	if(left.length()==0)
	//		return 1;
	//	if((t==0)&&(left.length()>0))
	//		return 0;
	//	if(t-left.length()<0)
	//		return 0;
	//
	//	string preword="";
	//	preword=oldword.substr(0,t);
	//	preword=this->ignoreIt(preword);
	//	size_t t2=preword.rfind(left);
	//	if(t2==preword.npos)
	//		return 0;
	//	if(t2+left.length()==preword.length())
	//		return 1;
	//	return 0;}
	//
	///*a function that checks the right term*/
	//bool LSYS::rightCon(string oldword,size_t t2,string right){
	//	if(right.length()==0)
	//		return 1;
	//	if(t2>oldword.length())
	//		return 0;
	//	string postword=oldword.substr(t2);
	//	postword=this->ignoreIt(postword);
	//	if(right.length()>postword.length())
	//		return 0;
	//	size_t t1=postword.find(right);
	//	if (t1==0)
	//		return 1;
	//	return 0;}
	//
	///*a function the propagate the system one time step and prints the system's current state*/
	//int LSYS::propagate(){
	//	string oldword=*(--this->history.end());
	//	string bestpre,bestsuc,tempPre,tempLeft,tempRight,bestLeft,bestRight;
	//	string newword="";
	//	int condition,lcon,rcon;
	//	size_t t_old1=0,tp;
	//	vector<word>::iterator t;
	//	while(t_old1<oldword.length()){
	//		condition=0;
	//		bestpre="";
	//		bestsuc="";
	//		tempPre="";
	//		tempLeft="";
	//		tempRight="";
	//		bestRight="";
	//		bestLeft="";
	//		for(t=this->words.begin();t!=this->words.end();t++){
	//			tempPre=t->p;
	//			tempLeft=t->l;
	//			tempRight=t->r;
	//			lcon=0;
	//			rcon=0;
	//			tp=oldword.substr(t_old1).find(tempPre);
	//			//				cout << oldword.substr(t_old1).length() <<endl;
	//			if(tp==0){
	//
	//				//					if(tempLeft.empty())lcon=1;
	//				//					else if (tempLeft.length()>t_old1)lcon=0;
	//				//				//					else lcon=(tempLeft==oldword.substr(t_old1-tempLeft.length(),tempLeft.length()));
	//				//				//					if(tempRight.empty())rcon=1;
	//				//				//					else if (tempRight.length()>(oldword.substr(t_old1)).length()-tempPre.length())rcon=0;
	//				//				//					else rcon=(tempRight==oldword.substr(t_old1+tempPre.length(),tempRight.length()));
	//				lcon=this->leftCon(oldword, t_old1, tempLeft);
	//				rcon=this->rightCon(oldword, t_old1+tempPre.length(), tempRight);
	//				if((tempPre.length()>=bestpre.length())&&(tempLeft.length()>=bestLeft.length())&&(tempRight.length()>=bestRight.length())&&lcon&&rcon){
	//					if(tempPre.length()>bestpre.length()){
	//						bestpre=tempPre;
	//						tempLeft=bestLeft;
	//						tempRight=bestRight;
	//						bestsuc=t->s;
	//						condition=1;
	//					}else if((tempRight.length()>bestRight.length())||(tempLeft.length()>bestLeft.length())){
	//						bestpre=tempPre;
	//						tempLeft=bestLeft;
	//						tempRight=bestRight;
	//						bestsuc=t->s;
	//						condition=1;
	//					}
	//				}
	//			}
	//		}
	//		if(condition==0){
	//			bestpre=oldword[t_old1];
	//			bestsuc=bestpre;
	//		}
	//
	//		newword+=bestsuc;
	//		//			cout<< newword<< endl;
	//		t_old1+=bestpre.length();
	//	}
	//	cout<< newword<< endl;
	//	this->history.push_back(newword);
	//	this->timestep++;
	//	return 0;}



