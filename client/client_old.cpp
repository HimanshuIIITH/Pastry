#include<bits/stdc++.h>
#include "headerfile.h"
#define MAX_SIZE 90000
struct addr{
	string ip;
	string port;
	string nodeId;
};
struct table
{
	string nodeId;
	string ip;
	string port;
	struct addr nSet[4];
	struct addr lSet[4];
	struct addr rTable[8][16];
}node;
map<char,int> h;
map<string,string> mytable;
map<string,addr>mytable2;
map<string,string>keyhashtable;
char buffer[MAX_SIZE];
pthread_t thread1[100];
int lo;
void handle_sigint(int);

vector<string> filter(string s)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	string j="";
	vector<string> v;
	for(int i=0;i<s.length();i++)
	{
		if(s[i]!='+')
		j+=s[i];
		else if(s[i]=='+')
		{
			v.push_back(j);
			if(j=="route")
			return v;
			else if(j=="update")
			return v;
			j="";
		}
		if((i+1)==s.length())
		v.push_back(j);
	}
	return v;
}
string get(table node)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	string t=node.nodeId+"+"+node.ip+"+"+node.port+"+";
	for(int i=0;i<4;i++)
	{
		t+=node.nSet[i].nodeId+"+"+node.nSet[i].ip+"+"+node.nSet[i].port+"+";
	}
	for(int i=0;i<4;i++)
	{
		t+=node.lSet[i].nodeId+"+"+node.lSet[i].ip+"+"+node.lSet[i].port+"+";
	}
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<16;j++)
		{
			t+=node.rTable[i][j].nodeId+"+"+node.rTable[i][j].ip+"+"+node.rTable[i][j].port+"+";
		}
	}
	return t;
}
void setTo(table &temp,string msg)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	int i=0,c=0;
	string t="";
	vector<string> v;
	while(1)
	{
		if(msg[i]=='+')
		c++;
		if(c==4)
		break;
		i++;
		
	}
	for(int j=i+1;j<msg.length();j++)
	{
		if(msg[j]!='+')
		{
			t+=msg[j];	
		}
		else
		{
			v.push_back(t);
			t="";
		}
	}
	c=0;
	temp.nodeId=v[c++];
	temp.ip=v[c++];
	temp.port=v[c++];
	for(int i=0;i<4;i++)
	{
		temp.nSet[i].nodeId=v[c++];
		temp.nSet[i].ip=v[c++];
		temp.nSet[i].port=v[c++];
	}
	for(int i=0;i<4;i++)
	{
		temp.lSet[i].nodeId=v[c++];
		temp.lSet[i].ip=v[c++];
		temp.lSet[i].port=v[c++];
	}
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<16;j++)
		{
			temp.rTable[i][j].nodeId=v[c++];
			temp.rTable[i][j].ip=v[c++];
			temp.rTable[i][j].port=v[c++];
		}
	}
}
void setToU(table &temp,string msg)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	int i=0,c=0;
	string t="";
	vector<string> v;
	for(int j=7;j<msg.length();j++)
	{
		if(msg[j]!='+')
		{
			t+=msg[j];	
		}
		else
		{
			v.push_back(t);
			t="";
		}
	}
	c=0;
	temp.nodeId=v[c++];
	temp.ip=v[c++];
	temp.port=v[c++];
	for(int i=0;i<4;i++)
	{
		temp.nSet[i].nodeId=v[c++];
		temp.nSet[i].ip=v[c++];
		temp.nSet[i].port=v[c++];
	}
	for(int i=0;i<4;i++)
	{
		temp.lSet[i].nodeId=v[c++];
		temp.lSet[i].ip=v[c++];
		temp.lSet[i].port=v[c++];
	}
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<16;j++)
		{
			temp.rTable[i][j].nodeId=v[c++];
			temp.rTable[i][j].ip=v[c++];
			temp.rTable[i][j].port=v[c++];
		}
	}
}
void print(addr t)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	cout<<"\n\n----------------Self Info---------------------\n\n";
	cout<<t.ip<<"\n"<<t.nodeId<<endl<<t.port<<endl;
}
void print(table t)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	cout<<"----------------Node----------------------"<<endl;
	cout<<t.ip<<" "<<t.nodeId<<" "<<t.port<<endl;
	cout<<endl<<"-------------------------------NSet--------------------------"<<endl<<endl;
	for(int i=0;i<4;i++)
	{
		if(t.nSet[i].nodeId!="_")
		cout<<t.nSet[i].ip<<" "<<t.nSet[i].port<<" "<<t.nSet[i].nodeId<<endl;
	}
	cout<<endl<<endl<<"-------------------------------LSet--------------------------"<<endl<<endl;
	for(int i=0;i<4;i++)
	{
		if(t.lSet[i].nodeId!="_")
		cout<<t.lSet[i].ip<<" "<<t.lSet[i].port<<" "<<t.lSet[i].nodeId<<endl;
	}
	cout<<endl<<endl<<"-------------------------------RTable---------------------------"<<endl<<endl;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<16;j++)
		{
			if(t.rTable[i][j].nodeId!="_"&&t.rTable[i][j].nodeId!=node.nodeId)
			cout<<t.rTable[i][j].ip<<" "<<t.rTable[i][j].port<<" "<<t.rTable[i][j].nodeId<<endl;
		}
	}
}		
void convert()
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	for(int i=0;i<16;i++)
	{
		if(i>9)
		{
			h.insert(make_pair('a'+(i-10),i));
		}
		else
		{
			h.insert(make_pair('0'+i,i));
		}
	}
}
string getIp()
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	struct ifaddrs * ifAddrStruct=NULL;
	struct ifaddrs * ifa=NULL;
	void * tmpAddrPtr=NULL;
	string ip;
	getifaddrs(&ifAddrStruct);
	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
	{
        	if (!ifa->ifa_addr)
		{
            		continue;
        	}
        	if (ifa->ifa_addr->sa_family == AF_INET)
		{ 
            		tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            		char addressBuffer[INET_ADDRSTRLEN];
            		inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			if(ifa->ifa_name[0] == 'e')
			{
				ip = string(addressBuffer);
				if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
				return ip;
			}
			else if(ifa->ifa_name[0] == 'w')
			{
				ip = string(addressBuffer);
				if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
				return ip;
			}
        	}
    	}
	return ip;
}
void sendTo(string data,string i,string p)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	struct sockaddr_in serv_addr1;
	int argc=3,sockfd1;
	char *argv[3]={"Self"};
	argv[1]=(char *)malloc(i.length());
	strcpy(argv[1],i.c_str());
	argv[2]=(char *)malloc(p.length());
	strcpy(argv[2],p.c_str());
	
	if(argc != 3)
	{
		printf("\n Usage: %s <ip of server> \n",argv[0]);
		return ;
	} 
	if((sockfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Error : Could not create socket \n");
		return ;
	} 
	memset(&serv_addr1, '0', sizeof(serv_addr1)); 
	serv_addr1.sin_family = AF_INET;
	int port=stoi(p);
	serv_addr1.sin_port = htons(port); 
	if(inet_pton(AF_INET, argv[1], &serv_addr1.sin_addr)<=0)
	{
		printf("\ninet_pton error occured\n");
		return;
	} 
	if( connect(sockfd1, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		return;
	} 
	memset(buffer, 0, sizeof(buffer));
	strcpy(buffer,data.c_str());
	send(sockfd1,buffer,sizeof(buffer),0);
	close(sockfd1);
}
string nodeIdCall(string port,string ip)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	unsigned char *buff;
	char tt[3];
	int size=port.length();
	size+=ip.length();
	buff=(unsigned char *)malloc(size+1);
	string g=port+ip;	
	for(int i=0;i<size;i++)
	{
		buff[i]=(unsigned char)g[i];
	}
	buff[size]='\0';
	const unsigned char *t=buff;
	char unsigned result[SHA_DIGEST_LENGTH];
	SHA1(t,size, result);
	string kk="";
	for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		sprintf(tt,"%02x",result[i]);
		string k(tt);
		kk+=k;
	}
	return kk.substr(0,8);		
}
string hashC(string key)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	unsigned char *buff;
	char tt[3];
	int size=key.length();
	buff=(unsigned char *)malloc(size+1);
	string g=key;	
	for(int i=0;i<size;i++)
	{
		buff[i]=(unsigned char)g[i];
	}
	buff[size]='\0';
	const unsigned char *t=buff;
	char unsigned result[SHA_DIGEST_LENGTH];
	SHA1(t,size, result);
	string kk="";
	for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		sprintf(tt,"%02x",result[i]);
		string k(tt);
		kk+=k;
	}
	return kk.substr(0,8);		
}
void shareTable()
{
		signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

		vector<addr> v;
		set<string> s;
		string msg="update+"+get(node);
		for(int i=0;i<4;i++)
		{
			if(node.lSet[i].nodeId != "_"&&node.lSet[i].nodeId != node.nodeId)
			{
				set<string>::iterator it=s.find(node.lSet[i].nodeId);
				if(it==s.end())
				{
					v.push_back(node.lSet[i]);
					s.insert(node.lSet[i].nodeId);
				}
			}
		}
		for(int i=0;i<4;i++)
		{
			if(node.nSet[i].nodeId != "_"&&node.nSet[i].nodeId != node.nodeId)
			{
				set<string>::iterator it=s.find(node.nSet[i].nodeId);
				if(it==s.end())
				{
					v.push_back(node.nSet[i]);
					s.insert(node.nSet[i].nodeId);
				}
			}
		}
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<16;j++)
			{
				if(node.rTable[i][j].nodeId != "_"&&node.rTable[i][j].nodeId != node.nodeId)
				{
					set<string>::iterator it=s.find(node.rTable[i][j].nodeId);
					if(it==s.end())
					{
						v.push_back(node.rTable[i][j]);
						s.insert(node.rTable[i][j].nodeId);
					}
				}
			}	
		}

		for(int i=0;i<v.size();i++)
		{
			sendTo(msg,v[i].ip,v[i].port);
			cout<<"\nRTable share to :"<<node.nodeId<<" -> "<<v[i].nodeId<<endl;
		}
}
bool isLeaf(string id,addr &temp)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	int p=-2;
	long long m;
	if(node.lSet[0].nodeId=="_")
	{
		return false;
	}
	long long l=stoll(node.lSet[0].nodeId,0,16);
	long long h;
	for(int i=0;i<4&&node.lSet[i].nodeId!="_";i++)
	{
		h=stoll(node.lSet[i].nodeId,0,16);
	}
	if(stoll(id,0,16)>=l&&stoll(id,0,16)<=h)
	{
		m=abs(stoll(id,0,16)-stoll(node.nodeId,0,16));
		for(int i=0;i<4&&node.lSet[i].nodeId != "_";i++)
		{
			long long t=abs(stoll(id,0,16)-stoll(node.lSet[i].nodeId,0,16));
			if(t<m)			
			{
				m=t;
				p=i;
			}
		}
		if(p!=-2)
		{
			temp=node.lSet[p];
		}
		else
		{
			temp.port=node.port;
			temp.ip=node.ip;
			temp.nodeId=node.nodeId;
		}
		return true;
	}
