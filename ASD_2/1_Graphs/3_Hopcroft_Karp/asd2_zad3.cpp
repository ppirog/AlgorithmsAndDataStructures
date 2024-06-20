// C++ implementation of Hopcroft Karp algorithm for
// maximum matching
#include<bits/stdc++.h>

using namespace std;
#define NIL 0
#define INF INT_MAX

// A class to represent Bipartite graph for Hopcroft
// Karp implementation
class BipGraph {
    // m and n are number of vertices on left
    // and right sides of Bipartite Graph
    int m, n;

    // adj[u] stores adjacents of left side
    // vertex 'u'. The value of u ranges from 1 to m.
    // 0 is used for dummy vertex
    list<int> *adj;

    // These are basically pointers to arrays needed
    // for hopcroftKarp()
    int *pairU, *pairV, *dist;

public:
    BipGraph(int m, int n); // Constructor
    void addEdge(int u, int v); // To add edge

    // Returns true if there is an augmenting path
    bool bfs();

    // Adds augmenting path if there is one beginning
    // with u
    bool dfs(int u);

    // Returns size of maximum matching
    int hopcroftKarp();
};

// Returns size of maximum matching
int BipGraph::hopcroftKarp() {
    // pairU[u] stores pair of u in matching where u
    // is a vertex on left side of Bipartite Graph.
    // If u doesn't have any pair, then pairU[u] is NIL
    pairU = new int[m + 1];

    // pairV[v] stores pair of v in matching. If v
    // doesn't have any pair, then pairU[v] is NIL
    pairV = new int[n + 1];

    // dist[u] stores distance of left side vertices
    // dist[u] is one more than dist[u'] if u is next
    // to u'in augmenting path
    dist = new int[m + 1];

    // Initialize NIL as pair of all vertices
    for (int u = 0; u <= m; u++)
        pairU[u] = NIL;
    for (int v = 0; v <= n; v++)
        pairV[v] = NIL;

    // Initialize result
    int result = 0;

    // Keep updating the result while there is an
    // augmenting path.
    while (bfs()) {
        // Find a free vertex
        for (int u = 1; u <= m; u++)

            // If current vertex is free and there is
            // an augmenting path from current vertex
            if (pairU[u] == NIL && dfs(u))
                result++;
    }
    return result;
}

// Returns true if there is an augmenting path, else returns
// false
bool BipGraph::bfs() {
    queue<int> Q; //an integer queue

    // First layer of vertices (set distance as 0)
    for (int u = 1; u <= m; u++) {
        // If this is a free vertex, add it to queue
        if (pairU[u] == NIL) {
            // u is not matched
            dist[u] = 0;
            Q.push(u);
        }

            // Else set distance as infinite so that this vertex
            // is considered next time
        else dist[u] = INF;
    }

    // Initialize distance to NIL as infinite
    dist[NIL] = INF;

    // Q is going to contain vertices of left side only.
    while (!Q.empty()) {
        // Dequeue a vertex
        int u = Q.front();
        Q.pop();

        // If this node is not NIL and can provide a shorter path to NIL
        if (dist[u] < dist[NIL]) {
            // Get all adjacent vertices of the dequeued vertex u
            list<int>::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i) {
                int v = *i;

                // If pair of v is not considered so far
                // (v, pairV[V]) is not yet explored edge.
                if (dist[pairV[v]] == INF) {
                    // Consider the pair and add it to queue
                    dist[pairV[v]] = dist[u] + 1;
                    Q.push(pairV[v]);
                }
            }
        }
    }

    // If we could come back to NIL using alternating path of distinct
    // vertices then there is an augmenting path
    return (dist[NIL] != INF);
}

// Returns true if there is an augmenting path beginning with free vertex u
bool BipGraph::dfs(int u) {
    if (u != NIL) {
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i) {
            // Adjacent to u
            int v = *i;

            // Follow the distances set by BFS
            if (dist[pairV[v]] == dist[u] + 1) {
                // If dfs for pair of v also returns
                // true
                if (dfs(pairV[v]) == true) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }

        // If there is no augmenting path beginning with u.
        dist[u] = INF;
        return false;
    }
    return true;
}

// Constructor
BipGraph::BipGraph(int m, int n) {
    this->m = m;
    this->n = n;
    adj = new list<int>[m + 1];
}

// To add edge from u to v and v to u
void BipGraph::addEdge(int u, int v) {
    adj[u].push_back(v); // Add u to v’s list.
}

#include<bits/stdc++.h>
#include <set>
#include <vector>

using namespace std;

int indeksDlaBialych = 1;
int indeksDlaCzarnych = 1;

class Element {
public:
    int indeksWpisywania = 0;
    int operacja = 0;
    bool czarny = false;
    bool odwiedzony = false;
    int nowyIndeks = 0;
    vector<int> sasiedzi;
};


