#include<bits/stdc++.h> 
using namespace std;
typedef void(*rs)();
map<string,rs>keywords;
vector<string>code;
char *ram;
int a,b;
int index=1;
void fp(){ram=new char[a];}
void mio(){ram[a]=ram[b];}
void mov(){ram[a]=b;}
void add(){ram[a]=ram[a]+ram[b];}
void sub(){ram[a]=ram[a]-ram[b];}
void tim(){ram[a]=ram[a]*ram[b];}
void div(){ram[a]=ram[a]/ram[b];}
void mod(){ram[a]=ram[a]%ram[b];}
void _and(){ram[a]=ram[a]&ram[b];}
void _or(){ram[a]=ram[a]|ram[b];}
void _not(){ram[a]=~ram[a];}
void _xor(){ram[a]=ram[a]^ram[b];}
void rmv(){ram[a]=ram[a]>>ram[b];}
void lmv(){ram[a]=ram[a]<<ram[b];}
void jmp(){index=ram[a];}
void _if(){ram[a]&1?index+=1:index+=2;}
void ext(){exit(0);}
void put(){cout<<(int)ram[a];}
void get(){short temp;cin>>temp;ram[a]=temp;}
void sam(){ram[a]=ram[a]==ram[b];}
void gre(){ram[a]=ram[a]>ram[b];}
void les(){ram[a]=ram[a]<ram[b];}
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
	keywords["not"]=_not;
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
	keywords["ext"]=ext;
	return;
}
vector<string> opencode(string x)
{
	vector<string>ret;
	string s;
	for(char i:x)
	{
		if(i==' ')
		{
			ret.push_back(s);
			s="";
		}
		else
		{
			s=s+i;
		}
	}
	ret.push_back(s);
	return ret;
}
int main()
{
	init();
	string path,s;
	cin>>path;
	ifstream dim(path.c_str());
	code.push_back("");
	while(getline(dim,s))
	{
		code.push_back(s);
	}
	for(;index<(int)code.size();index++)
	{
		vector<string>sduc=opencode(code[index]);
		if(sduc.size()==2)
		{
			a=atoi(sduc[1].c_str());
		}
		else
		{
			a=atoi(sduc[1].c_str());
			b=atoi(sduc[2].c_str());
		}
		keywords[sduc[0]]();
	}
	return 0;
}