return false;
}
addr path(string id)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);
	
	addr temp;
	if(isLeaf(id,temp))
	{
		return temp;
	}
	else
	{
		int i;
		int p;
		for(i=0;i<8&&node.nodeId[i]==id[i];i++)
		{
		}
		if(node.rTable[i][h[id[i]]].nodeId != "_")
		{
			return node.rTable[i][h[id[i]]];
		}
		else
		{
			long long m=INT_MAX,t;
			for(int j=0;j<16;j++)
			{
				if(node.rTable[i][j].nodeId!="_")
				{
					t= abs(stoll(id,0,16)-stoll(node.rTable[i][j].nodeId,0,16));
					if(t<m)	
					{				
						p=j;
						m=t;
					}
				}
			}
		}
	return node.rTable[i][p];
	}
}
void setRTable(table temp)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	string n=temp.nodeId;
	int i;
	for(i=0;i<8&&n[i]==node.nodeId[i];i++);
	for(int j=0;j<16;j++)
	{
		if((node.rTable[i][j].nodeId =="_"||node.rTable[i][j].nodeId == node.nodeId) && temp.rTable[i][j].nodeId != "_" && temp.rTable[i][j].nodeId != node.rTable[i][j].nodeId)
		{
			node.rTable[i][j]=temp.rTable[i][j];
		}
	}
}
void setLeaf(table temp)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	vector<addr> l,h;
	addr tt;
	tt.ip=temp.ip;
	tt.nodeId=temp.nodeId;
	tt.port=temp.port;
	if(stoll(tt.nodeId, 0, 16) < stoll(node.nodeId, 0, 16))
		l.push_back(tt);
	else
		h.push_back(tt);
	set<string> s;
	s.insert(tt.nodeId);
	for(int i=0;i<4&&temp.lSet[i].nodeId!="_";i++)
	{
		set<string>::iterator it=s.find(temp.lSet[i].nodeId);
		if(temp.lSet[i].nodeId!=node.nodeId&&it==s.end())
		{
			s.insert(temp.lSet[i].nodeId);
			if(stoll(temp.lSet[i].nodeId, 0, 16) < stoll(node.nodeId, 0, 16))
				l.push_back(temp.lSet[i]);
			else
				h.push_back(temp.lSet[i]);
		}
	}
	for(int i=0;i<4&&node.lSet[i].nodeId!="_";i++)
	{
		set<string>::iterator it=s.find(node.lSet[i].nodeId);
		if(node.lSet[i].nodeId!=node.nodeId&&it==s.end())
		{
			s.insert(node.lSet[i].nodeId);
			if(stoll(node.lSet[i].nodeId, 0, 16) < stoll(node.nodeId, 0, 16))
				l.push_back(node.lSet[i]);
			else
				h.push_back(node.lSet[i]);
		}
	}
	vector<addr>::iterator it;
	int c=0;
	for(it=l.begin();it!=l.end()&&c<2;it++,c++)
	node.lSet[c]=(*it);
	for(it=h.begin();it!=h.end()&&c<4;it++,c++)
	node.lSet[c]=(*it);
}
void putKey(string key,string val, addr t)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	string kk=hashC(key);
	cout<<"\n\nKey(hash) : "<<kk<<" Value : "<<val<<endl;
	addr temp=path(kk);
	if(node.nodeId == temp.nodeId)
	{
		cout<<"\nKey store on my Node.\n";
		mytable.insert(make_pair(kk,val));
		mytable2.insert(make_pair(kk,t));
		keyhashtable.insert(make_pair(kk,key));
		cout<<t.nodeId<<endl;
	
	}
	else
	{
		string msg="setkey+"+key+"+"+val+"+" +node.nodeId + "+" + node.ip + "+" + node.port ;
		cout<<"Key send to "<<temp.nodeId<<endl;
		sendTo(msg,temp.ip,temp.port);
	}
	
}
void getKey(string key,string ip,string port)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	string kk=hashC(key);
	addr temp=path(kk);
	if(node.nodeId == temp.nodeId)
	{
		cout<<"\nKey present on my Node.\n";
		//cout<<"Key : "<<key<<" Value : "<<mytable[key]<<endl;
		auto it=mytable.find(kk);
		if(it!=mytable.end()){
		string msg="found+"+key+"+"+mytable[kk];
		sendTo(msg,ip,port);	
		}
		else
		{
			cout<<"Fail to retrive.\n";
		}
	}
	else
	{
		string msg="getkey+"+key+"+"+ip+"+"+port;
		sendTo(msg,temp.ip,temp.port);
	}
}

