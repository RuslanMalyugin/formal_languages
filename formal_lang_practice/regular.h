#ifndef REGULAR_H_INCLUDED
#define REGULAR_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>

std::vector <std::vector<bool>>
matrix_and(const std::vector <std::vector<bool>> &first_matrix, const std::vector <std::vector<bool>> &second_matrix);

std::vector <std::vector<bool>>
matrix_or(const std::vector <std::vector<bool>> &first_matrix, const std::vector <std::vector<bool>> &second_matrix);

std::vector <std::vector<bool>>
matrix_star(const std::vector <std::vector<bool>> &first_matrix, const std::vector <std::vector<bool>> &second_matrix);

class regular {
    //a stack of matrices in which the element [i][j] is true if the language currently accepts the word u[i...j]
    std::vector<std::vector<std::vector<bool>>> stack;
    //our expression
    std::string regular_exp;
    //given word
    std::string word;
    //length of word
    int len_word = word.length();
    //input error check
    bool is_correct = true;

    //operations
    bool operation_dot();

    bool operation_plus();

    bool operation_star();

    //character processing in regular expression
    bool processing(char symbol);

    //function for parsing expression
    bool parse_regular();

    //message for wrong input
    static void error_message();

public:
    regular(const std::string &alpha, const std::string &u);

    //fuction for solving our problem
    int longest_common_suffix();
};



#endif
