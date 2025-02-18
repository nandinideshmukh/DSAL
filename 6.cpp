/*

Represent a given graph using adjacency list to perform DFS and BFS.
Use the map of the area around the college as the graph. Identify the
prominent landmarks as nodes and perform DFS and BFS on that.

*/

#include <bits/stdc++.h>
using namespace std;

class adjList{
    public:
    void addEdge(vector<vector<int>>  &adj,int i,int j){
        adj[i].push_back(j);
        adj[j].push_back(i);
    }

    vector<int> dfs(int start,vector<vector<int>> adj,int vis[],vector<int> &ls){
        
        vis[start] =1;
        ls.push_back(start);
        for(auto it:adj[start]){
            if(!vis[it]) dfs(it,adj,vis,ls);
        }
        // st.push(start);
        return ls;
    }

        vector<int> bfs(int start,vector<vector<int>> adj,int vis[])
    {
        queue<int> q;
        q.push(start);
        vector<int> bfs_vector; 

        vis[start] = 1;
        while(!q.empty()){
            auto it = q.front();
            bfs_vector.push_back(it);
            q.pop();
            for(auto i:adj[it]){
            if(!vis[i]) {
                vis[i] = 1; 
                q.push(i);}
        }
        }
    return bfs_vector;
    }

void displayAdjList(const vector<vector<int>>& adj) {
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": "; // Print the vertex
        for (int j : adj[i]) {
            cout << j << " "; // Print its adjacent
        }
        cout << endl; 
    }
}
    void display(vector<int> vt){
        for(int it=0;it<vt.size();it++)
        cout<<vt[it]<<" ";
    }
};

int main(){
    adjList op;
    int n;
    cout<<"\nEnter number of nodes: ";
    cin>>n;
    vector<vector<int>>  adj(n);

    op.addEdge(adj,0,1);
    op.addEdge(adj,1,2);
    op.displayAdjList(adj);
    vector<int> st(n);
    int vis[n]={0};
    st = op.bfs(0,adj,vis);
    op.display(st);
    // op.dfs(0,adj,vis,st);
    // op.display(st);

    return 0;
}