void checklr(string id)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	int pos=-1;
	addr temp;
	for(int i=0;i<4;i++)
	{
		if(node.lSet[i].nodeId == id)
		{
			node.lSet[i].ip = "_";
			node.lSet[i].port = "_";
			node.lSet[i].nodeId = "_";
			pos = i;
		}
	}
	for(int i=0;i<4;i++)
	{
		if(node.nSet[i].nodeId == id)
		{
			node.nSet[i].ip = "_";
			node.nSet[i].port = "_";
			node.nSet[i].nodeId = "_";
		}
	}

	for(int i=0;i<8;i++)
	{
		for(int j=0;j<16 ; j++)
		{
			if(node.rTable[i][j].nodeId == id)
			{
				node.rTable[i][j].ip = "_";
				node.rTable[i][j].port = "_";
				node.rTable[i][j].nodeId = "_";
			}

		}
	}
	bool flag = false;
	int i;
	if(pos != -1 && pos != 3)
	{
		if(node.lSet[pos+1].nodeId != "_")
		{
			for( i=pos+1;i<3;i++)
			{
				if(node.lSet[i].nodeId == "_")
				{
					flag = true;
					break;
				}
				else
				{
					temp = node.lSet[i];
					node.lSet[i] = node.lSet[i-1];
					node.lSet[i-1]=temp;
				}
			}
			if(flag == true)
			{
				node.lSet[i-1].ip = "_";
				node.lSet[i-1].port = "_";
				node.lSet[i-1].nodeId = "_";
			}
		}
	}

	addr tem;
	tem.ip=node.ip;
	tem.nodeId=node.nodeId;
	tem.port=node.port;
	for(int i=0;i<8;i++)
	{
		if(node.rTable[i][h[node.nodeId[i]]].nodeId == "_")
			node.rTable[i][h[node.nodeId[i]]]=tem;
	}


}


