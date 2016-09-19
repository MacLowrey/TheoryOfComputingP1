//
//  main.cpp
//  p1Theory
//
//  Created by Jon Lowrey on 9/7/16.
//  Copyright © 2016 Jon Lowrey. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct node{
    node* a =nullptr;
    node* b =nullptr;
    bool finalState = false;
    int name = -1;
    
}firstNode;

void simulate(vector<node> map, vector<string> theStrings,int startNode){
    node* p = &map[startNode];
    for(int i=0;i<theStrings.size();i++)
    {
        cout<<theStrings[i]<<" <---";
        for(int j=0;j<theStrings[i].length();j++)
        {
            if(theStrings[i].at(j) == 'a')
            {
                node hold = *p;
                p = hold.a;
            }
            if(theStrings[i].at(j) == 'b')
            {
                node hold = *p;
                p = hold.b;
            }
        
        }
        node hold = *p;
        if(hold.finalState){cout<<"ACCEPT"<<endl;}
        else cout<<"REJECT"<<endl;
    }
    


}

void printMap(vector<node> map){
    for(int i =1;i<map.size();i++)
    {
        node a = *map[i].a;
        node b = *map[i].b;
        cout<<"Node:"<<map[i].name<<" A: "<<a.name<<" B: "<<b.name;
        if(map[i].finalState){cout<<" FINAL"<<endl;}
        cout<<endl;

        
    }
    return;
}



int main(int argc, const char * argv[]) {
    vector<node> map;
    map.push_back(firstNode); //This allows our numbers to match
    vector<string> theStrings;
    vector<int> finalStates;
    fstream file;
    string filename,holder,title,alphabet;
    int numberOfNodes;
    cout<<"please enter the filename"<<endl;
    cin>>filename;
    file.open(filename);
    if(!file.is_open()){cout<<"Filename Issue"<<endl; return 0;}
    getline(file,title);
    file>>alphabet;
    file>>numberOfNodes;
    for(int i = 1;i<=numberOfNodes;i++){
        node n;
        n.name=i;
        map.push_back(n);
    }
    for(int i = 1;i<=numberOfNodes;i++){
        int x=-1;
        file>>x;
        map[i].a = &map[x];
        file>>x;
        map[i].b = &map[x];
    }
    int beginStates = 0,numfinState,finState;
    file>>beginStates; //The Node where we begin test
    file>>numfinState; //The Number of Nodes that have a final state
    for(int i =0;i<numfinState;i++){
    file>>finState;
        map[finState].finalState = true;
        finalStates.push_back(finState);
    }
    //cout<<"The Garbage"<<endl<<title<<endl<<alphabet<<endl<<numberOfNodes<<endl<<map[1].name<<endl<<map[2].name<<endl<<map[3].name<<endl;
    
    while(file>>holder){
        theStrings.push_back(holder);
        holder.clear();
    }
    for(int j =0;j<theStrings.size();j++){
        cout<<theStrings[j]<<endl;
    
    }
    //printMap(map);
    simulate(map, theStrings, beginStates);
    return 0;
        
        
}
