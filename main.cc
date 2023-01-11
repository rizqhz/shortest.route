#include <iostream>
#include <vector>

int graph[4][4] = {
    {0, 30, 28, 41},    // A
    {30, 0, 18, 15},    // B
    {28, 18, 0, 21},    // C
    {41, 15, 21, 0},    // D
};

std::vector<std::pair<int, int>> solusi;

bool isVisited(int vertex) {
    for (const std::pair<int, int> &i : solusi) {
        if (vertex == i.first) {
            return true;
        }
    }
    return false;
}

void FindShortest(int n, int start, int end, int& edge, int& vertex) {
    if (end - start == 1) {
        int s[2] = {
            graph[n][start],
            graph[n][end],
        };
        if (s[0] < s[1]) {
            vertex = s[0] != 0 and s[0] != edge ? start : end;
            edge = s[0] != 0 and s[0] != edge ? s[0] : s[1];
        } else {
            vertex = s[1] != 0 and s[1] != edge ? end : start;
            edge = s[1] != 0 and s[1] != edge ? s[1] : s[0];
        }
        return;
    }
    int mid = (start + end) / 2;
    static int e[2], v[2];
    FindShortest(n, start, mid, e[0], v[0]);
    FindShortest(n, mid + 1, end, e[1], v[1]);
    if (e[0] < e[1]) {
        edge = e[1] = not isVisited(v[0]) ? e[0] : e[1];
        vertex = v[1] = not isVisited(v[0]) ? v[0] : v[1];
    } else {
        edge = e[0] = not isVisited(v[1]) ? e[1] : e[0];
        vertex = v[0] = not isVisited(v[1]) ? v[1] : v[0];
    }
    if (isVisited(vertex)) {
        solusi.push_back({n, graph[n][3]});
        solusi.push_back({3, 0});
    } else {
        solusi.push_back({n, edge});
        FindShortest(vertex, 0, 3, edge, vertex);
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

void CheckSolusi() {
    int sum = 0;
    for (int i = 0; i < solusi.size() - 1; i++) {
        std::cout << "Kurir pergi dari rumah " << Change(solusi.at(i).first)
                  << " ke rumah " << Change(solusi.at(i + 1).first)
                  << " dengan jarak " << solusi.at(i).second << "m\n";
        sum += solusi.at(i).second;
    }
    std::cout << "Total perjalanan kurir : " << sum << "m"
              << std::endl;
}

int main() {
    static int edge, vertex, sum;
    FindShortest(3, 0, 3, edge, vertex);
    CheckSolusi();
    return 0;
}
