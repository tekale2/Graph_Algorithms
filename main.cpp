#include "dijkstra.h"
#include "grap_data_struct.h"
#include "kruskal.h"
#include <ctime>
#include <sys/time.h>
using namespace std;
/*test wether generated value is unique*/
vector<unsigned int> st_pair;
bool is_uniq(unsigned int vert)
{
    bool temp = true;
    for(unsigned int i=0;i<st_pair.size();i++)
    {
            if(st_pair[i]==vert)
            {
                temp=false;
                break;
            }
    }
    return temp;
}

void timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
 unsigned  long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    //return (diff<0);
}

int main()
{
    Graph G1;
    Graph G2;
    struct timeval start;
    struct timeval finish;
    struct timeval result;
    unsigned int temp,j;
    srand(time(NULL));
    char filename[] = "test_graph.txt";
    char out_file[] = "output.txt";
   ofstream output(out_file);

#ifdef debug
    G1.init_graph_file(filename);
    init_data();
    Make_Heap(&G1.node_list);
    /*Please change your values accordingly for testing*/
    cout<<"The number steps executed for Kruskal were: "<<Kruskal(&G1)<<endl;
    cout<< "The steps number executed for dijkstra were: "<<normal_dijkstra(&G1,0,4)<<endl;
    cout<< "The steps number executed for heap dijkstra were: "<<heap_dijkstra(&G1,0,4)<<endl;
    cout<< "The steps number executed for dfs were: "<<DFS(&G1,0,4)<<endl;

#endif // debug

#ifndef debug
   G1.init1_random_graph(6);
   G2.init1_random_graph(1000);
   //generate 5 random st_pairs
      temp = rand()%VERTICES;
   st_pair.push_back(temp);
   for(int i=1;i<10;i++)
   {    temp = rand()%VERTICES;
        while(is_uniq(temp)==false)
            temp = rand()%VERTICES;
        st_pair.push_back(temp);
   }

    //test on G1
    init_data();
    Make_Heap(&G1.node_list);
    cout<<"Running Kruskal"<<endl;
    output<<"Running tests on graph G1 of degree 6"<<endl;
     gettimeofday(&start,NULL);
     //Running Kruskal first
     output<<"The number steps executed for Kruskal were: "<<Kruskal(&G1)<<endl;
     gettimeofday(&finish,NULL);
     timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for Kruskal was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;
    //running dijkstra
    cout<<"Running dijkstra"<<endl;
    gettimeofday(&start,NULL);
    for(j=0;j<10;j=j+2)
        output<< "The steps number executed for dijkstra were: "<<normal_dijkstra(&G1,st_pair[j],st_pair[j+1])<<endl;

    gettimeofday(&finish,NULL);
    timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for normal dijkstra was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;

    //running heap_dijkstra
     cout<<"Running heap_dijkstra"<<endl;
    gettimeofday(&start,NULL);
    for(j=0;j<10;j+=2)
        output<< "The steps number executed for heap_dijkstra were: "<<heap_dijkstra(&G1,st_pair[j],st_pair[j+1])<<endl;

    gettimeofday(&finish,NULL);
    timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for heap dijkstra was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;
        //running dfs
    cout<<"Running DFS"<<endl;
    gettimeofday(&start,NULL);
    for(j=0;j<10;j+=2)
        output<< "The steps number executed for dfs were: "<<DFS(&G1,st_pair[j],st_pair[j+1])<<endl;

    gettimeofday(&finish,NULL);
    timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for normal dfs was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;
   /*

   Now Testing on G2 graph

   */
    init_data();
    Make_Heap(&G2.node_list);
        cout<<"Running Kruskal"<<endl;
    output<<"Running tests on graph G2 of degree 1000"<<endl;
     gettimeofday(&start,NULL);
     //Running Kruskal first
     output<<"The number steps executed for Kruskal were: "<<Kruskal(&G2)<<endl;
     gettimeofday(&finish,NULL);
     timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for Kruskal was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;
    //running dijkstra
    cout<<"Running dijkstra"<<endl;
    gettimeofday(&start,NULL);
    for(j=0;j<10;j+=2)
        output<< "The steps number executed for dijkstra were: "<<normal_dijkstra(&G2,st_pair[j],st_pair[j+1])<<endl;

    gettimeofday(&finish,NULL);
    timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for normal dijkstra was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;

    //running heap_dijkstra
     cout<<"Running heap_dijkstra"<<endl;
    gettimeofday(&start,NULL);
    for(j=0;j<10;j+=2)
        output<< "The steps number executed for heap_dijkstra were: "<<heap_dijkstra(&G2,st_pair[j],st_pair[j+1])<<endl;

    gettimeofday(&finish,NULL);
    timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for heap dijkstra was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;
        //running dfs
    cout<<"Running DFS"<<endl;
    gettimeofday(&start,NULL);
    for(j=0;j<10;j+=2)
        output<< "The steps number executed for dfs were: "<<DFS(&G2,st_pair[j],st_pair[j+1])<<endl;

    gettimeofday(&finish,NULL);
    timeval_subtract(&result,&finish,&start);
    cout<< "The total system runtime for normal dfs was"<<result.tv_sec<<" secs and "<<result.tv_usec<<" usecs"<<endl;
#endif // debug
    output.close();
    return 0;
}