void *connect1(void *arg)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	int connfd =*((int*)(&arg));
	memset(buffer, 0, sizeof(buffer));
	recv(connfd,buffer,sizeof(buffer),0);
	string msg(buffer);
	vector<string> rev= filter(msg);
	if(rev[0]=="join1")
	{
		string id=rev[1],ip=rev[2],port=rev[3];
		addr temp=path(id);
		if(node.nodeId == temp.nodeId)
		{
			//cout<<"NO :P"<<endl;
			string route="";
			route+="route+1+1+1+"; // buddy+terminating+hop
			route=route+get(node);
			sendTo(route,ip,port);
		}
		else
		{
			string route="";
			route+="route+1+0+1+"; // buddy+terminating+hop
			route=route+get(node);
			sendTo(route,ip,port);
			string t="join2+2+"+id+"+"+ip+"+"+port;
			sendTo(t,temp.ip,temp.port);
		}
	}
	else if(rev[0]=="route")
	{
		//cout<<msg<<endl;
		table temp;
		setTo(temp,msg);
		int x=msg[8]-'0';
		setLeaf(temp);
		setRTable(temp);
		if(x==1)
		{
			shareTable();
		}
		
	}
	else if(rev[0]=="join2")
	{
		string hop=rev[1],id=rev[2],ip=rev[3],port=rev[4];
		addr temp=path(id);
		if(node.nodeId == temp.nodeId)
		{
			//cout<<"NO :P"<<endl;
			string route="";
			route+="route+0+1+"+hop+"+"; // buddy+terminating+hop
			route=route+get(node);
			sendTo(route,ip,port);
		}
		else
		{
			string route="";
			route+="route+0+0+"+hop+"+"; // buddy+terminating+hop
			route=route+get(node);
			sendTo(route,ip,port);
			string t="join2+2+"+id+"+"+ip+"+"+port;
			sendTo(t,temp.ip,temp.port);
		}
		
	}
	else if(rev[0]=="update")
	{
		table temp;
		setToU(temp,msg);
		setLeaf(temp);
		setRTable(temp);
	}
	else if(rev[0]=="setkey")
	{
		string key=rev[1];
		string val=rev[2];
		string id = rev[3];
		string ip  = rev[4];
		string port = rev[5];
		addr temp;
		temp.nodeId= id;
		temp.ip  = ip;
		temp.port = port;
		putKey(key,val,temp);
	}
	else if(rev[0]=="found")
	{
		cout<<rev[1]<<" -> "<<rev[2]<<endl;
	}
	else if(rev[0]=="getkey")
	{
		getKey(rev[1],rev[2],rev[3]);
	}
	else if(rev[0]=="shutdown")
	{
		close(connfd);
		exit(0);
	}
	else if(rev[0] == "quit")
	{
		string id = rev[1];
		checklr(id);

	}
	else if(rev[0] == "putkeywhenquit")
	{
		string key=rev[1];
		string val=rev[2];
		string id = rev[3];
		string ip  = rev[4];
		string port = rev[5];
		addr temp;
		temp.nodeId= id;
		temp.ip  = ip;
		temp.port = port;
		putKey(key,val,temp);
	}
	close(connfd);	
}
void *create_server(void *arg)
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	int port=stoi(node.port);
	int listenfd = 0;
	struct sockaddr_in serv_addr; 
   	listenfd = socket(AF_INET, SOCK_STREAM, 0);
   	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port); 
	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
	listen(listenfd, 10); 
	for(int i=0;i<4;i++)
	{
		node.nSet[i].nodeId="_";
		node.nSet[i].ip="_";
		node.nSet[i].port="_";
		node.lSet[i].nodeId="_";
		node.lSet[i].ip="_";
		node.lSet[i].port="_";
	}
	addr temp;
	temp.ip=node.ip;
	temp.nodeId=node.nodeId;
	temp.port=node.port;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<16;j++)
		{
			node.rTable[i][j].nodeId="_";
			node.rTable[i][j].ip="_";
			node.rTable[i][j].port="_";
		}
		node.rTable[i][h[node.nodeId[i]]]=temp;
	}
	/*for(int i=0;i<4;i++)
	{
		for(int j=0;j<16;j++)
		{
			cout<<j<<" "<<node.rTable[i][j].nodeId<<" "<<node.rTable[i][j].port<<" "<<node.rTable[i][j].ip<<endl;
		}
	}*/
	while(1)
	{
		int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
		if(connfd==-1)
		{
			cout<<endl<<"Error to connect\n";
		} 
		pthread_create(&thread1[lo],NULL,connect1,(void *)connfd);
		lo++;
	}
}

