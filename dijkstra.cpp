#include "dijkstra.h"
/*The heap struct to hold Heap*/
vector<unsigned int> Q;
unsigned int pos_Q[VERTICES];//holds the position of vertices in the Q
/*Dijkstra v^2 algo. i.e dijkstra without min heap*/

//status marker for Dijkstra algo
enum status{UNSEEN,IN_TREE,FRINGE};
//Heapify code
int heapify (unsigned int cap[], unsigned int curr)
{
    unsigned int left = 2*curr;
    unsigned int right = 2* curr + 1;
    unsigned int largest = curr;
    unsigned int  temp;
    int step_count =0;
    while(curr<Q.size())
    {
        left = 2*curr;
        right = 2*curr + 1;
        if(left< Q.size()&& cap[Q[left]]>cap[Q[curr]])
            largest = left;
        if(right< Q.size() && cap[Q[right]]>cap[Q[largest]])
            largest = right;
        if(largest!=curr)
        {
            /*Swap the two structures*/
            temp = Q[curr];
            Q[curr] = Q[largest];
            Q[largest] = temp;
            //update their positions
            pos_Q[Q[largest]]=largest;
            pos_Q[Q[curr]] = curr;

            curr = largest;

        }
        else
            break;
        step_count++;
    }
return step_count;
}

/*Extract Max element from the heap*/
int extract_max(unsigned int cap[])
{
    Q[0] =Q.back();
    pos_Q[Q[0]] =0;
    Q.pop_back();
    return heapify(cap,0);
}
int increase_key(unsigned int cap[], unsigned int curr)
{
    int steps = 0;
    unsigned int parent = curr/2;
    unsigned int temp;
    while(curr>0&& cap[Q[parent]]<cap[Q[curr]])
    {
            temp = Q[curr];
            Q[curr] = Q[parent];
            Q[parent] = temp;
            //update their positions
            pos_Q[Q[parent]]=parent;
            pos_Q[Q[curr]] = curr;

            curr = parent;
            parent = curr/2;
            steps++;
    }
    return steps;
}

/*Returns max_index*/
unsigned int minimum(unsigned int t1, unsigned int t2)
{
    unsigned int mini;
    if(t1<t2)
        mini=t1;
    else
        mini=t2;
    return mini;
}
/*Returns the max_Vertex using the cap array*/
unsigned int max_vertex(unsigned int cap[],status visited[])
{
    unsigned int max_v;
    //initialize the values
    unsigned int max_weight = 0;
    for (unsigned int i =0;i<VERTICES;i++)
    {
        if(visited[i]==FRINGE && cap[i]>max_weight)
        {
            max_weight = cap[i];
            max_v = i;
        }
    }
    return max_v;
}

/*normal dijkstra's algorithm without heap*/
int normal_dijkstra(Graph *g, unsigned int start, unsigned int dest)
{
    unsigned int cap[VERTICES];
    unsigned int k;
    unsigned int intree_count =0;
    status visited[VERTICES];
    unsigned int parent[VERTICES];
    int v;
    unsigned int temp,temp1;
    int step_count =0;
    //initialize the above variables
    for(int i=0;i<VERTICES;i++)
    {
        cap[i] = 0;
        visited[i] = UNSEEN;
        parent[i] = i;
        step_count++;
    }
    visited[start]=IN_TREE;
    intree_count++;
    /*ADD adjacent vertices of src to fringe*/
    for(k =0;k<g->graph[start].size();k++)
    {
        temp = g->graph[start][k].vertex;
        visited[temp] = FRINGE;
        parent[temp]=start;
        cap[temp]= g->graph[start][k].weight;
        step_count++;
    }
    while(intree_count<VERTICES)
    {
    //select vertice with max weight
    //source will be selected
      v = max_vertex(cap,visited);
      step_count+=VERTICES;
      visited[v] =IN_TREE;
      intree_count++;
      for(k =0;k<g->graph[v].size();k++)
      {
          //for each of the adjacent edges do
          temp1 = g->graph[v][k].vertex;
          temp =  g->graph[v][k].weight;
          if(visited[temp1]==UNSEEN)
          {
              visited[temp1]=FRINGE;
              parent[temp1]=v;
              cap[temp1] = minimum(cap[v],temp);
          }
          else if(visited[temp1]==FRINGE && cap[temp1]<minimum(cap[v],temp))
          {
              parent[temp1]=v;
              cap[temp1] = minimum(cap[v],temp);
          }
          step_count++;
      }
    }
#ifdef debug

    cout<<"The Max_Bandwidth_Path from "<<start<<" to "<<dest<<" printed in reverse is:"<<endl;
    temp=dest;
        if(parent[temp]!=temp)
    {
        while(parent[temp]!=start)
        {
            cout<<temp<<" --> ";
            temp = parent[temp];
        }
        cout<<temp<<" --> "<< parent[temp]<<endl;
    }
#endif // debug
return step_count;
}

int heap_dijkstra(Graph *g, unsigned int start, unsigned int dest)
{
    unsigned int cap[VERTICES];
    unsigned int k;
    unsigned int intree_count =0;
    status visited[VERTICES];
    unsigned int parent[VERTICES];
    int v;
    int pos =0;
    unsigned int temp,temp1;
    int step_count =0;
    //initialize the above variables
    for(unsigned int i=0;i<VERTICES;i++)
    {
        cap[i] = 0;
        visited[i] = UNSEEN;
        parent[i] = i;
        step_count++;
        if(i!=start)
        {
            Q.push_back(i);
            pos_Q[i] = pos;
            pos++;
        }
    }
    visited[start]=IN_TREE;
    intree_count++;
    /*ADD adjacent vertices of src to fringe*/
    for(k =0;k<g->graph[start].size();k++)
    {
        temp = g->graph[start][k].vertex;
        visited[temp] = FRINGE;
        parent[temp]=start;
        cap[temp]= g->graph[start][k].weight;
        step_count+=increase_key(cap,pos_Q[temp]);
    }
    while(!Q.empty())
    {
    //select vertice with max weight
    //source will be selected
      v = Q.front();
      step_count+=extract_max(cap);
      visited[v] =IN_TREE;
      for(k =0;k<g->graph[v].size();k++)
      {
          //for each of the adjacent edges do
          temp1 = g->graph[v][k].vertex;
          temp =  g->graph[v][k].weight;
          if(visited[temp1]==UNSEEN)
          {
              visited[temp1]=FRINGE;
              parent[temp1]=v;
              cap[temp1] = minimum(cap[v],temp);
              step_count+=increase_key(cap,pos_Q[temp1]);
          }
          else if(visited[temp1]==FRINGE && cap[temp1]<minimum(cap[v],temp))
          {
              parent[temp1]=v;
              cap[temp1] = minimum(cap[v],temp);
              step_count+=heapify(cap,pos_Q[temp1]);
          }
          step_count++;
      }
    }
#ifdef debug
    cout<<"The Max_Bandwidth_Path from "<<start<<" to "<<dest<<" printed in reverse is:"<<endl;
    temp=dest;
    if(parent[temp]!=temp)
    {
        while(parent[temp]!=start)
        {
            cout<<temp<<" --> ";
            temp = parent[temp];
        }
        cout<<temp<<" --> "<< parent[temp]<<endl;
    }
#endif // debug
return step_count;
}
