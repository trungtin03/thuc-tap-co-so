#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

const int INF = 1e9;

using namespace std;

class InputOutput {
public:
    static void printResult(const vector<int>& distances) {
        printf("Khoang cach ngan nhat tu dinh %d den cac dinh khac:\n", distances[0]);
        for (size_t i = 1; i < distances.size(); ++i) {
            printf("dinh %zu: ", i);
            if (distances[i] == INF) {
                printf("Khong co duong di.\n");
            } else {
                printf("%d\n", distances[i]);
            }
        }
    }

    static void printNegativeCycle() {
        printf("Do thi chua chu trinh am!\n");
    }

    static void DocFile(const string& filename, int& V, vector<vector<int> >& graph, int& u) {
        FILE* inputFile = fopen(filename.c_str(), "r");
        if (!inputFile) {
            cerr << "Khong the mo file " << filename << endl;
            exit(1);
        }

        fscanf(inputFile, "%d", &V);

        graph.resize(V, vector<int>(V, INF));

        int edges;
        fscanf(inputFile, "%d", &edges);
        for (int i = 0; i < edges; ++i) {
            int from, to, weight;
            fscanf(inputFile, "%d %d %d", &from, &to, &weight);
            graph[from][to] = weight;
        }

        fscanf(inputFile, "%d", &u);

        fclose(inputFile); // Dong file
    }

    static void NhapTuBanPhim(int& V, vector<vector<int> >& graph, int& u) {
        cout << "Nhap so dinh: ";
        cin >> V;

        graph.resize(V, vector<int>(V, INF));

        int edges;
        cout << "Nhap so canh: ";
        cin >> edges;

        for (int i = 0; i < edges; ++i) {
            int from, to, weight;
            cout << "Nhap dinh xuat phat, dinh dich, trong so: ";
            cin >> from >> to >> weight;
            graph[from][to] = weight;
        }

        cout << "Nhap dinh nguon: ";
        cin >> u;
    }

    static int LuaChonNhap() {
        int luaChon;
        cout << "Ban muon doc tu file hay nhap tu ban phim?" << endl;
        cout << "1. Doc tu file." << endl;
        cout << "2. Nhap tu ban phim." << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;
        return luaChon;
    }
};


class ShortestPathAlgorithm {
public:
    virtual void findShortestPath(int source, vector<vector<int> >& graph) = 0;
};

class Dijkstra : public ShortestPathAlgorithm {
public:
    void findShortestPath(int source, vector<vector<int> >& graph) override {
        int V = graph.size();
        vector<int> distances(V, INF);
        vector<bool> visited(V, false);
        distances[source] = 0;

        // Priority queue de lua chon dinh có khoang cach ngan nhat
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            if (visited[u]) continue;
            visited[u] = true;

            for (int v = 0; v < V; ++v) {
                if (!visited[v] && graph[u][v] != INF && distances[u] + graph[u][v] < distances[v]) {
                    distances[v] = distances[u] + graph[u][v];
                    pq.push({distances[v], v});
                }
            }
        }

        InputOutput::printResult(distances);
    }
};

class BellmanFord : public ShortestPathAlgorithm {
public:
    void findShortestPath(int source, vector<vector<int> >& graph) override {
        int V = graph.size();
        vector<int> distances(V, INF);
        vector<int> parent(V, -1);
        distances[source] = 0;

        // Relax all edges V-1 times
        for (int k = 0; k < V - 1; ++k) {
            for (int u = 0; u < V; ++u) {
                for (int v = 0; v < V; ++v) {
                    if (graph[u][v] != INF && distances[u] != INF && distances[u] + graph[u][v] < distances[v]) {
                        distances[v] = distances[u] + graph[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative cycles
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (graph[u][v] != INF && distances[u] != INF && distances[u] + graph[u][v] < distances[v]) {
                    // Negative cycle found
                    InputOutput::printNegativeCycle();
                    return;
                }
            }
        }

        // Negative cycle not found, print the result
        InputOutput::printResult(distances);
    }
};

int main() {
    Dijkstra dijkstra;
    BellmanFord bellmanFord;
    int V;
    vector<vector<int> > graph;
    int source;
    int luaChon = InputOutput::LuaChonNhap();
    if (luaChon == 1) {
        string filename;
        cout << "Nhap ten file: ";
        cin >> filename;
        InputOutput::DocFile(filename, V, graph, source);
    } else if (luaChon == 2) {
        InputOutput::NhapTuBanPhim(V, graph, source);
    } else {
        cout << "Lua chon khong hop le." << endl;
        return 1;
    }

    // Check if the graph has negative weights
    bool hasNegativeWeight = false;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (graph[i][j] < 0) {
                hasNegativeWeight = true;
                break;
            }
        }
        if (hasNegativeWeight) {
            break;
        }
    }

    if (hasNegativeWeight) {
        cout << "Do thi co chua trong so am." << endl;

        printf("\nThuat toan Bellman-Ford:\n");
        bellmanFord.findShortestPath(source, graph);
    } else {
        printf("\nThuat toan Dijkstra:\n");
        dijkstra.findShortestPath(source, graph);
    }

    return 0;
}