void shutdown_fn()
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	vector<addr> v;
		set<string> s;
		string msg="shutdown+";
		for(int i=0;i<4;i++)
		{
			if(node.lSet[i].nodeId != "_"&&node.lSet[i].nodeId != node.nodeId)
			{
				set<string>::iterator it=s.find(node.lSet[i].nodeId);
				if(it==s.end())
				{
					v.push_back(node.lSet[i]);
					s.insert(node.lSet[i].nodeId);
				}
			}
		}
		for(int i=0;i<4;i++)
		{
			if(node.nSet[i].nodeId != "_"&&node.nSet[i].nodeId != node.nodeId)
			{
				set<string>::iterator it=s.find(node.nSet[i].nodeId);
				if(it==s.end())
				{
					v.push_back(node.nSet[i]);
					s.insert(node.nSet[i].nodeId);
				}
			}
		}
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<16;j++)
			{
				if(node.rTable[i][j].nodeId != "_"&&node.rTable[i][j].nodeId != node.nodeId)
				{
					set<string>::iterator it=s.find(node.rTable[i][j].nodeId);
					if(it==s.end())
					{
						v.push_back(node.rTable[i][j]);
						s.insert(node.rTable[i][j].nodeId);
					}
				}
			}	
		}

		for(int i=0;i<v.size();i++)
		{
			sendTo(msg,v[i].ip,v[i].port);
			// cout<<"\nRTable share to :"<<node.nodeId<<" -> "<<v[i].nodeId<<endl;
		}

}

