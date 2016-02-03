#include "kruskal.h"
bool IN_MST[VERTICES][VERTICES];
/*The Heapify algorithm*/
int Heapify (vector<Knode> *arr, unsigned int curr, unsigned int heap_size)
{
    unsigned int left = 2*curr;
    unsigned int right = 2* curr + 1;
    unsigned int smallest = curr;
    Knode temp;
    int step_count =0;
    while(curr<=heap_size)
    {
        left = 2*curr;
        right = 2*curr + 1;
        if(left<=heap_size && (*arr)[left].weight<(*arr)[curr].weight)
            smallest = left;
        if(right<=heap_size && (*arr)[right].weight<(*arr)[smallest].weight)
            smallest = right;
        if(smallest!=curr)
        {
            /*Swap the two structures*/
            temp = (*arr)[curr];
            (*arr)[curr] = (*arr)[smallest];
            (*arr)[smallest] = temp;
            curr = smallest;
        }
        else
            break;
        step_count++;
    }
return step_count;
}
void init_data()
{
        for(int i=0;i<VERTICES;i++)
            for(int j=0;j<VERTICES;j++)
            {
                IN_MST[i][j]=false;
                IN_MST[j][i]=false;
            }
}
/*Builds a heap out of unordered array*/
int Make_Heap(vector<Knode> *arr)
{
    int steps =0;
    for(int i = (arr->size()-1)/2; i>=0;i--)
        steps+=Heapify(arr,i,arr->size()-1);

    return steps;
}

int Heapsort(vector<Knode> *arr)
{
    Knode temp;
    int steps =0;
    for(int i =(arr->size()-1);i>=1; i--)
    {
            temp = (*arr)[i];
            (*arr)[i] = (*arr)[0];
            (*arr)[0] = temp;
           steps+=Heapify(arr,0,i-1);
    }
    return steps;
}

void make_set(unsigned int Parent[],unsigned int Rank[], unsigned int i)
{
    Parent[i] = i;
    Rank[i] = 0;
}

int Find(unsigned int Parent[], unsigned int v, int *steps)
{
    unsigned int w;
    w = v;
    while(Parent[w]!=w)
    {
        (*steps)++;
        w = Parent[w];
    }

    return Parent[w];
}
/*Union By Rank*/
void Union(unsigned int Parent[], unsigned int Rank[], unsigned int r1, unsigned int r2)
{
    if(Rank[r1]<Rank[r2])
        Parent[r1] = r2;
    else if(Rank[r2]<Rank[r1])
        Parent[r2] = r1;
    else
    {
        Parent[r2] = r1;
        Rank[r1]++;
    }
}

int Kruskal(Graph *g)
{
    int steps = 0;
    unsigned int Parent[VERTICES];
    unsigned int Rank[VERTICES];
    unsigned int r1,r2;
    Knode edge;
    //Step1: Heapsort make heap is already called
    // in main loop.

    steps=+Heapsort(&(g->node_list));
    //do makeset
    for(unsigned int v=0;v<VERTICES;v++)
    {
        make_set(Parent,Rank,v);
        steps++;
    }
    //perform the main algo
    for(unsigned int i=0;i<g->EDGES;i++)
    {
        //greedily pick the next edge
        edge = g->node_list[i];
        //find operation
        r1 = Find(Parent,edge.u,&steps);
        r2 = Find(Parent,edge.v,&steps);
       // cout<<edge.u<<" e "<<edge.v<<" "<<edge.weight<<" "<<r1<<" "<<r2<<endl;
        if(r1!=r2)
        {
            //Union those two edges
            Union(Parent,Rank,r1,r2);
            //Mark those edges in_tree status
            IN_MST[edge.v][edge.u]=true;
            IN_MST[edge.u][edge.v]=true;
        }
        //just discard it.
        steps++;
    }
    return steps;
}
void DFS_main(Graph *g,unsigned int start, int *steps, bool visited[], unsigned int prev[] )
{

    visited[start] =true;
   for(unsigned int i=0;i<VERTICES;i++)
   {
       steps++;
       if(!visited[i]&&IN_MST[start][i])
       {
           prev[i]=start;
           DFS_main(g,i,steps,visited,prev);
       }
   }

}
int DFS(Graph *g, unsigned int start, unsigned int dest)
{
    bool visited[VERTICES];
    unsigned int prev[VERTICES];
    int steps =0;
    unsigned int temp;
    for(int i =0;i<VERTICES;i++)
    {
        visited[i] =false;
        prev[i] = i;
        steps++;
    }
    DFS_main(g,start,&steps,visited,prev);
#ifdef debug

    cout<<"The Max_Bandwidth_Path from "<<start<<" to "<<dest<<" printed in reverse is:"<<endl;
    temp=dest;
        if(prev[temp]!=temp)
    {
        while(prev[temp]!=start)
        {
            cout<<temp<<" --> ";
            temp = prev[temp];
        }
        cout<<temp<<" --> "<< prev[temp]<<endl;
    }
#endif
    return steps;
}
