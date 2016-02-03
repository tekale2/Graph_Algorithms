max_bandwidth: main.cpp dijkstra.cpp kruskal.cpp
	g++ -o max_bandwidth main.cpp dijkstra.cpp kruskal.cpp
clean:
	rm -f *.o max_bandwidth*
