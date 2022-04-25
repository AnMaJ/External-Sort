//
//  main.cpp
//  External_Sort
//
//  Created by Mansi on 24/04/22.
//

#include<bits/stdc++.h>
#include<iostream>
#include<vector>

using namespace std;
void externalsort(vector<vector<int>> &runs,int b){
    //sorting ther values inside the pages by sending pages to the ram one by one
    for(int i=0;i<runs.size();i++){
        sort(runs[i].begin(),runs[i].end());
    }
    
    while((runs.size())>1){
        vector<vector<int>> nextruns;
        //merging b-1 entries at a time
        for(int i=0;i<runs.size();i+=(b-1)){
            int numpointers;
            //initializing teh number of pointers as they won't be always b-1(in cases where they will be less than b-1
            if((runs.size())-i+1>=b-1){
                numpointers=b-1;
            }else{
                numpointers=(runs.size())-i;
            }
            //array to store the value of pointers (b-1 pointers in the ram)
            int arr[numpointers];
            //initializing all the pointers to the first element in the page(sorted)
            for(int i=0;i<numpointers;i++){
                arr[i]=0;
            }
            //utilizing the bth page in the ram
            vector<int> temp;
            while(1){
                bool allmerged=true;
                int minindex=-1,minval;
                for(int j=0;j<numpointers;j++){
                    //if any of the pointers hasn't reached till the end of the page, then declaring allmerged as false
                    if(arr[j]<runs[j+i].size()){
                        allmerged=false;
                        if(minindex==-1 || (runs[j+i][arr[j]]<minval)){
                            minindex=j;
                            minval=runs[j+i][arr[j]];
                        }
                    }
                }
                if(minindex==-1){
                    break;
                }
                arr[minindex]++;
                temp.push_back(minval);
            }
            nextruns.push_back(temp);
        }
        runs=nextruns;
    }
}
int main(){
    int b,recperpage,totalrec,numfullpages;
    cin>>b>>recperpage>>totalrec;
    numfullpages=totalrec/recperpage;
    vector<vector<int>> runs;
    int k=0;
    for(int i=0;i<numfullpages;i++){
        vector<int> temp;
        for(int j=0;j<recperpage;j++){
            int x;
            cin>>x;
            temp.push_back(x);
            k++;
        }
        runs.push_back(temp);
    }
    if((totalrec%recperpage)!=0){
        int recordsleft=totalrec-k;
        vector<int> temp;
        for(int i=0;i<recordsleft;i++){
            int x;
            cin>>x;
            temp.push_back(x);
        }
        runs.push_back(temp);
    }
    
    externalsort(runs,b);
    //printing
    for(int i=0;i<runs[0].size();i++){
        cout<<runs[0][i]<<endl;
    }
}
