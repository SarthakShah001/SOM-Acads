#include<bits/stdc++.h>
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
                double t=pow(2,d);
                grid[i][j][k]+=4.5*(grid[x][y][k]-grid[i][j][k])/d;
                
            }
        }
    }
}
int main(){
    vector<vector<int>> dataset(10000,vector<int>(3,0));
    for(int i=0;i<dataset.size();i++){
        for(int j=0;j<dataset[0].size();j++){
            dataset[i][j]=rand()%256;
        }
    }
    vector<vector<vector<float>>> grid(100,vector<vector<float>>(100,vector<float>(3,0)));
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            for(int k=0;k<3;k++){
                grid[i][j][k]=rand()%256;
            }
        }
    }
    for(int i=0;i<dataset.size();i++){
        pair<int,int> loc_neuron=winning_neuron(dataset[i],grid);
        float l_r=0.1;
        update_grid(loc_neuron,grid,l_r);
        if(i>5000){
            l_r=0.01;
        }

    }
    cout << endl;
    for(int i=0;i<100;i++){
        for(int j=90;j<98;j++){
            cout << "[";
            for(int k=0;k<3;k++){
                cout << int(grid[i][j][k])<<",";
            }
            cout << "] ";
        }
        cout <<endl;
    }
    return 0;
}