int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;

    auto **tab = new Element *[n];
    for (int i = 0; i < n; i++) {
        tab[i] = new Element[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tab[i][j].operacja;

            tab[i][j].indeksWpisywania = i * n + j;

            if ((i + j) % 2 == 0) {
                tab[i][j].czarny = true;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Element &aktulany = tab[i][j];

            int operacja = aktulany.operacja;
            if (operacja == 0) { continue; }

            //najpierw czarni
            if (tab[i][j].czarny) {
                if (operacja == 1) {

                    //dodaj sasiada o 3 na prawo
                    if (j + 3 < n) {
                        Element &sasiad = tab[i][j + 3];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w prawo i 1 w dol
                    if (j + 2 < n && i + 1 < n) {
                        Element &sasiad = tab[i + 1][j + 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w prawo i 1 w gore
                    if (j + 2 < n && i - 1 >= 0) {
                        Element &sasiad = tab[i - 1][j + 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                }
                if (operacja == 2) {

                    //dodaj sasiada o 1 w prawo
                    if (j + 1 < n) {
                        Element &sasiad = tab[i][j + 1];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 1 w dol
                    if (i + 1 < n) {
                        Element &sasiad = tab[i + 1][j];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 1 w gore
                    if (i - 1 >= 0) {
                        Element &sasiad = tab[i - 1][j];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }
                }
                if (operacja == 3) {

                    //dodaj sasiada o 1 w prawo
                    if (j + 1 < n) {
                        Element &sasiad = tab[i][j + 1];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w prawo i 1 w dol
                    if (j + 2 < n && i + 1 < n) {
                        Element &sasiad = tab[i + 1][j + 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w prawo i 1 w gore
                    if (j + 2 < n && i - 1 >= 0) {
                        Element &sasiad = tab[i - 1][j + 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaBialych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaCzarnych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }
                }
            } else {
                if (operacja == 1) {

                    //dodaj sasiada o 3 na lewo
                    if (j - 3 >= 0) {
                        Element &sasiad = tab[i][j - 3];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w lewo i 1 w dol
                    if (j - 2 >= 0 && i + 1 < n) {
                        Element &sasiad = tab[i + 1][j - 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w lewo i 1 w gore
                    if (j - 2 >= 0 && i - 1 >= 0) {
                        Element &sasiad = tab[i - 1][j - 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }
                }
                if (operacja == 2) {

                    //dodaj sasiada o 1 w lewo
                    if (j - 1 >= 0) {
                        Element &sasiad = tab[i][j - 1];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 1 w dol
                    if (i + 1 < n) {
                        Element &sasiad = tab[i + 1][j];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 1 w gore
                    if (i - 1 >= 0) {
                        Element &sasiad = tab[i - 1][j];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }
                }
                if (operacja == 3) {
                    //dodaj sasiada o 1 w lewo
                    if (j - 1 >= 0) {
                        Element &sasiad = tab[i][j - 1];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w lewo i 1 w dol
                    if (j - 2 >= 0 && i + 1 < n) {
                        Element &sasiad = tab[i + 1][j - 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }

                    //dodaj sasiada o 2 w lewo i 1 w gore
                    if (j - 2 >= 0 && i - 1 >= 0) {
                        Element &sasiad = tab[i - 1][j - 2];
                        if (sasiad.operacja != 0) {
                            if (!sasiad.odwiedzony) {
                                sasiad.nowyIndeks = indeksDlaCzarnych++;
                            }
                            if (aktulany.nowyIndeks == 0) {
                                aktulany.nowyIndeks = indeksDlaBialych++;
                                aktulany.odwiedzony = true;
                            }
                            sasiad.odwiedzony = true;

                            aktulany.sasiedzi.push_back(sasiad.nowyIndeks);
                        }
                    }
                }
            }
        }
    }


//    cout << "-------------------" << endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            auto number = tab[i][j].indeksWpisywania;
//            cout << number << "\t";
//        }
//        cout << endl;
//    }
//    cout << "-------------------" << endl;
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            auto number = tab[i][j].czarny;
//            cout << number << "\t";
//        }
//        cout << endl;
//    }
//    cout << "-------------------" << endl;
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            auto number = tab[i][j].operacja;
//            cout << number << "\t";
//        }
//        cout << endl;
//    }
//    cout << "-------------------" << endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            auto number = tab[i][j].nowyIndeks;
//            cout << number << "\t";
//        }
//        cout << endl;
//    }
//    cout << "-------------------" << endl;
//
//    //wypisz sasiadow
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            auto sasiedzi = tab[i][j].sasiedzi;
//            cout << "Sasiedzi dla " << tab[i][j].indeksWpisywania << ": ";
//            for (int sasiad: sasiedzi) {
//                cout << sasiad << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    //wypisz sasiadow po nowych indeksach dla czarnych jak nowy indeks jest wiekszy od 0
//    cout << "-------------------" << endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (tab[i][j].nowyIndeks > 0 && tab[i][j].czarny) {
//                auto sasiedzi = tab[i][j].sasiedzi;
//                cout << "Sasiedzi dla " << tab[i][j].nowyIndeks << ": ";
//                for (int sasiad: sasiedzi) {
//                    cout << sasiad << " ";
//                }
//                cout << endl;
//            }
//        }
//    }
//
//    //wypisz sasiadow po nowych indeksach dla bialych
//    cout << "-------------------" << endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            if (tab[i][j].nowyIndeks > 0 && !tab[i][j].czarny) {
//                auto sasiedzi = tab[i][j].sasiedzi;
//                cout << "Sasiedzi dla " << tab[i][j].nowyIndeks << ": ";
//                for (int sasiad: sasiedzi) {
//                    cout << sasiad << " ";
//                }
//                cout << endl;
//            }
//        }
//    }

    map<int, vector<int>> ostateczne;

    //dodaj czarne do mapy
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto &aktualny = tab[i][j];
            if (aktualny.nowyIndeks > 0 && aktualny.czarny) {
                ostateczne[aktualny.nowyIndeks] = aktualny.sasiedzi;
            }
        }
    }

    //dodaj biale do mapy
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto &aktualny = tab[i][j];
            if (aktualny.nowyIndeks > 0 && !aktualny.czarny) {
                for (int sasiad: aktualny.sasiedzi) {
                    ostateczne[sasiad].push_back(aktualny.nowyIndeks);
                }
            }
        }
    }

    BipGraph g(indeksDlaCzarnych, indeksDlaBialych);

    for (auto &it: ostateczne) {
        for (int sasiad: it.second) {
            g.addEdge(it.first, sasiad);
        }
    }

    cout << n * n - g.hopcroftKarp();

    return 0;
}
