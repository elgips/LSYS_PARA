/*
 * MyClass.cpp
 *
 *  Created on: Aug 19, 2020
 *      Author: gips
 */
#include "LSYS_PARA.h"
/*Variable definition*/

variable::variable(void){
	this->name="";
	this->value=new double;
}

variable::variable(string Name){
	this->name=Name;
	this->value=new double;
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
	this->p=new mu::Parser;
	this->Template="";
	this->variables=new vector	<variable>;
}

expression::expression(string tmplt){
	this->p=new mu::Parser;
	this->Template=tmplt;
	this->variables=new vector	<variable>;
	this->p.SetExpr(tmplt);
}

expression::expression(vector <variable> Variables,string tmplt){
	this->p=new mu::Parser;
	this->Template=tmplt;
	vector<variable> vars1(Variables);
	this->variables= vars1;
	this->ParseVariables();
}

void expression::SetTemplet(string tmplt){
	this->Template=tmplt;
	this->p.SetExpr(tmplt);
}

void expression::SetVariables(vector <variable> Variables){
	vector<variable> vars1(Variables);
	this->variables= vars1;
	this->ParseVariables();
}
void expression::ParseVariables(){
	vector<variable>::iterator t;
	for(t=this->variables.begin();t!=this->variables.end();t++){
		double * VarPlace = &(t->value);
		p.DefineVar(t->name, VarPlace);
	}
}

/*End of expression definition*/

/*Term definition*/

bool term::evalVal(){
	bool x;
	x=static_cast<bool>(p.Eval());
	return x;
}

/*End of Term definition*/

/*SuccessorVariable definition*/

double sucVar::evalVal(){

	return p.Eval();
}

/*End of successorVariable definition*/

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
	string tempName,SubTemp=Template,varsTemp,VarName;
	int varCounter;
	size_t t1=0,t2,t3;
	while(t1!=Template.npos){
		t2=SubTemp.find("(");
		if(t2==SubTemp.npos){
			namesClean+=SubTemp;
			t1=Template.npos;
		}else{
			namesClean+=SubTemp.substr(0,t2-1);
			t3=SubTemp.find(")");
			varCounter=0;
			if (t2<t3){
				varsTemp=SubTemp.substr(t2+1,t3-t2-1)
				varCounter=1;
				if(varsTemp.find(",")==varsTemp.npos){
					Var
				}
				for(unsigned int i=t2+1,i0=i;i<t3-1;i++){
					if(SubTemp[i]==',')	varCounter++;
						VarName=SubTemp.substr(i0, i-1);

				}
			}
			numOfVars+="_";
			numOfVars+=to_string(varCounter);
			t1=t1+t3;
		}
	}
	if(numOfVars.empty())numOfVars="0";
}

paraString::paraString(){
	Template="";
	numOfVars="";
	namesClean="";
	variables=new vector <variable>;
}

paraString::paraString(string tmplt){
	Template=tmplt;
	numOfVars=;
	namesClean="";
	variables=new vector <variable>;
}

/*End of successorVariable definition*/

word::word(){
	this->l="";
	this->stWord="";
	this->p="";
	this->r="";
	this->s="";
}
word::word(string L,string S,string P,string R){
	this->l=L;
	this-stWord="";
	this->p=P;
	this->r=R;
	this->s=S;
}
LSYS::LSYS(string s){
	s.erase(remove(s.begin(), s.end(), ' '), s.end());
	//		input - standard LSYS formulation:
	//
	//		axiom: ####;
	//		words:
	//		#->#;
	//		#->#;
	//		#->#;
	//		endsys
	/*input may be any set of chars excluding ';'*/
	//Initialize simulation time
	timestep=0;

	//Parsing the expression
	//	this->words = new vector<word>;
	//	this->ignore= new string;
	//	this->axiom=new string;
	string temp,temp_p,temp_s;
	size_t t1,t2;
	//	//step 1 - axiom
	t1=s.find("#ignore:");
	if(t1!=s.npos){
		t2=s.find(";");
		this->ignore=s.substr(t1+8,t2-t1-8);}
	t1=s.find("axiom:");
	if(t1==s.npos){
		cout << "system's axiom is missing" << endl;
		terminate();
	}
	t2=s.find(";words:");
	if(t2==s.npos){
		cout << "Illegal input -axiom footer or words header" << endl;
		terminate();
	}
	this->axiom=s.substr(t1+6,t2-t1-6);
	history.push_back(axiom);
	//step 2 - words
	s=s.substr(t2+7);
	t1=s.find(";");
	if(t1==s.npos){
		cout << "no legal words" << endl;
		terminate();
	}
	while(t1!=s.npos){
		word w;
		t1=s.find(";");
		temp=s.substr(0,t1);
		temp.erase(remove(temp.begin(), temp.end(), ';'), temp.end());
		t1=temp.find("->");
		if((t1!=temp.npos)&&(!(temp.substr(0,t1)).empty())){
			temp_p=temp.substr(0,t1);
			//			 if left term exist than extract it
			if(temp_p.find("<")!=temp_p.npos){
				size_t tl=temp_p.find("<");
				//				left term extraction
				w.l=temp_p.substr(0,tl);
				//					cout << w.l << endl;
				//Predecessor
				temp_p=temp_p.substr(tl+1);
				//					cout << temp_p << endl;
			}else w.l="";
			if(temp_p.find(">")!=temp_p.npos){
				size_t tl=temp_p.find(">");
				//left term extraction
				w.r=temp_p.substr(tl+1);
				//					cout << w.l << endl;
				//predeccessor
				temp_p=temp_p.substr(0,tl);
				//					cout << temp_p << endl;
			}else w.r="";
			//				cout<<temp<<endl;
			if(!((temp.substr(t1+2)).empty())){
				temp_s=temp.substr(t1+2);
			}else temp_s=temp_p;
			w.p=temp_p;
			//								cout << "pre:"<<w.p << endl;
			w.s=temp_s;
			//								cout << "suc:"<<w.s << endl;
			//			word *q=&w;
			this->words.push_back(w);
		}
		t1=s.find(";");
		s=s.substr(t1+1);
	}
	t1=s.find("endsys");
	if(t1==s.npos){
		cout << "footnote e 'endsys' is missing " << endl;
		terminate();
	}}
