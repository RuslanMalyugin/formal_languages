#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <set>
#include <string>
#include <vector>

struct Rule {
    int lhs;
    std::vector<int> rhs;

    bool operator<(const Rule &rule2) const;

    bool operator==(const Rule &rule2) const;
};


struct State {
    Rule rule;
    int dot{};
    int pos{};

    State();

    State(Rule rule, int dot, int pos);

    bool operator<(const State &state2) const;

    bool operator==(const State &state2) const;
};


struct CFG {
    std::set<Rule> rules;
    std::vector<char> symbols;
    int nonterm_cnt;
    int term_cnt;
    friend class Algo;

    bool IsTerminal(int idx) const;
};

using Configuration = std::set<State>;

struct EarleyParser {
    EarleyParser();

    EarleyParser(CFG cfg);

    bool predict(const std::string &word);

    std::vector<Configuration> configs;
    CFG cfg;

    void Predict(int j);

    void Scan(const std::string &word, int j);

    void Complete(int j);

    friend std::ostream &operator<<(std::ostream &out, const EarleyParser &algo);
};

#endif  // SOLUTION_H
