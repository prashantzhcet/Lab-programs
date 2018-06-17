#include <bits/stdc++.h>
using namespace std;

int ans[1000][100]={0};
int k=0;

class Graph{
	int v1;
	list<int> *adj;
	
public:
	Graph(int v){
	    v1=v;
	    adj = new list<int>[v1];
	}
	void addEdge(int a, int b);
	void init(int start,int d,int v);
	void spanning(int , int , bool [], int [], int & , int );
};

void Graph :: addEdge(int a, int b){
	adj[a].push_back(b);
	adj[b].push_back(a);
}

void Graph :: init(int s, int d ,int v){
	bool visited[v];
	int *span = new int[v]; 
	int index = 0; 
	for (int i=0;i<v;i++){
		visited[i] = false;
	}
	spanning(s, d, visited, span, index,v);
}


void Graph ::spanning(int source, int d, bool visited[],int span[], int &index , int v){
	visited[source] = true;
	span[index] = source;
	index++;

	if(source==d){ // this loop is only to print all paths from 
	    if(index==v){ 
		    for (int i = 0; i<index; i++){
		    	ans[k][i]=span[i];
	    	}
	    	k++;
	    }	
	}
	else{
		list<int>::iterator itr;
		for(itr=adj[source].begin();itr!=adj[source].end();itr++){
			if(!visited[*itr])
				spanning(*itr,d,visited,span,index,v);
		}
	}
	index--;
	visited[vr]=false;
}

int main()
{
	int v,e,x,y;
	cout<<"Enter total vertices in the Graph:\n";
	cin>>v;
	Graph g(v);
	e=0;
	cout<<"Enter the vertices for making an edge between them:\n";
	while(1){
		cin>>x>>y;
		g.addEdge(x,y);
        	e++;
		cout<<"want to enter more?(y/n)\n";
		char choice;
		cin>>choice;
		if(choice=='y'){
			continue;
		}
		else{
			break;
		}
	}
    
	for(int i=0;i<v;i++){
	    for(int j=0;j<v && i!=j ;j++){
	        g.init(i,j,v);
	    }
	}

	
	int c=0,p=0;
        
	for(int i=0;i<k-1;i++){
		for(int j=i+1;j<v;j++){
			for(int l=0;l<v;l++){
				if(ans[i][l]==ans[j][l]){
					c++;
				}
			}
			
			if(c==v){
				for(int l=0;l<v;l++){
					ans[j][l]=-1;
				}
			}
			c=0;
		}
	}
	
        c=0;
	for(int i=0;i<k;i++){
		for(int j=i+1;j>=0;j--){
			for(int l=0;l<v;l++){
				if(ans[i][l]!=-1 && ans[j][l]!=-1){
					if(ans[i][l]==ans[j][v-1-l]){
						c++;
					}
				}
			}
			if(c==v){
				for(int l=0;l<v;l++){
					ans[j][l]=-1;
				}
			}
			c=0;
		}
	}
    int flag;
	for(int i=0;i<k;i++){
		flag=0;
	    for(int j=0;j<v;j++){
	    	if(ans[i][j]!=-1){
	        	cout<<ans[i][j]<<" ";
	        	flag=1;
	    	}
	    }
	    if(flag==1)
	    cout<<"\n";
	}
		
	return 0;
}
