#include <iostream>
#include <string>
#include <vector>
#include "regular.h"

using std::vector;

//matrix_or - this is matrix sum
vector<vector<bool>> matrix_or(const vector<vector<bool>> &first_matrix, const vector<vector<bool>> &second_matrix) {
    int size = first_matrix.size();
    vector<vector<bool>> res = vector<vector<bool>>(size, vector<bool>(size, false));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (first_matrix[i][j] || second_matrix[i][j])
                res[i][j] = true;
        }
    }
    return res;
}

//matrix_and - this is matrix multiplication
vector<vector<bool>> matrix_and(const vector<vector<bool>> &first_matrix, const vector<vector<bool>> &second_matrix) {
    int size = first_matrix.size();
    vector<vector<bool>> res = vector<vector<bool>>(size, vector<bool>(size, false));
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            for (int k = i; k <= j; k++) {
                if (first_matrix[i][k] && second_matrix[k][j]) {
                    res[i][j] = true;
                    break;
                }
            }
        }
    }
    return res;
}

//matrix star - this operation is similar to multiplication, but with the addition of empty steps (epsilon)
vector<vector<bool>> matrix_star(const vector<vector<bool>> &first_matrix) {
    int size = first_matrix.size();
    vector<vector<bool>> res = vector<vector<bool>>(size, vector<bool>(size, false));
    for (int i = 0; i < size; i++) {
        res[i][i] = true;
        for (int j = i + 1; j < size; j++) {
            for (int k = i; k <= j; k++) {
                if (!res[i][k])
                    continue;
                if (first_matrix[k][j]) {
                    res[i][j] = true;
                    break;
                }
            }
        }
    }
    return res;
}


regular::regular(const std::string &alpha, const std::string &u) : regular_exp(alpha), word(u) {
    is_correct = parse_regular();
}
void regular::error_message() {
    std::cout << "ERROR";
}

bool regular::operation_dot() {
    if (stack.size() < 2) {
        error_message();
        return false;
    }
    vector<vector<bool>> first_matrix = stack[stack.size() - 2];
    vector<vector<bool>> second_matrix = stack[stack.size() - 1];
    stack.pop_back();
    stack.pop_back();
    vector<vector<bool>> res = matrix_and(first_matrix, second_matrix);
    stack.push_back(res);
    return true;
}

bool regular::operation_plus() {
    if (stack.size() < 2) {
        error_message();
        return false;
    }
    vector<vector<bool>> first_matrix = stack[stack.size() - 1];
    vector<vector<bool>> second_matrix = stack[stack.size() - 2];
    stack.pop_back();
    stack.pop_back();
    vector<vector<bool>> res = matrix_or(first_matrix, second_matrix);
    stack.push_back(res);
    return true;
}

bool regular::operation_star() {
    if (stack.empty()) {
        error_message();
        return false;
    }
    vector<vector<bool>> first_matrix = stack[stack.size() - 1];
    stack.pop_back();
    vector<vector<bool>> res = matrix_star(first_matrix);
    stack.push_back(res);
    return true;
}

bool regular::processing(char symbol) {
    if (symbol >= 'a' && symbol <= 'c') {
        vector<vector<bool>> res = vector<vector<bool>>(len_word + 1, vector<bool>(len_word + 1, false));
        for (int i = 0; i < len_word; i++) {
            if (word[i] == symbol) {
                res[i][i + 1] = true;
            }
        }
        stack.push_back(res);
        return true;
    }

    if (symbol == '1') {
        vector<vector<bool>> res = vector<vector<bool>>(len_word + 1, vector<bool>(len_word + 1, false));
        for (int i = 0; i <= len_word; i++) {
            res[i][i] = true;
        }
        stack.push_back(res);
        return true;
    }

    switch (symbol) {
        case '.':
            return operation_dot();
        case '*':
            return operation_star();
        case '+':
            return operation_plus();
    }
    error_message();
    return false;
}

bool regular::parse_regular() {
    for (int i = 0; i < regular_exp.length(); i++) {
        if (!processing(regular_exp[i]))
            return false;
    }
    if (stack.size() != 1) {
        error_message();
        return false;
    }
    return true;
}

int regular::longest_common_suffix() {
    if (is_correct) {
        for (int i = 0; i < len_word; i++) {
            if (stack[0][i][len_word]) {
                return len_word - i;
            }
        }
        return 0;
    }
    return 0;
}
