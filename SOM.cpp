#include<bits/stdc++.h>
#include <fstream>
using namespace std;
float dist(vector<int> &node, vector<float> &neuron){
    int var=0;
    for(int i=0;i<neuron.size();i++){
        // calculating similarity based on features
        var+=(node[i]-neuron[i])*(node[i]-neuron[i]);
    }
    return sqrt(var);
}
pair<int,int> winning_neuron(vector<int> &node,vector<vector<vector<float>>> &grid){
    float curr_min_dist=INT_MAX;
    pair<int,int> loc_neuron={-1,-1};
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            // calculating similarity of dataset point and grid features.
            int d=dist(node,grid[i][j]);
            if(d<curr_min_dist){
                // storing the current winner properties
                loc_neuron={i,j};
                curr_min_dist=d;
            }
        }
    }
    return loc_neuron;
}
void update_grid(pair<int,int>loc_neuron,vector<vector<vector<float>>> &grid,float l_r,float feature_max,float feature_min){
    int x=loc_neuron.first;
    int y=loc_neuron.second;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            for(int k=0;k<grid[0][0].size();k++){
                // calculating euclidean distance b/w two points in grid
                int d=(x-i)*(x-i)+(y-j)*(y-j);
                d=d+2;
                double t=pow(1.15,d/3);
                // updating the grid points
                grid[i][j][k]+=l_r*(grid[x][y][k]-grid[i][j][k])/t;
                //normalising the grid points
                grid[i][j][k]=max(min(int(feature_max),int(grid[i][j][k])),int(feature_min));
            }
        }
    }
}
void SOM(vector<vector<int>> dataset,int initial_l_r,int no_of_itr,int grid_height,int grid_width,int feature_size,float feature_max,float feature_min){
    
    // initialising grid with random values
    vector<vector<vector<float>>> grid(grid_height,vector<vector<float>>(grid_width,vector<float>(feature_size,0)));
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            for(int k=0;k<grid[0][0].size();k++){
                grid[i][j][k]=rand()%int((feature_max-feature_min+1))+feature_min;
            }
        }
    }
// running the algorithm of SOM
for(int j=0;j<no_of_itr;j++){
    for(int i=0;i<dataset.size();i++){
        // finding coord of winning neuron for each data point
        pair<int,int> loc_neuron=winning_neuron(dataset[i],grid);
        float l_r=0.1;
        l_r=pow(0.9,i/10);
        // updating the grid
        update_grid(loc_neuron,grid,l_r,feature_max,feature_min);
    }
    }
    // storing the output in file named myfile.csv
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
    // Creating the database of Colours based on RGB values
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

    // providing the desired inputs to the SOM.
    int no_of_itr=5;
    // l_r is changing exponentially inside the SOM
    float l_r=0.9;
    int grid_length=100;
    int grid_width=100;
    int feature_size=3;
    float feature_max=255;
    float feature_min=56;
    // cluster the dataset based on grid
    // in case of dim reduction set the first n(feature_size) of data features as most important ones
    SOM(dataset,l_r,no_of_itr,grid_length,grid_width,feature_size,feature_max,feature_min);
    return 0;
}