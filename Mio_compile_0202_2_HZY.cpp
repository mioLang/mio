#include<bits/stdc++.h>
using namespace std;
typedef void(*rs)();
int varnum;
long long *ram;
int a,b,c;
string jph;
int index=1;
vector<string>code;
vector<string>sduc;
unordered_map<string,rs>keywords;
unordered_map<string,stack<int> >var;
unordered_map<string,int>jpd;
unordered_map<string,int>funname;
unordered_map<string,vector<string>>funin;
void runcode(vector<string>&sduc){
	if(!sduc.size()||sduc[0][0]==':'||sduc[0][0]=='#') return;
	try{
		if(keywords[sduc[0]]==0) throw runtime_error("\'"+sduc[0]+"\' is not define!");
		keywords[sduc[0]]();
	}catch(const runtime_error &e){
		cout<<"On line "<<index<<",catch a error:"<<e.what()<<'\n';
	}catch (...){
		cout<<"On line"<<index<<",have unknown error\n"<<'\n';
	}
}
int gein(string s){return var[s].top();}
vector<string> opencode(string x);
void fp() {a=atoi(sduc[1].c_str());ram=new long long[a];for(int i=0;i<a;i++) ram[i]=0;}
void mov() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[b];}
void mio() {a=gein(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=b;}
void add() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]+ram[b];}
void sub() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]-ram[b];}
void tim() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]*ram[b];}
void div() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]/ram[b];}
void mod() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]%ram[b];}
void _and() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]&ram[b];}
void _or() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]|ram[b];}
void _compl() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=~ram[a];}
void _xor() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]^ram[b];}
void rmv() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]>>ram[b];}
void lmv() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=ram[a]<<ram[b];}
void jmp() {jph=sduc[1];index=jpd[jph];}
void _if() {a=gein(sduc[1].c_str());ram[a]&1?:index++;}
void ext() {cout<<"\ncode exit\n";system("pause");exit(0);}
void put() {a=gein(sduc[1].c_str());cout<<ram[a];}
void get() {a=gein(sduc[1].c_str());cin>>ram[a];}
void putc() {a=gein(sduc[1].c_str());cout<<(char)ram[a];}
void getc() {a=gein(sduc[1].c_str());char c;cin>>c;ram[a]=c;}
void sam() {a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=(ram[a]==ram[b]);}
void gre() {a=gein(sduc[1].c_str());ram[a]=(ram[a]>ram[b]);}
void les() {a=gein(sduc[1].c_str());ram[a]=(ram[a]<ram[b]);}
void _for(){
	int a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str()),c=gein(sduc[3].c_str());
	index++;
	const int temp=index;
	for(ram[a]=ram[b];ram[a]<=ram[c];ram[a]++){
		while(1){
			sduc=opencode(code[index]);
			if(sduc[0]=="end"){if(ram[a]<ram[c]) index=temp;break;}
			runcode(sduc);
			index++;
		}
	}
	return; 
}
void forn(){
	int a=gein(sduc[1].c_str()),b=atoi(sduc[2].c_str()),c=gein(sduc[3].c_str());
	index++;
	const int temp=index;
	for(ram[a]=b;ram[a]<=ram[c];ram[a]++){
		while(1){
			sduc=opencode(code[index]);
			if(sduc[0]=="end"){if(ram[a]<ram[c]) index=temp;break;}
			runcode(sduc);
			index++;
		}
	}
	return; 
}
void _while(){
	int a=gein(sduc[1].c_str());
	index++;
	const int temp=index;
	while(ram[a]){
		while(1){
			sduc=opencode(code[index]);
			if(sduc[0]=="end"){if(ram[a]) index=temp;break;}
			runcode(sduc);
			index++;
		}
	}
	return; 
}
void add_var(){for(size_t i=1;i<sduc.size();i++)var[sduc[i]].push(++varnum);}
void _max(){int a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=max(ram[a],ram[b]);}
void _min(){int a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=min(ram[a],ram[b]);}
void def(){
	string name=sduc[1];funname[name]=index;
	int inps=atoi(sduc[2].c_str());
	for(int i=1;i<=inps;i++){
		string inp=sduc[i+2];
		funin[name].push_back(inp);
	}
	while(1){
		sduc=opencode(code[index]);
		if(sduc[0]=="endf") break;
		index++;
	}
}
void run(){
	string name=sduc[1];
	int inps=funin[name].size(),temp=index;
	vector<int>inp(inps,0);
	for(int i=0;i<inps;i++) inp[i]=gein(sduc[i+2].c_str()),var[funin[name][i]].push(++varnum),ram[varnum]=ram[inp[i]];
	index=funname[name]+1;
	while(1){
		sduc=opencode(code[index]);
		if(sduc[0]=="endf"||sduc[0]=="return"){
			for(int i=0;i<inps;i++) var[funin[name][i]].pop(),varnum--;
			break;
		}
		runcode(sduc);
		index++;
	}
	index=temp;
}
inline void init() {
	keywords["fp"]=fp;
	keywords["var"]=add_var;
	keywords["mio"]=mio;
	keywords["mov"]=mov;
	keywords["add"]=add;
	keywords["sub"]=sub;
	keywords["tim"]=tim;
	keywords["div"]=div;
	keywords["mod"]=mod;
	keywords["and"]=_and;
	keywords["or"]=_or;
	keywords["compl"]=_compl;
	keywords["xor"]=_xor;
	keywords["rmv"]=rmv;
	keywords["lmv"]=lmv;
	keywords["jmp"]=jmp;
	keywords["sam"]=sam;
	keywords["gre"]=gre;
	keywords["les"]=les;
	keywords["if"]=_if;
	keywords["ext"]=ext;
	keywords["put"]=put;
	keywords["get"]=get;
	keywords["putc"]=putc;
	keywords["getc"]=getc;
	keywords["ext"]=ext;
	keywords["for"]=_for;
	keywords["forn"]=forn;
	keywords["while"]=_while;
	keywords["max"]=_max;
	keywords["min"]=_min;
	keywords["def"]=def;
	keywords["run"]=run;
	return;
}
vector<string> opencode(string x) {
	vector<string>ret;
	string s;
	for(char i:x)
		if(i==' ') ret.push_back(s),s="";
		else s=s+i;
	ret.push_back(s);
	return ret;
}
int main(int argc, char* argv[]) {
	init();
	string path,s;
	if(argc>1) path=argv[1];
	else cin>>path;
	system("cls");
	ifstream dim(path.c_str());
	code.push_back("");
	int line=0;
	while(getline(dim,s)) {
		line++;
		code.push_back(s);
		if(s[0]==':') jpd[s.substr(1)]=line;
	}
	for(; index<(int)code.size(); index++) runcode(sduc=opencode(code[index]));
	return 0;
}
