#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <string>

using namespace std;

struct Edge {
string to;
int weight;
};

class Graph {
private:
unordered_map<string, vector<Edge> > adj;

public:

void addEdge(string u, string v, int w) {
adj[u].push_back(Edge{v, w});
adj[v].push_back(Edge{u, w});
}

void dijkstra(string source, string target) {

const int INF = numeric_limits<int>::max();

unordered_map<string, int> dist;
unordered_map<string, string> prev;

if (adj.find(source) == adj.end() ||
adj.find(target) == adj.end()) {

cout << "Error: City not found." << endl;
return;
}

for (auto it = adj.begin(); it != adj.end(); ++it) {
dist[it->first] = INF;
}

priority_queue<
pair<int, string>,
vector<pair<int, string> >,
greater<pair<int, string> >
> pq;

dist[source] = 0;
pq.push(make_pair(0, source));

while (!pq.empty()) {

pair<int, string> current = pq.top();
pq.pop();

int d = current.first;
string u = current.second;

if (d != dist[u])
continue;

if (u == target)
break;

for (size_t i = 0; i < adj[u].size(); i++) {

string v = adj[u][i].to;
int w = adj[u][i].weight;

if (dist[u] != INF && dist[u] + w < dist[v]) {

dist[v] = dist[u] + w;
prev[v] = u;

pq.push(make_pair(dist[v], v));
}
}
}

if (dist[target] == INF) {
cout << "No route found." << endl;
return;
}

vector<string> path;

string at = target;

while (at != source) {
path.push_back(at);
at = prev[at];
}

path.push_back(source);

reverse(path.begin(), path.end());

cout << "\nShortest route: ";

for (size_t i = 0; i < path.size(); i++) {
if (i > 0)
cout << " -> ";

cout << path[i];
}

cout << "\nTotal distance: "
<< dist[target] << " km" << endl;
}
};

int main() {

Graph g;

// Malawi road network

g.addEdge("Lilongwe", "Dowa", 55);
g.addEdge("Lilongwe", "Mchinji", 110);
g.addEdge("Lilongwe", "Kasungu", 120);
g.addEdge("Lilongwe", "Salima", 115);
g.addEdge("Lilongwe", "Dedza", 85);

g.addEdge("Dowa", "Kasungu", 75);
g.addEdge("Dowa", "Salima", 70);

g.addEdge("Kasungu", "Nkhotakota", 105);
g.addEdge("Kasungu", "Mzuzu", 200);

g.addEdge("Salima", "Nkhotakota", 110);
g.addEdge("Salima", "Dedza", 100);

g.addEdge("Nkhotakota", "Nkhata Bay", 95);
g.addEdge("Nkhotakota", "Mzuzu", 160);

g.addEdge("Nkhata Bay", "Mzuzu", 50);
g.addEdge("Mzuzu", "Rumphi", 65);

g.addEdge("Rumphi", "Karonga", 105);
g.addEdge("Karonga", "Chitipa", 90);

g.addEdge("Dedza", "Ntcheu", 80);
g.addEdge("Ntcheu", "Blantyre", 170);
g.addEdge("Ntcheu", "Balaka", 100);

g.addEdge("Blantyre", "Zomba", 65);
g.addEdge("Blantyre", "Mulanje", 70);

g.addEdge("Zomba", "Liwonde", 80);
g.addEdge("Liwonde", "Balaka", 50);

g.addEdge("Liwonde", "Mangochi", 120);
g.addEdge("Balaka", "Mangochi", 105);

g.addEdge("Mangochi", "Monkey Bay", 70);
g.addEdge("Monkey Bay", "Salima", 120);

g.addEdge("Zomba", "Mangochi", 105);
g.addEdge("Mulanje", "Zomba", 75);

g.addEdge("Chitipa", "Rumphi", 85);
g.addEdge("Balaka", "Zomba", 60);

g.addEdge("Kasungu", "Salima", 95);
g.addEdge("Lilongwe", "Nkhotakota", 180);

cout << "Malawi Road Network - Dijkstra Algorithm"
<< endl;

cout << "----------------------------------------"
<< endl;

g.dijkstra("Lilongwe", "Blantyre");

return 0;
}