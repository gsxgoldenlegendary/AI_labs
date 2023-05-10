#include "bits/stdc++.h"

#define INPUT_FILE "./input/input9.txt"
#define OUTPUT_FILE "./output/output9.txt"

#define RANDOM
//most optimal outputs
//input0 11/21/35
//input1 31/60/332
//input2 19/33/350
//input3 53/114/748
//input4 37/69/632
//input5 288/576/23705
//input6 513/1008/49741
//input7 185/378/11673
//input8 1094/2160/154963
//input9 378/720/70560
#define DEBUG

int main() {
    std::ifstream in;
    std::ofstream out;
    auto cinbackup = std::cin.rdbuf(in.rdbuf());
    auto coutbackup = std::cout.rdbuf(out.rdbuf());
    in.open(INPUT_FILE, std::ios::in);
    out.open(OUTPUT_FILE, std::ios::out);
    std::cin.rdbuf(in.rdbuf());
    std::cout.rdbuf(out.rdbuf());

    int N, D, S;
    char comma = ',';
    std::cin >> N >> comma >> D >> comma >> S;
    auto request = new bool[N * D * S];
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < D; y++) {
            for (int z = 0; z < S; z++) {
                std::cin >> request[x * D * S + y * S + z];
                if (z != S - 1)
                    std::cin >> comma;
            }
        }
    }

#ifdef RANDOM

    int min_on_duty = D * S / N;
    int even_on_duty = min_on_duty * N;
    int extra_on_duty = D * S - even_on_duty;

    std::random_device rd;
    std::mt19937_64 e(rd());

    auto arrangement = new std::vector<int>;
    auto sequence = new std::vector<int>;
    for (int i = 0; i < min_on_duty; i++) {
        arrangement->push_back(0);
    }
    for (int i = 0; i <= min_on_duty; i++) {
        sequence->push_back(i);
    }
    for (int i = 1; i < N; i++) {
        std::vector<int> position;
        std::sample(sequence->begin(), sequence->end(),
                    std::back_inserter(position), min_on_duty, e);
        for (int j = 0; j < min_on_duty; j++) {
            sequence->push_back(i * min_on_duty + j + 1);
        }
        int j = 0;
        for (auto x: position) {
            auto it = arrangement->begin();
            std::advance(it, x + j);
            arrangement->insert(it, i);
            j++;
        }
    }

    auto table = new std::vector<std::set<int>>;
    for (int i = 0; i < extra_on_duty; i++) {
        auto tmp_set = new std::set<int>;
        for (int j = 0; j < N; j++) {
            tmp_set->insert(j);
        }
        table->push_back(*tmp_set);
        delete tmp_set;
    }
    if (extra_on_duty != 0 && table->at(0).find(arrangement->at(even_on_duty - 1)) != table->at(0).end()) {
        table->at(0).erase(arrangement->at(even_on_duty - 1));
    }
    for (int i = 0; i < extra_on_duty; i++) {
        auto cur_set = &table->at(i);
        auto it = cur_set->begin();
        std::uniform_int_distribution<unsigned> generator(0, cur_set->size() - 1);
        std::advance(it, generator(e));
        arrangement->push_back(*it);
        if (i != extra_on_duty - 1 && table->at(i + 1).find(*it) != table->at(i + 1).end())
            table->at(i + 1).erase(*it);
    }

    auto personnel = new std::vector<int>;
    for (int i = 0; i < N; i++) {
        personnel->push_back(i);
    }

    std::shuffle(personnel->begin(), personnel->end(), e);
    //do {
    for (int &i: *arrangement) {
        i = personnel->at(i);
    }
    for (int j = 0; j < even_on_duty + extra_on_duty; j++) {
        std::cout << (*arrangement)[j] + 1 << ",\n"[j % S == S - 1];
    }
    int satisfy = 0;
    int total = 0;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < D; y++) {
            for (int z = 0; z < S; z++) {
                if (request[x * D * S + y * S + z]) {
                    total++;
                    if (arrangement->at(y * S + z) == x) {
                        satisfy++;
                    }
                }
            }
        }
    }

    std::cout << satisfy << std::endl;
    //} while (std::next_permutation(personnel->begin(), personnel->end()));
    delete arrangement;
    delete sequence;
    delete table;
    delete personnel;
#endif
    delete[] request;
    std::cin.rdbuf(cinbackup);
    std::cout.rdbuf(coutbackup);
    in.close();
    out.close();
#ifdef DEBUG
    int max_satisfy = D * S;
    std::cout << satisfy << std::endl << max_satisfy << std::endl << total << std::endl;
#endif
    return 0;
}