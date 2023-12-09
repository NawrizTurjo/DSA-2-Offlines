import java.util.*;

public class shortest_bellMan {
    static class Edge {
        int src;
        int dest;
        int wt;

        public Edge(int s, int d, int w) {
            this.src = s;
            this.dest = d;
            this.wt = w;
        }
    }

    public static void createGraph(ArrayList<Edge> graph[]) {
        for (int i = 0; i < graph.length; i++) {
            graph[i] = new ArrayList<Edge>();
        }
        // by default NULL that's why you cannot store any data inside them

        graph[0].add(new Edge(0, 1, 2));
        graph[0].add(new Edge(0, 2, 4));

        graph[1].add(new Edge(1, 2, -4));
        // graph[1].add(new Edge(1, 3, 7));

        graph[2].add(new Edge(2, 3, 2));

        graph[3].add(new Edge(3, 4, 4));

        graph[4].add(new Edge(4, 1, -1));
        // graph[4].add(new Edge(4, 5, 5));

    }

    // O(E + ElogV)
    public static void bellManFord(ArrayList<Edge> graph[], int src, int V) {
        int dist[] = new int[V];
        for (int i = 0; i < V; i++) {
            if (i != src)
                dist[i] = Integer.MAX_VALUE;
        }
        boolean isNeg = false;
        for (int k = 0; k < V - 1; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < graph[i].size(); j++) {
                    Edge e = graph[i].get(j);
                    int u = e.src;
                    int v = e.dest;

                    
                    if (dist[u] != Integer.MAX_VALUE && dist[u] + e.wt < dist[v]) {
                        dist[v] = dist[u] + e.wt;
                    }
                }
            }
        }

        // detect -ve weight cycle
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < graph[i].size(); j++) {
                Edge e = graph[i].get(j);
                int u = e.src;
                int v = e.dest;

                if (dist[u] != Integer.MAX_VALUE && dist[u] + e.wt < dist[v]) {
                    System.out.println("negative weight cycle");
                    isNeg = true;
                }
            }
        }
        if (!isNeg) {
            for (int i = 0; i < V; i++) {
                System.out.print(dist[i] + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int V = 5;
        ArrayList<Edge> graph[] = new ArrayList[V];

        createGraph(graph);

        // //print 2's neighbours
        // for(int i=0;i<graph[2].size();i++)
        // {
        // Edge e = graph[2].get(i);
        // System.out.print(e.dest+", "+e.wt+"\n");
        // }
        // System.out.println();
        // //print 1's neighbours
        // for(int i=0;i<graph[1].size();i++)
        // {
        // Edge e = graph[1].get(i);
        // System.out.print(e.dest+", "+e.wt+"\n");
        // }
        // System.out.println();
        bellManFord(graph, 0, V);

    }
}
