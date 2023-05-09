#include "bits/stdc++.h"
//#define DEBUG
#define INPUT_FILE "./input/input0.txt"
#define OUTPUT_FILE "./output/output0.txt"

constexpr int MAX_LENGTH = 1000;

enum Direction {
    TOP_LEFT = 4,
    TOP_RIGHT = 3,
    BOTTOM_LEFT = 1,
    BOTTOM_RIGHT = 2
};

struct Node {
    bool matrix[12][12]{false};
    int f{0}, g{0}, h{0};
    std::vector<std::tuple<int, int, Direction>> steps;
};

int N;

int h_func(const Node *n) {
    int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (n->matrix[i][j])
                cnt++;
    return cnt;
}

auto compare = [](const Node *a, const Node *b) {
    return a->f < b->f;
};

std::multiset<Node *, decltype(compare)> edge_set(compare);

std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>> set_L(int i, int j, Direction s) {
    switch (s) {
        case TOP_LEFT:
            return std::make_tuple(std::make_pair(i, j), std::make_pair(i + 1, j), std::make_pair(i, j + 1));
        case TOP_RIGHT:
            return std::make_tuple(std::make_pair(i, j + 1), std::make_pair(i, j), std::make_pair(i + 1, j + 1));
        case BOTTOM_LEFT:
            return std::make_tuple(std::make_pair(i + 1, j), std::make_pair(i + 1, j + 1), std::make_pair(i, j));
        case BOTTOM_RIGHT:
            return std::make_tuple(std::make_pair(i + 1, j + 1), std::make_pair(i, j + 1), std::make_pair(i + 1, j));
    }
}

int main() {
    std::ifstream in;
    std::ofstream out;
    auto cinbackup = std::cin.rdbuf(in.rdbuf());
    auto coutbackup = std::cout.rdbuf(out.rdbuf());

    in.open(INPUT_FILE, std::ios::in);
    out.open(OUTPUT_FILE, std::ios::out);
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());
    std::cin >> N;

    auto base_node = new Node;
    auto result_node = new Node;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            std::cin >> base_node->matrix[i][j];
    base_node->h = h_func(base_node);
    base_node->f = base_node->g + base_node->h;
    edge_set.insert(base_node);

    for (; (*edge_set.begin())->h != 0;) {
        auto top = *edge_set.begin();
        edge_set.erase(edge_set.begin());
        for (int i = 0; i < N - 1; i++) {
            for (int j = 0; j < N - 1; j++) {
                for (int k = 1; k <= 4; k++) {
                    auto location = set_L(i, j, Direction(k));
                    if (top->matrix[std::get<0>(location).first][std::get<0>(location).second] ||
                        top->matrix[std::get<1>(location).first][std::get<1>(location).second] ||
                        top->matrix[std::get<2>(location).first][std::get<2>(location).second]) {
                        auto new_node = new Node;
                        memcpy(new_node->matrix, top->matrix, sizeof(top->matrix));
                        new_node->matrix[std::get<0>(location).first][std::get<0>(
                                location).second] = !new_node->matrix[std::get<0>(location).first][std::get<0>(
                                location).second];
                        new_node->matrix[std::get<1>(location).first][std::get<1>(
                                location).second] = !new_node->matrix[std::get<1>(location).first][std::get<1>(
                                location).second];
                        new_node->matrix[std::get<2>(location).first][std::get<2>(
                                location).second] = !new_node->matrix[std::get<2>(location).first][std::get<2>(
                                location).second];
                        new_node->steps = top->steps;
                        new_node->steps.emplace_back(std::get<0>(location).first, std::get<0>(location).second, Direction(k));
                        new_node->g = top->g + 3;
                        new_node->h = h_func(new_node);
                        new_node->f = new_node->g + new_node->h;
                        edge_set.insert(new_node);
                        if (new_node->h == 0) {
                            result_node = new_node;
                            goto A;
                        }
                    }
                }
                if (edge_set.size() > MAX_LENGTH) {
                    for (int k = 0; k < 10; k++) {
                        delete *--edge_set.end();
                        edge_set.erase(--edge_set.end());
                    }
                }
            }
        }
    }
    A:
    std::cout << result_node->steps.size() << std::endl;
    for (auto x: result_node->steps)
        std::cout << std::get<0>(x) << " " << std::get<1>(x) << " " << std::get<2>(x) << std::endl;
    std::cin.rdbuf(cinbackup);
    std::cout.rdbuf(coutbackup);
    in.close();
    out.close();
#ifdef DEBUG
    cinbackup = std::cin.rdbuf(in.rdbuf());
    in.open(OUTPUT_FILE, std::ios::in);
    std::cin.rdbuf(in.rdbuf());
    int M;
    std::cin >> M;
    for (int k = 0; k < M; k++) {
        int i, j, s;
        std::cin >> i >> j >> s;
        switch (Direction(s)) {
            case TOP_LEFT:
                base_node->matrix[i][j] = !base_node->matrix[i][j];
                base_node->matrix[i + 1][j] = !base_node->matrix[i + 1][j];
                base_node->matrix[i][j + 1] = !base_node->matrix[i][j + 1];
                break;
            case TOP_RIGHT:
                base_node->matrix[i][j] = !base_node->matrix[i][j];
                base_node->matrix[i][j - 1] = !base_node->matrix[i][j - 1];
                base_node->matrix[i + 1][j] = !base_node->matrix[i + 1][j];
                break;
            case BOTTOM_LEFT:
                base_node->matrix[i][j] = !base_node->matrix[i][j];
                base_node->matrix[i][j + 1] = !base_node->matrix[i][j + 1];
                base_node->matrix[i - 1][j] = !base_node->matrix[i - 1][j];
                break;
            case BOTTOM_RIGHT:
                base_node->matrix[i][j] = !base_node->matrix[i][j];
                base_node->matrix[i - 1][j] = !base_node->matrix[i - 1][j];
                base_node->matrix[i][j - 1] = !base_node->matrix[i][j - 1];
                break;
        }
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            std::cout << base_node->matrix[i][j] << " \n"[j == N - 1];
    std::cin.rdbuf(cinbackup);
    in.close();
#endif
    return 0;
}