#include "Solution.h"

static short LexSort(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    size_t size = std::min(lhs.size(), rhs.size());
    for (size_t i = 0; i < size; ++i) {
        if (lhs[i] > rhs[i]) {
            return 1;
        } else if (lhs[i] < rhs[i]) {
            return -1;
        }
    }
    if (rhs.size() > lhs.size()) {
        return -1;
    }
    if (rhs.size() < lhs.size()) {
        return 1;
    }
    return 0;
}

bool Rule::operator<(const Rule &rule2) const {
    if (lhs == 0 && rule2.lhs > 0) {
        return true;
    }
    if (rule2.lhs == 0) {
        return false;
    }
    return (lhs < rule2.lhs) ||
           (lhs == rule2.lhs && LexSort(rhs, rule2.rhs) < 0);
}

bool Rule::operator==(const Rule &rule2) const {
    if (lhs != rule2.lhs) {
        return false;
    }
    if (rhs.size() != rule2.rhs.size()) {
        return false;
    }
    return LexSort(rhs, rule2.rhs) == 0;
}

State::State() = default;

State::State(Rule rule, int dot, int pos)
        : rule(std::move(rule)), dot(dot), pos(pos) {}

bool State::operator<(const State &state2) const {
    return (rule < state2.rule) || (rule == state2.rule && dot < state2.dot) ||
           (rule == state2.rule && dot == state2.dot && pos < state2.pos);
}

bool State::operator==(const State &state2) const {
    return (rule == state2.rule && dot == state2.dot && pos == state2.pos);
}

bool CFG::IsTerminal(int idx) const { return idx >= nonterm_cnt; }

EarleyParser::EarleyParser() = default;

EarleyParser::EarleyParser(CFG cfg) : cfg(std::move(cfg)) {}

void EarleyParser::Predict(int j) {
    auto copy = configs[j];
    for (const auto &state : configs[j]) {
        if (state.dot < state.rule.rhs.size() &&
            !cfg.IsTerminal(state.rule.rhs[state.dot])) {
            for (const auto &rule : cfg.rules) {
                if (rule.lhs == state.rule.rhs[state.dot]) {
                    copy.emplace(rule, 0, j);
                }
            }
        }
    }
    configs[j] = std::move(copy);
}

void EarleyParser::Scan(const std::string &word, int j) {
    for (const auto &state : configs[j]) {
        if (state.dot < state.rule.rhs.size() &&
            cfg.IsTerminal(state.rule.rhs[state.dot])) {
            if (cfg.symbols[state.rule.rhs[state.dot]] == word[j]) {
                configs[j + 1].emplace(state.rule, state.dot + 1, state.pos);
            }
        }
    }
}

void EarleyParser::Complete(int j) {
    auto copy = configs[j];
    for (const auto &state : configs[j]) {
        if (state.dot == state.rule.rhs.size()) {
            for (const auto &state2 : configs[state.pos]) {
                if (state2.dot < state2.rule.rhs.size() &&
                    state2.rule.rhs[state2.dot] == state.rule.lhs) {
                    copy.emplace(state2.rule, state2.dot + 1, state2.pos);
                }
            }
        }
    }
    configs[j] = std::move(copy);
}

bool EarleyParser::predict(const std::string &word) {
    configs = std::vector<Configuration>(word.size() + 1, Configuration{});
    Rule initial_rule{0, {1}};
    configs[0].emplace(initial_rule, 0, 0);
    size_t old_size = configs[0].size();
    size_t new_size = old_size;
    do {
        old_size = new_size;
        Predict(0);
        Complete(0);
        new_size = configs[0].size();
    } while (old_size != new_size);
    for (int j = 1; j < configs.size(); ++j) {
        Scan(word, j - 1);
        old_size = configs[j].size();
        new_size = old_size;
        do {
            old_size = new_size;
            Predict(j);
            Complete(j);
            new_size = configs[j].size();
        } while (old_size != new_size);
    }
    auto res_state = State{initial_rule, 1, 0};
    return configs[word.size()].find(res_state) != configs[word.size()].end();
}

std::ostream &operator<<(std::ostream &out, const EarleyParser &algo) {
    int i = 0;
    for (const auto &config : algo.configs) {
        std::cout << 'D' << i << ": {";
        for (const auto &state : config) {
            std::cout << '(' << algo.cfg.symbols[state.rule.lhs] << "->";
            for (size_t j = 0; j < state.rule.rhs.size(); ++j) {
                if (j == state.dot) {
                    std::cout << '*';
                }
                std::cout << algo.cfg.symbols[state.rule.rhs[j]];
            }
            if (state.dot == state.rule.rhs.size()) {
                std::cout << '*';
            }
            std::cout << ", " << state.pos << "), ";
        }
        std::cout << "}\n";
        ++i;
    }
    return out;
}
