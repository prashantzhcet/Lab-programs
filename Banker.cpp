#include <iostream>
using namespace std;

class Banker{

	int allocation[100][100],max[100][100],need[100][100],available[100];
	int process_number,total_processes,total_resources,request[100];

	public:
		Banker(){
			cout<<"\tBanker's Algorithm:\n\n";
			cout<<"Enter Total number of Processes:\n";
			cin>>total_processes;
			cout<<"Enter the total Resources:\n";
			cin>>total_resources;
			allocation_table();
			requesting_instances();

		}
		void allocation_table();
		void maximum_table();
		void need_table();
		void available_table();
		int checking_safe_sequence();
		void requesting_instances();
		int request_resources();
};

int Banker::request_resources(){
	cout<<"Enter the process number: \n P";
	cin>>process_number;
	cout<<"Enter the instances of the resources respectively:\n";
	for(int i=1;i<=total_resources;i++){
		cin>>request[i];
	}
	//Algo starts here..........................
	int i,flag=0;
	for(i=1;i<=total_resources;i++){
		if(request[i]>need[process_number][i])
		{
			flag=1;
			cout<<request[i]<<"  "<<need[process_number][i]<<" ";
			cout<<"The process has exceeded its maximum need.";
			return 0;
		}
	}
	if(flag==0){
		for(i=1;i<=total_resources;i++){
			if(request[i]>available[i]){
				flag=1;
				cout<<"The process has exceeded its maximum need.";
				return 0;
			}
		}
	}
		for(i=1;i<=total_resources;i++){
			available[i]+=-request[i];
			allocation[process_number][i]+=request[i];
			need[process_number][i]+=-request[i];	
		}	
		
		return 1;	
}


void Banker::requesting_instances(){
	while(1){

		cout<<"Any process need to further request the resources:?(y/n)\n";
		char ch;
		cin>>ch;
		if(ch=='n'){
			return ;
		}
		else if(ch=='y'){
			if(request_resources())
			checking_safe_sequence();
		}
		else{
			cout<<"Enter valid choice:\n";
		}
	}
}


void Banker::allocation_table(){
	cout<<"Enter the Allocation Table:\n";
	int i,j;
	for(i=1;i<=total_resources;i++){
		cout<<"\tR"<<i;
	}
	cout<<"\n";
	for(i=1;i<=total_processes;i++){
		cout<<"P"<<i<<"\t";
		for(j=1;j<=total_resources;j++){
			cin>>allocation[i][j];
		}
		cout<<"\n";
	}
	maximum_table();
}

void Banker::maximum_table(){
	cout<<"Enter the Maximum Table:\n";
	int i,j;
	for(i=1;i<=total_resources;i++){
		cout<<"\tR"<<i;
	}
	cout<<"\n";
	for(i=1;i<=total_processes;i++){
		cout<<"P"<<i<<"\t";
		for(j=1;j<=total_resources;j++){
			cin>>max[i][j];
		}
		cout<<"\n";
	}
	available_table();
} 


void Banker::available_table(){
	cout<<"Available Instances of the Resources respectively:\n";
	for(int i=1;i<=total_resources;i++){
		cout<<"R"<<i<<" ";
		cin>>available[i];
	}
	need_table();
}

void Banker::need_table(){
	cout<<"Need Table:\n";
	int i,j,flag=0;
	for(i=1;i<=total_resources;i++){
		cout<<"\tR"<<i;
	}
	cout<<"\n";
	for(i=1;i<=total_processes;i++){
		for(j=1;j<=total_resources;j++){
			if(max[i][j]-allocation[i][j]>=0)
			need[i][j]=max[i][j]-allocation[i][j];
		    else{
			cout<<"\nThe SYSTEM IS NOT IN SAFE STATE AND THEREFORE BANKING ALGORITHM FAILS......\n\n";
            flag=1;
			break;
		//	Banker b;
		}
		}
		if(flag==1){
			break;
		}
	}
	if(flag==0){

	for(i=1;i<=total_processes;i++){
		cout<<"P"<<i<<"\t";
		for(j=1;j<=total_resources;j++){
			cout<<need[i][j]<<"\t";
		}
		cout<<"\n";
	}
	checking_safe_sequence();
}
else {
	allocation_table();
}
}

int Banker::checking_safe_sequence(){
	int counter=0,i,j;
	
	int sequence[total_processes];// for completed processes..........

	int work[100];
	//Step 1:Initialise the finish_flag and work;
	int flag[total_processes]={0};
	for(i=1;i<=total_resources;i++){
		work[i]=available[i];
	}

	//step 2:if any such i found.............
    cout<<"Finally Processes are allocated in the manner::\n";
    cout<<"Processes\t R1  R2  R3\n";
	while(counter<total_processes){
            bool complete=false;
			for(i=1;i<=total_processes;i++){
				if(flag[i]==0){
					for(j=1;j<=total_resources;j++){
						if(need[i][j] >work[j]){
						    break;
						}
					}
					if(j==total_resources+1){
						cout<<"P"<<i<<"\t\t ";
						for(int k=1;k<=total_resources;k++){
							work[k]=work[k]+allocation[i][k];
							cout<<work[k]<<"    ";
						}
						cout<<"\n";
						counter++;
						sequence[counter]=i;
						flag[i]=1;
						complete=true;
					}
				}
			}
			if(complete==false){
				cout<<"\nSYSTEM IS NOT IN SAFE STATE:\n";
				return 0;
			}
	}
	cout<<"\nSYSTEM IS IN SAFE STATE:\n";
	for(i=1;i<=total_processes-1;i++){
		cout<<sequence[i]<<"->";
	}
	cout<<sequence[total_processes]<<endl;
	/*for(i=1;i<=total_resources;i++){
		available[i]=work[i];	
	}*/
	return 1;
}

int main()
{	
	Banker b;
	return 0;
}