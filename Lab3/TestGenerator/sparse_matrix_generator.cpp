//
// Created by NelosG.
//
#include <ctime>
#include <matrix_generator.h>
#include <random>

double get_row_sum1(const std::vector<double> &row) {
    double res = 0;
    for (int i = 0; i < row.size(); ++i) {
        res += (i + 1) * row[i];
    }
    return res;
}

std::pair<sparse_matrix, std::vector<double>> matrix_generator::generate_sparse(int n, int k) {
    std::vector<std::vector<double>> res(n, std::vector<double>(n, 0));
    std::string s = std::to_string(time(nullptr));
    std::seed_seq seed1(s.begin(), s.end());

    std::mt19937 random(seed1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                res[i][j] = -1. * (random() % matrix_generator::UPPER_BOUND);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        res[i][i] = -get_row_sum1(res[i]);
        if (i == 0) {
            res[i][i] += 1;
        }
    }
    sparse_matrix sp(res);
    return {sp, multiply_by_vector(sp)};
}
