#include <iostream>
#include <vector>

int graph[4][4] = {
    {0, 30, 28, 41},  /* Rumah A */
    {30, 0, 18, 15},  /* Rumah B */
    {28, 18, 0, 21},  /* Rumah C */
    {41, 15, 21, 0},  /* Rumah D */
};

std::vector<std::pair<int, int>> Solusi;

bool isVisited(const int& vertex) {
    for (const std::pair<int, int>& i : Solusi) {
        if (vertex == i.first) {
            return true;
        }
    }
    return false;
}

void ShortestRoute(int rumah, int start, int end, int& edge, int& vertex) {
    /* deklarasi */
    int mid;
    static int e[2];
    static int v[2];
    int s[2];
    /* algoritma */
    if (end - start == 1) {
        s[0] = graph[rumah][start];
        s[1] = graph[rumah][end];
        if (s[0] < s[1]) {
            if (s[0] != 0 and s[0] != edge) {
                vertex = start;
                edge = s[0];
            } else {
                vertex = end;
                edge = s[1];
            }
        } else {
            if (s[1] != 0 and s[1] != edge) {
                vertex = end;
                edge = s[1];
            } else {
                vertex = start;
                edge = s[0];
            }
        }
    } else {
        mid = (start + end) / 2;
        ShortestRoute(rumah, start, mid, e[0], v[0]);
        ShortestRoute(rumah, mid + 1, end, e[1], v[1]);
        if (e[0] < e[1]) {
            if (not isVisited(v[0])) {
                vertex = v[1] = v[0];
                edge = e[1] = e[0];
            } else {
                vertex = v[0] = v[1];
                edge = e[0] = e[1];
            }
        } else {
            if (not isVisited(v[1])) {
                vertex = v[0] = v[1];
                edge = e[0] = e[1];
            } else {
                vertex = v[1] = v[0];
                edge = e[1] = e[0];
            }
        }
        if (isVisited(vertex)) {
            Solusi.push_back({rumah, graph[rumah][3]});
            Solusi.push_back({3, 0});
        } else {
            Solusi.push_back({rumah, edge});
            ShortestRoute(vertex, 0, 3, edge, vertex);
        }
    }
}

char Change(int index) {
    switch (index) {
        case 0: return 'A';
        case 1: return 'B';
        case 2: return 'C';
        case 3: return 'D';
    }
    return ' ';
}

int main() {
    static int edge, vertex;
    ShortestRoute(3, 0, 3, edge, vertex);
    int sum = Solusi.at(1).second;
    for (int i = 0; i < Solusi.size() - 1; i++) {
        std::cout << "Kurir pergi dari rumah " << Change(Solusi.at(i).first)
                  << " ke rumah " << Change(Solusi.at(i + 1).first)
                  << " dengan jarak " << Solusi.at(i).second << "m\n";
        sum += Solusi.at(i + 1).second;
    }
    std::cout << "Total perjalanan kurir : " << sum << "m\n";
    return 0;
}
