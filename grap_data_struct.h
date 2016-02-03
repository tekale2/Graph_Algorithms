#ifndef GRAP_DATA_STRUCT_H
#define GRAP_DATA_STRUCT_H

#include <list>
#include <vector>
#include <string>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
//change this to debug or no debug

//uncomment the line below for debugging
//#define debug
#ifdef debug
     #define VERTICES 9
#endif // debug
#ifndef debug
    #define VERTICES 5000
#endif // debug

#define MAX_WEIGHT 10000

using namespace std;
/* Data Struct to hold the next vertex value*/
struct list_node
{
    unsigned int weight;
    unsigned int vertex;
};

typedef struct list_node node;

struct kruskal_node
{
    unsigned int u;
    unsigned int v;
    unsigned int weight;
    //operator overloading
    // will be used by swap funtion
    kruskal_node& operator=(const kruskal_node& rhs)
    {
        u = rhs.u;
        v = rhs.v;
        weight = rhs.weight;
        return *this;
    }
};
typedef struct kruskal_node Knode;
/*Main Adjaceny list data_struct*/
class Graph
{
public:
    vector< vector<node> > graph; // graph with 5000 vertices
    vector<Knode> node_list; // to be used by kruskal's heapsort

    unsigned int EDGES; //number of edges in the graph
    /*Graph Initializer functions*/
    Graph()
    {
        graph.resize(VERTICES);
    }
    void init1_random_graph(unsigned int degree); /*initialize a random graph with random values of given degree*/


    void init_graph_file(char* filename); //intialize graph with a file
    bool uniq(unsigned int vert, unsigned int k)
    {
        bool temp = true;
        for(unsigned int i=0;i<graph[k].size();i++)
        {
            if(graph[k][i].vertex==vert)
            {
                temp = false;
                break;
            }
        }
        return temp;
    }
};
inline void Graph::init1_random_graph(unsigned int degree)
{
    unsigned int edge;
    unsigned int vert;
    Knode mynode;
    EDGES =0;
    node gnode;//graph struct
    //generate a connected graph
    /* i.e connect 0 to 5000 with a single path*/
    for(int i=0;i<VERTICES-1;i++)
    {
        edge = rand()%MAX_WEIGHT + 1;
        mynode.u=i;
        mynode.v=i+1;
        mynode.weight = edge;
        node_list.push_back(mynode);
        gnode.weight = mynode.weight;
        gnode.vertex = i;
        graph[i+1].push_back(gnode);
        gnode.vertex = i+1;
        graph[i].push_back(gnode);
        EDGES++;
    }
    //Actual random graph generation
    for(unsigned int j=0;j<degree-1;j++)
    {
        for(unsigned int k =0;k<VERTICES;k++)
        {
            if(graph[k].size()<degree)
            {
                vert = rand()%VERTICES;
                while(vert==k && uniq(vert,k)==false)
                    vert = rand()%VERTICES;
                edge = rand()%MAX_WEIGHT + 1;
                mynode.u=k;
                mynode.v=vert;
                mynode.weight = edge;
                node_list.push_back(mynode);
                gnode.weight = mynode.weight;
                gnode.vertex = vert;
                graph[k].push_back(gnode);
                gnode.vertex = k;
                graph[vert].push_back(gnode);
                EDGES++;
            }
        }
    }
}

inline void Graph::init_graph_file(char* filename)
{
    ifstream myfile;
    myfile.open(filename);
    Knode mynode;
    node gnode;//graph struct
    if(myfile)
    {
        myfile>>EDGES;
        for(unsigned int i=0;i<EDGES;i++)
        {
            //populate the list as well as the graph.
            myfile>>mynode.u;
            myfile>>mynode.v;
            myfile>>mynode.weight;
            node_list.push_back(mynode);
            gnode.weight = mynode.weight;
            gnode.vertex = mynode.v;
            graph[mynode.u].push_back(gnode);
            gnode.vertex = mynode.u;
            graph[mynode.v].push_back(gnode);
        }
    }
    else
    {
        cout<<"The filename you entered was incorrect"<<endl;
        exit(1);
    }
    //close the file
    myfile.close();
    return;
}

#endif // GRAP_DATA_STRUCT_H
