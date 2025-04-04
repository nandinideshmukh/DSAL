#include <bits/stdc++.h>
using namespace std;

struct node{
    int data ;
    node *left = nullptr;
    node *right = nullptr;
};

class obst{
    int r[100][100]={0};
    double c[100][100]={0.0};
    double w[100][100]={0.0};
    
    
    public:
    node *get_cost(int n,double p[],double q[],double keys[]){
        for(int i=0;i<=n;i++){
            r[i][i] = 0;
            w[i][i] = q[i];
            c[i][i] = 0;
        }
        
        for(int m =1;m<=n;m++){
            for(int i=0;i<=n-m;i++){
                int j = i + m;
                
                w[i][j] = p[j-1]+q[j]+w[i][j-1];
                
                double mincost = DBL_MAX;
                int minroot = 0;

                for(int k = i+1;k<=j;k++){
                    
                    double cost = c[i][k-1]+c[k][j];
                    
                    if(cost<mincost){
                        mincost = cost;
                        minroot = k;
                    }
                }
                r[i][j] = minroot;
                c[i][j] = mincost + w[i][j];
            }
        }
        
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++)
        cout<<c[i][j]<<"\t";
        cout<<endl;
    }
    node *root = create_tree(0,n,keys);
    return root;
    }
    
    node *create_tree(int i,int j,double keys[]){
        if(i==j) return nullptr;
        else{
            node *n = new node();
            n -> data = keys[r[i][j] - 1];
            n -> left = create_tree(i , r[i][j] - 1 , keys);
            n -> right = create_tree(r[i][j] , j , keys);
            return n;
        }
        
    }
    
    void inOrder(node *n){
        if(n == nullptr) return;

        inOrder(n -> left);
        cout<<n -> data<<" ";
        inOrder(n -> right);
    }
    
};
int main()
{
    double keys[]= {10,20};
    double p[]= {0.6,0.4};
    double q[] = {0.1,0.1,0.1};
    obst t;
    node *head = t.get_cost(2,p,q,keys);
    t.inOrder(head);
    return 0;
}
