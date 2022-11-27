#include<bits/stdc++.h>
#include <fstream>
using namespace std;
float dist(vector<int> &node, vector<float> &neuron){
    int var=0;
    for(int i=0;i<node.size();i++){
        var+=(node[i]-neuron[i])*(node[i]-neuron[i]);
    }
    return sqrt(var);
}
pair<int,int> winning_neuron(vector<int> &node,vector<vector<vector<float>>> &grid){
    float curr_min_dist=INT_MAX;
    pair<int,int> loc_neuron={-1,-1};
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
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
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            for(int k=0;k<grid[0][0].size();k++){
                int d=(x-i)*(x-i)+(y-j)*(y-j);
                d=d+2;
                double t=pow(1.15,d/3);
                grid[i][j][k]+=l_r*(grid[x][y][k]-grid[i][j][k])/t;
                grid[i][j][k]=max(min(255,int(grid[i][j][k])),0);
            }
        }
    }
}
void SOM(vector<vector<int>> dataset,int initial_l_r,int no_of_itr,int grid_height,int grid_width,int feature_size,int feature_max,int feature_min){
    vector<vector<vector<float>>> grid(grid_height,vector<vector<float>>(grid_width,vector<float>(feature_size,0)));
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            for(int k=0;k<grid[0][0].size();k++){
                grid[i][j][k]=rand()%(feature_max-feature_min)+feature_min;
            }
        }
    }
for(int j=0;j<no_of_itr;j++){
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
		cout << "SOM was not able create the file for output!";
	}
	else {
		cout << "SOM finished successfully, you can check output in my_file.csv"<<endl;
		cout <<"Output is in the format of grid where every neuron's feature are listed in a row."<<endl;
	}
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            // cout << "[";
            for(int k=0;k<grid[0][0].size();k++){
                my_file << int(grid[i][j][k])<<",";
            }
            // cout << "] ";
        }
        my_file <<endl;
    }
    my_file.close(); 
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
    int no_of_itr=0;
    float l_r=0.9;
    int grid_length=100;
    int grid_width=100;
    int feature_size=3;
    int feature_max=256;
    int feature_min=56;
    SOM(dataset,l_r,no_of_itr,grid_length,grid_width,feature_size,feature_max,feature_min);
    return 0;
}