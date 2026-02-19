#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
typedef void(*rs)();
struct node
{
	string s;
	int inindex;
	vector<int>input;
	short* p;
	node(string& _s,int _inindex,vector<int>&_input,short* _p)
	{
		s=_s;
		inindex=_inindex;
		input=_input;
		p=_p;
	}
};
map<string,rs>keywords;
map<string,int>user;
vector<string>code;
short *ram;
int a,b,c;
string jph;
vector<string>sduc;
int index=1;
map<string,int>jpd;
stack<node>s;
void run(vector<string>&sduc)
{
	if(sduc[0][0]==':'||sduc[0][0]=='#') return;
	try
	{
		if(keywords[sduc[0]]==0&&keywords[sduc[0]]==0)
		{
			throw runtime_error("\'"+sduc[0]+"\' is not define!");
		}
		keywords[sduc[0]]();
	}
	catch(const runtime_error &e)
	{
		cout<<"\nOn line "<<index<<",catch a error:"<<e.what()<<'\n';
	}
	catch (...)
	{
		cout<<"\nunknown error\n"<<'\n';
	}
}
void funcrun(vector<string>&sduc)
{
	if(sduc[0][0]==':'||sduc[0][0]=='#'||sduc[0]=="def") return;
	try
	{
		if(keywords[sduc[0]]==0&&keywords[sduc[0]]==0)
		{
			throw runtime_error("\'"+sduc[0]+"\' is not define!");
		}
		keywords[sduc[0]]();
	}
	catch(const runtime_error &e)
	{
		cout<<"On line "<<index<<",catch a error:"<<e.what()<<'\n';
	}
	catch (...)
	{
		cout<<"\nunknown error\n"<<'\n';
	}
}
vector<string> opencode(string x);
void fp() {a=atoi(sduc[1].c_str());ram=new short[a];}
void mov() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[b];}
void mio() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=b;}
void add() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]+ram[b];}
void sub() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]-ram[b];}
void tim() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]*ram[b];}
void div() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]/ram[b];}
void mod() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]%ram[b];}
void _and() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]&ram[b];}
void _or() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]|ram[b];}
void _compl() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=~ram[a];}
void _xor() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]^ram[b];}
void rmv() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]>>ram[b];}
void lmv() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=ram[a]<<ram[b];}
void jmp() {jph=sduc[1];index=jpd[jph];}
void jmpn() {index=ram[a]-1;}
void _if() {a=atoi(sduc[1].c_str());ram[a]&1?:index++;}
void ext() {cout<<"\ncode exit\n";system("pause");exit(0);}
void put() {a=atoi(sduc[1].c_str());cout<<ram[a];}
void get() {a=atoi(sduc[1].c_str());cin>>ram[a];}
void putc() {a=atoi(sduc[1].c_str());cout<<(char)ram[a];}
void getc() {a=atoi(sduc[1].c_str());char c;cin>>c;ram[a]=c;}
void sam() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=(ram[a]==ram[b]);}
void gre() {a=atoi(sduc[1].c_str());ram[a]=(ram[a]>ram[b]);}
void les() {a=atoi(sduc[1].c_str());ram[a]=(ram[a]<ram[b]);}
void _for()
{
	const int a=atoi(sduc[1].c_str());
	const int b=atoi(sduc[2].c_str());
	const int c=atoi(sduc[3].c_str());
	index++;
	const int temp=index;
	for(ram[a]=ram[b];ram[a]<=ram[c];ram[a]++)
	{
		while(1)
		{
			sduc=opencode(code[index]);
			if(sduc[0]=="end")
			{
				if(ram[a]<ram[c])
				{
					index=temp;
					break;
				}
			}
			run(sduc);
			index++;
		}
	}
	return; 
}
void frram() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());ram[a]=s.top().p[b];}
void fmov() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[b];}
void fmio() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=b;}
void fadd() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]+s.top().p[b];}
void fsub() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]-s.top().p[b];}
void ftim() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]*s.top().p[b];}
void fdiv() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]/s.top().p[b];}
void fmod() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]%s.top().p[b];}
void f_and() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]&s.top().p[b];}
void f_or() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]|s.top().p[b];}
void f_compl() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=~s.top().p[a];}
void f_xor() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]^s.top().p[b];}
void frmv() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]>>s.top().p[b];}
void flmv() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=s.top().p[a]<<s.top().p[b];}
void fjmp() {jph=sduc[1];index=jpd[jph];}
void fjmpn() {index=s.top().p[a]-1;}
void f_if() {a=atoi(sduc[1].c_str());s.top().p[a]&1?:index++;}
void fext() {cout<<"\ncode exit\n";system("pause");exit(0);}
void fput() {a=atoi(sduc[1].c_str());cout<<s.top().p[a];}
void fget() {a=atoi(sduc[1].c_str());cin>>s.top().p[a];}
void fputc() {a=atoi(sduc[1].c_str());cout<<(char)s.top().p[a];}
void fgetc() {a=atoi(sduc[1].c_str());char c;cin>>c;s.top().p[a]=c;}
void fsam() {a=atoi(sduc[1].c_str()),b=atoi(sduc[2].c_str());s.top().p[a]=(s.top().p[a]==s.top().p[b]);}
void fgre() {a=atoi(sduc[1].c_str());b=atoi(sduc[2].c_str());s.top().p[a]=(s.top().p[a]>s.top().p[b]);}
void fles() {a=atoi(sduc[1].c_str());b=atoi(sduc[2].c_str());s.top().p[a]=(s.top().p[a]<s.top().p[b]);}
void finput() {a=atoi(sduc[1].c_str());b=atoi(sduc[2].c_str());s.top().p[a]=s.top().input[b];}
void ffor()
{
	const int a=atoi(sduc[1].c_str());
	const int b=atoi(sduc[2].c_str());
	const int c=atoi(sduc[3].c_str());
	index++;
	const int temp=index;
	for(s.top().p[a]=s.top().p[b];s.top().p[a]<=s.top().p[c];s.top().p[a]++)
	{
		while(1)
		{
			sduc=opencode(code[index]);
			if(sduc[0]=="end")
			{
				if(s.top().p[a]<s.top().p[c])
				{
					index=temp;
					break;
				}
			}
			run(sduc);
			index++;
		}
	}
	return; 
}
void func()
{
	vector<short>tws;
	string temp;
	for(char i:sduc[2])
	{
		if(i==',')
		{
			tws.push_back(atoi(temp.c_str()));
			temp="";
		}
		else
		{
			temp=temp+i;
		}
	}
	short p;
	s.push(node(
		sduc[1],
		index,
		tws,
		new short[atoi(sduc[3])]
	));
	for(index=user[sduc[1]]+1;;index++)
	{
		sduc=opencode(code[index]);
		if(sduc[0]=="end")
		{
			index=s.top().inindex;
			s.pop();
			return;
		}
		else
		{
			funcrun(sduc);
		}
	}
}
void null(){}
inline void init()
{
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
	keywords["jmpn"]=jmpn;
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
	keywords["func"]=func;
	keywords["fmio"]=fmio;
	keywords["fmov"]=fmov;
	keywords["fadd"]=fadd;
	keywords["fsub"]=fsub;
	keywords["ftim"]=ftim;
	keywords["fdiv"]=fdiv;
	keywords["fmod"]=fmod;
	keywords["fand"]=f_and;
	keywords["for"]=f_or;
	keywords["fcompl"]=f_compl;
	keywords["fxor"]=f_xor;
	keywords["frmv"]=frmv;
	keywords["flmv"]=flmv;
	keywords["fjmp"]=fjmp;
	keywords["fjmpn"]=fjmpn;
	keywords["fsam"]=fsam;
	keywords["fgre"]=fgre;
	keywords["fles"]=fles;
	keywords["fif"]=f_if;
	keywords["fext"]=fext;
	keywords["fput"]=fput;
	keywords["fget"]=fget;
	keywords["fputc"]=fputc;
	keywords["fgetc"]=fgetc;
	keywords["ffor"]=ffor;
	keywords["frram"]=ffor;
	keywords["finput"]=finput;
	keywords["def"]=null;
	return;
}
vector<string> opencode(string x)
{
	vector<string>ret;
	string s;
	for(char i:x)
		if(i==' ') ret.push_back(s),s="";
		else s=s+i;
	ret.push_back(s);
	return ret;
}
int main(int argc, char* argv[])
{
	init();
	string path,s;
	if(argc>1) path=argv[1];
	else cin>>path;
	system("cls");
	ifstream dim(path.c_str());
	code.push_back("");
	int line=0;
	while(getline(dim,s))
	{
		line++;
		code.push_back(s);
		if(s[0]==':')
		{
			jpd[s.substr(1)]=line;
		}
		if(s.substr(0,3)=="def")
		{
			sduc=opencode(s);
			user[sduc[1]]=line;
		}
	}
	for(;index<(int)code.size(); index++)
	{
		run(sduc=opencode(code[index]));
	}
	return 0;
}