void quit_fn(){
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);


vector<addr> v;
		set<string> s;
		string msg="quit+"+node.nodeId +"+";
		for(int i=0;i<4;i++)
		{
			if(node.lSet[i].nodeId != "_"&&node.lSet[i].nodeId != node.nodeId)
			{
				set<string>::iterator it=s.find(node.lSet[i].nodeId);
				if(it==s.end())
				{
					v.push_back(node.lSet[i]);
					s.insert(node.lSet[i].nodeId);
				}
			}
		}
		for(int i=0;i<4;i++)
		{
			if(node.nSet[i].nodeId != "_"&&node.nSet[i].nodeId != node.nodeId)
			{
				set<string>::iterator it=s.find(node.nSet[i].nodeId);
				if(it==s.end())
				{
					v.push_back(node.nSet[i]);
					s.insert(node.nSet[i].nodeId);
				}
			}
		}
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<16;j++)
			{
				if(node.rTable[i][j].nodeId != "_"&&node.rTable[i][j].nodeId != node.nodeId)
				{
					set<string>::iterator it=s.find(node.rTable[i][j].nodeId);
					if(it==s.end())
					{
						v.push_back(node.rTable[i][j]);
						s.insert(node.rTable[i][j].nodeId);
					}
				}
			}	
		}

		for(int i=0;i<v.size();i++)
		{
			sendTo(msg,v[i].ip,v[i].port);
			// cout<<"\nRTable share to :"<<node.nodeId<<" -> "<<v[i].nodeId<<endl;
		}



}

