#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
typedef void(*rs)();
map<string,rs>keywords;
vector<string>code;
map<string,int>dei;
short *ram;
int a,b,c;
string jph;
vector<string>sduc;
int index=1;
map<string,int>jpd;
void run(vector<string>&sduc){
	if(sduc[0][0]==':'||sduc[0][0]=='#') return;
	try{
		if(keywords[sduc[0]]==0) throw runtime_error("\'"+sduc[0]+"\' is not define!");
		keywords[sduc[0]]();
	}catch(const runtime_error &e){
		cout<<"On line "<<index<<",catch a error:"<<e.what()<<'\n';
	}catch (...){
		cout<<"On line"<<index<<",have unknown error\n"<<'\n';
	}
}
int gein(string s){return ('0'<=s[0]&&s[0]<='9')||s[0]=='-'?atoi(s.c_str()):dei[s];}
vector<string> opencode(string x);
void fp() {a=atoi(sduc[1].c_str());ram=new short[a];for(int i=0;i<a;i++) ram[i]=0;}
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
			run(sduc);
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
			run(sduc);
			index++;
		}
	}
	return; 
}
void defi(){string s=sduc[1].c_str();int a=atoi(sduc[2].c_str());dei[s]=a;}
void _max(){int a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=max(ram[a],ram[b]);}
void _min(){int a=gein(sduc[1].c_str()),b=gein(sduc[2].c_str());ram[a]=min(ram[a],ram[b]);}
inline void init() {
	keywords["defi"]=defi;
	keywords["fp"]=fp;
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
	keywords["max"]=_max;
	keywords["min"]=_min;
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
	for(; index<(int)code.size(); index++) run(sduc=opencode(code[index]));
	return 0;
}
