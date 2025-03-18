// You have a business with several offices; you want to lease phone lines
// to connect them up with each other; and the phone company charges
// different amounts of money to connect different pairs of cities. You
// want a set of lines that connects all your offices with a minimum total
// cost. Solve the problem by suggesting appropriate data structures.

// OR

// Tour operator organizes guided bus trips across the Maharashtra.
// Tourists may have different preferences. Tour operator offers a choice
// from many different routes. Every day the bus moves from starting city
// S to another city F as chosen by client. On this way, the tourists can see
// the sights alongside the route travelled from S to F. Client may have
// preference to choose route. There is a restriction on the routes that the
// tourists may choose from, the bus has to take a short route from S to F
// or a route having one distance unit longer than the minimal distance.
// Two routes from S to F are considered different if there is at least one
// road from a city A to a city B which is part of one route, but not of the
// other route

#include <bits/stdc++.h>
using namespace std;

class disjointSet
{
    int V;
    vector<int> size;
    vector<int> parent;

public:
    disjointSet(int V)
    {
        size.resize(V, 0);
        parent.resize(V, 0);
        for (int i = 0; i < V; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findPar(int node)
    {
        if (parent[node] == node)
            return node;
        return parent[node] = findPar(parent[node]);
    }

    void unionBysize(int n1, int n2)
    {
        int ulp_n1 = findPar(n1);
        int ulp_n2 = findPar(n2);
        if (ulp_n1 == ulp_n2)
            return;
        if (size[ulp_n1] > size[ulp_n2])
        {
            size[ulp_n1] += size[ulp_n2];
            parent[ulp_n2] = parent[ulp_n1];
        }
        else
        {
            size[ulp_n2] += size[ulp_n1];
            parent[ulp_n1] = parent[ulp_n2];
        }
    }
};

class mst
{
public:
    int prims(int start, int V, vector<pair<int, int>> adj[])
    {

        // Min heap because we will get the city at the top of priority queue which has minimum weight connected to it
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> vis(V, 0);

        pq.push({0, start});
        int weight = 0;

        while (!pq.empty())
        {
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int wt = it.first;

            if (vis[node])
                continue;
            vis[node] = 1;
            weight += wt;

            for (auto j : adj[node])
            {
                int edgeW = j.first;
                int adjNode = j.second;
                if (!vis[adjNode])
                    pq.push({edgeW, adjNode});
            }
        }
        return weight;
    }

    // it is based on disjoint set
    // in this assignment we will perform union by size as it is more intuitional than union by rank
    // works with sorted order 
    int kruskal(int V, vector<pair<int, int>> adj[])
    {   
            vector<tuple<int, int, int>> edges;
    
            for (int i = 0; i < V; i++) {
                for (auto [wt, adjn] : adj[i]) {
                    if (i < adjn)
                        edges.push_back({wt, i, adjn});
                }
            }
    
            sort(edges.begin(), edges.end());
    
            disjointSet ds(V);
            int mw = 0;
    
            for (auto [wt, u, v] : edges) {
                if (ds.findPar(u) != ds.findPar(v))
                {
                    mw += wt;
                    ds.unionBysize(u, v);
                }
            }
            return mw;
    }
    

    void displayAdjList(int n, const vector<pair<int, int>> adj[])
    {
        for (int i = 0; i < n; i++)
            for (auto it : adj[i])
            {
                // for(auto j:it)
                cout << "\nWeight: " << it.first << " -> " << " Adj node: " << it.second << endl;
            }
    }
};

int main()
{
    int n;
    cout << "\nEnter number of cities you want to add: ";
    cin >> n;
    vector<pair<int, int>> adj[n];
    int e;
    cout << "\nEnter number of routes you want to add: ";
    cin >> e;

    while (e--)
    {
        int parN, adjN, edW;
        cout << "\n\nEnter cities and distance between them: ";
        cin >> parN >> adjN >> edW;
        adj[parN].push_back({edW, adjN});
        adj[adjN].push_back({edW, parN});
    }
    mst calc;
    calc.displayAdjList(n, adj);
    cout<<"\n\nUsing Prims algorithm: \n\n";
    cout << "\n\nMinimum cost of travelling from S to F is: " << calc.prims(0, n, adj);
    cout << "\n\nDone!!\n\n";
    cout<<"\n\nUsing Kruskal's algorithm: \n\n";
    cout << "\n\nMinimum cost of travelling from S to F is: " << calc.kruskal( n, adj);
    cout << "\n\nDone!!\n\n";
    return 0;
}