addr retrive()
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	for(int i=0;i<4;i++)
	{
		if(node.lSet[i].nodeId != "_")
			return node.lSet[i];
	}
	for(int i=0;i<4;i++)
	{
		if(node.nSet[i].nodeId != "_")
			return node.nSet[i];
	}
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<16;j++)
		{
			if(node.rTable[i][j].nodeId != "_" && node.rTable[i][j].nodeId != node.nodeId)
				return node.rTable[i][j];
		}
	}
	exit(0);
}

void remtable()//---------------removing all 
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	//string msg = "putkeywhenquit+";
	for(auto it = mytable.begin(); it != mytable.end() ;it++)
	{
		string msg = "putkeywhenquit+";
		string k = it->first;
		cout<<"string k = "<<k<<endl;
		string val  = it->second;
		cout<<"value = "<<val<<endl;
		addr temp = mytable2[k];
		string key = keyhashtable[k];
		cout<<"string key = "<<key<<endl;
		if(temp.nodeId != node.nodeId)
			msg = msg+ key + "+" + val + "+" + temp.nodeId + "+" + temp.ip + "+" + temp.port;
		else{
			temp = retrive();
			msg = msg+ key + "+" + val + "+" + temp.nodeId + "+" + temp.ip + "+" + temp.port;
		}
		sendTo(msg,temp.ip, temp.port);
		sleep(1);
	}
}

void handle_sigint(int sig)
{
	quit_fn();
	remtable();
	exit(0);
}

int main()
{
	signal(SIGINT, handle_sigint);
	signal(SIGHUP, handle_sigint);
	signal(SIGQUIT, handle_sigint); 
	signal(SIGILL, handle_sigint);
	signal(SIGTRAP, handle_sigint);
	signal(SIGABRT, handle_sigint);

	pthread_t t1;
	string comm;
	convert();
	while(1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGHUP, handle_sigint);
		signal(SIGQUIT, handle_sigint); 
		signal(SIGILL, handle_sigint);
		signal(SIGTRAP, handle_sigint);
		signal(SIGABRT, handle_sigint);
		getline(cin,comm);
		stringstream str(comm);
		string ss;
		str >> ss;
		if(ss=="port")
		{
			str >> ss;
			node.port=ss;
			string y=getIp();
			if(y!="")
			node.ip=y;
			else
			node.ip="127.0.0.1";
			node.nodeId=nodeIdCall(node.port,node.ip);
			cout<<"Ip :"<<node.ip<<endl;
			cout<<"Port :"<<node.port<<endl;
			cout<<"....Node Id generated after SHA hashing.....\n";
			cout<<"Node Id :"<<node.nodeId<<endl<<endl;	
			pthread_create(&t1,NULL,create_server,NULL);
		}
		else if(ss=="join")
		{
			string nodeId="join1+"+node.nodeId+"+"+node.ip+"+"+node.port;
			str >> ss;
			string ip=ss;
			str >> ss;
			string port=ss;
			sendTo(nodeId,ip,port);
		}
		else if(ss=="put")
		{
			addr temp;
			str >> ss;
			string key=ss;
			str >> ss;
			string val=ss;
			temp.nodeId = node.nodeId;
			temp.ip = node.ip;
			temp.port = node.port;
			putKey(key,val,temp);
		}
		else if(ss=="get")
		{
			str >> ss;
			getKey(ss,node.ip,node.port); 
		}
		else if(ss=="print")
		print(node);
		else if(ss=="shutdown")
		{
			shutdown_fn();
			exit(0);
		}
		else if(ss == "quit")
		{
			quit_fn();
			remtable();
			exit(0);
		}
	}
}
