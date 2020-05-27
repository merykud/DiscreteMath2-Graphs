//
//  main.cpp
//  Math209_project
//
//  Created by Merjem Kudeimati on 18/05/2020.
//  Copyright © 2020 Merjem Kudeimati. All rights reserved.
//

#include <iostream>
#include <list>
using namespace std;

class Graph
{
    int no_vertices;
    list<int> *adj;
    void DFSrec (int n, bool visited[]);
    
public:
    Graph(int no_vertices);
    void addEdge(int a, int b);
    Graph ReverseGraph();
    bool complement(Graph g1, Graph g2);
    bool isConnected();
    int no_components();
    bool isomorph(Graph g1, Graph g2);
    int no_edges();
    
};

Graph::Graph(int V){
    this->no_vertices = V;
    adj = new list<int>[V];
}
    
void Graph::addEdge(int a, int b){
    adj[a].push_back(b);
    adj[b].push_back(a);
}
int Graph:: no_edges(){
    int sum = 0;
    for (int i = 0 ; i < no_vertices ; i++)
        sum += adj[i].size();
    return sum/2;
}
Graph Graph::ReverseGraph(){
    Graph g(no_vertices);
    for (int v = 0; v < no_vertices; v++){
        list<int>::iterator i;
        for(i = adj[v].begin(); i != adj[v].end(); ++i){
            g.adj[*i].push_back(v);
        }
    }
    return g;
}

bool Graph::complement(Graph g1, Graph g2){
    bool flag=false;
    g2.ReverseGraph();
    for (int i=0; i<no_vertices; i++)
       if (g1.adj[i]==g2.adj[i]){
           flag=true;
       }
        else
            flag=false;
    return flag;
}

void Graph::DFSrec (int n, bool visited[]){
    visited[n] = true;
    list<int>::iterator i;
    for (i = adj[n].begin(); i != adj[n].end(); ++i)
        if (!visited[*i])
            DFSrec(*i, visited);
}
bool Graph::isConnected(){
    bool visited[no_vertices];
    for (int i = 0; i < no_vertices; i++)
        visited[i] = false;
    
    DFSrec(0, visited);
    
    for (int i = 0; i < no_vertices; i++)
        if (visited[i] == false)
             return false;
    
    return true;
}

int Graph::no_components(){
    bool* visited = new bool[no_vertices];
    int count = 0;
    
    for (int n = 0; n < no_vertices; n++)
        visited[n] = false;
    
    for (int n = 0; n < no_vertices; n++){
        if (visited[n] == false){
            DFSrec(n, visited);
            count += 1;
        }
    }
    
    if (isConnected() == true)
        return 1;
    else
        return count;
}
bool Graph::isomorph(Graph g1, Graph g2){
    bool flag=false;
    for (int i=0; i<no_vertices; i++){
        if (g1.adj[i].size()==g2.adj[i].size())
                flag = true;
    }
    if (g1.no_components()==g2.no_components() && g1.no_edges()==g2.no_edges() && flag==true)
        return true;
    else
        return false;
}
int main()
{
    Graph g1(4);
    Graph g2(4);
    Graph g3(10);
    g1.addEdge(0, 1);
    g2.addEdge(1, 0);
    g1.addEdge(1, 2);
    g2.addEdge(2, 1);
    g1.addEdge(2, 3);
    g2.addEdge(3, 2);
    g1.addEdge(1, 3);
    g2.addEdge(3, 1);
    
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    
    g3.addEdge(3, 4);
    g3.addEdge(4, 5);
    
    g3.addEdge(6, 7);
    
    g3.addEdge(8, 9);
    
    cout << "Complement:"<<endl;
    cout<< g1.complement(g1,g2) <<"   ";
    cout<< g2.complement(g2,g3) <<"   ";
    cout<< g3.complement(g3,g1) <<endl;
    
    cout << "No of connected components:" <<endl;
    cout <<g1.no_components() <<"   ";
    cout <<g2.no_components() <<"   ";
    cout <<g3.no_components() <<endl;
     
    cout <<"Isomorphic:" <<endl;
    cout<< g1.isomorph(g1, g2) <<"   ";
    cout<< g2.isomorph(g2, g3) <<"   ";
    cout<< g3.isomorph(g3, g1) <<"   ";
    
    cout << endl;
    
    return 0;
}