//
//
//}
//LSYS::~LSYS(){
//	delete &(this->words);
//}
string LSYS::ignoreIt(string s){
	for(unsigned int i=0;i<this->ignore.length();i++){
		s.erase(remove(s.begin(), s.end(), this->ignore[i]), s.end());
	}
	return s;
}
//
bool LSYS::leftCon(string oldword,size_t t,string left){
	if(left.length()==0)
		return 1;
	if((t==0)&&(left.length()>0))
		return 0;
	if(t-left.length()<0)
		return 0;

	string preword="";
	preword=oldword.substr(0,t);
	preword=this->ignoreIt(preword);
	size_t t2=preword.rfind(left);
	if(t2==preword.npos)
		return 0;
	if(t2+left.length()==preword.length())
		return 1;
	return 0;}

/*a function that checks the right term*/
bool LSYS::rightCon(string oldword,size_t t2,string right){
	if(right.length()==0)
		return 1;
	if(t2>oldword.length())
		return 0;
	string postword=oldword.substr(t2);
	postword=this->ignoreIt(postword);
	if(right.length()>postword.length())
		return 0;
	size_t t1=postword.find(right);
	if (t1==0)
		return 1;
	return 0;}

/*a function the propagate the system one time step and prints the system's current state*/
int LSYS::propagate(){
	string oldword=*(--this->history.end());
	string bestpre,bestsuc,tempPre,tempLeft,tempRight,bestLeft,bestRight;
	string newword="";
	int condition,lcon,rcon;
	size_t t_old1=0,tp;
	vector<word>::iterator t;
	while(t_old1<oldword.length()){
		condition=0;
		bestpre="";
		bestsuc="";
		tempPre="";
		tempLeft="";
		tempRight="";
		bestRight="";
		bestLeft="";
		for(t=this->words.begin();t!=this->words.end();t++){
			tempPre=t->p;
			tempLeft=t->l;
			tempRight=t->r;
			lcon=0;
			rcon=0;
			tp=oldword.substr(t_old1).find(tempPre);
			//				cout << oldword.substr(t_old1).length() <<endl;
			if(tp==0){

				//					if(tempLeft.empty())lcon=1;
				//					else if (tempLeft.length()>t_old1)lcon=0;
				//				//					else lcon=(tempLeft==oldword.substr(t_old1-tempLeft.length(),tempLeft.length()));
				//				//					if(tempRight.empty())rcon=1;
				//				//					else if (tempRight.length()>(oldword.substr(t_old1)).length()-tempPre.length())rcon=0;
				//				//					else rcon=(tempRight==oldword.substr(t_old1+tempPre.length(),tempRight.length()));
				lcon=this->leftCon(oldword, t_old1, tempLeft);
				rcon=this->rightCon(oldword, t_old1+tempPre.length(), tempRight);
				if((tempPre.length()>=bestpre.length())&&(tempLeft.length()>=bestLeft.length())&&(tempRight.length()>=bestRight.length())&&lcon&&rcon){
					if(tempPre.length()>bestpre.length()){
						bestpre=tempPre;
						tempLeft=bestLeft;
						tempRight=bestRight;
						bestsuc=t->s;
						condition=1;
					}else if((tempRight.length()>bestRight.length())||(tempLeft.length()>bestLeft.length())){
						bestpre=tempPre;
						tempLeft=bestLeft;
						tempRight=bestRight;
						bestsuc=t->s;
						condition=1;
					}
				}
			}
		}
		if(condition==0){
			bestpre=oldword[t_old1];
			bestsuc=bestpre;
		}

		newword+=bestsuc;
		//			cout<< newword<< endl;
		t_old1+=bestpre.length();
	}
	cout<< newword<< endl;
	this->history.push_back(newword);
	this->timestep++;
	return 0;}



