#include<bits/stdc++.h>
#include <fstream>
using namespace std;
float dist(vector<int> &node, vector<float> &neuron){
    int var=0;
    for(int i=0;i<3;i++){
        var+=(node[i]-neuron[i])*(node[i]-neuron[i]);
    }
    return sqrt(var);
}
pair<int,int> winning_neuron(vector<int> &node,vector<vector<vector<float>>> &grid){
    float curr_min_dist=INT_MAX;
    pair<int,int> loc_neuron={-1,-1};
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            int d=dist(node,grid[i][j]);
            if(d<curr_min_dist){
                loc_neuron={i,j};
                curr_min_dist=d;
            }
        }
    }
    return loc_neuron;
}
void update_grid(pair<int,int>loc_neuron,vector<vector<vector<float>>> &grid,float l_r){
    int x=loc_neuron.first;
    int y=loc_neuron.second;
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            if(i==x&&j==y){
                continue;
            }
            for(int k=0;k<3;k++){
                int d=(x-i)*(x-i)+(y-j)*(y-j);
                d=d+2;
                double t=pow(1.15,d/3);
                grid[i][j][k]+=l_r*(grid[x][y][k]-grid[i][j][k])/t;
                grid[i][j][k]=max(min(255,int(grid[i][j][k])),0);
            }
        }
    }
}
int main(){
    vector<vector<int>> dataset(10000,vector<int>(3,0));
    for(int i=0;i<dataset.size();i++){
        if(i<7000){
            for(int j=0;j<dataset[0].size();j++){
            dataset[i][j]=rand()%200+56;
            }
        }
        else{
            for(int j=0;j<dataset[0].size();j++){
            dataset[i][j]=rand()%256;
            }
        }
        
    }
    vector<vector<vector<float>>> grid(100,vector<vector<float>>(100,vector<float>(3,0)));
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            for(int k=0;k<3;k++){
                grid[i][j][k]=rand()%200+56;
            }
        }
    }
    for(int j=0;j<10;j++){
    for(int i=0;i<dataset.size();i++){
        pair<int,int> loc_neuron=winning_neuron(dataset[i],grid);
        float l_r=0.1;
        l_r=pow(0.9,i/10);
        update_grid(loc_neuron,grid,l_r);
    }
    }
    fstream my_file;
	my_file.open("my_file.csv", ios::out);
	if (!my_file) {
		cout << "File not created!";
	}
	else {
		cout << "File created successfully!";
		
	}
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            // cout << "[";
            for(int k=0;k<3;k++){
                my_file << int(grid[i][j][k])<<",";
            }
            // cout << "] ";
        }
        my_file <<endl;
    }
    my_file.close(); 
    return 0;
}