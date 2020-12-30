#include <gtest/gtest.h>

#include "Solution.h"

CFG CreateCFG() {
    CFG cfg{}; //    0    1    2    3    4
    cfg.symbols = {'$', 'S', 'a', 'b', 'c'};
    cfg.rules = {
            {0, {1}}, // S'->S
            {1, {2, 2, 1, 3, 3, 3}}, // S->aaSbbb
            {1, {2, 2, 1, 3}}, // S->aaSb
            {1, {4, 1, 3}}, // S -> cSb
            {1, {1, 4}}, // S -> Sc
            {1, {4}}, // S -> c
    };
    cfg.term_cnt = 3;
    cfg.nonterm_cnt = 2;
    return cfg;
}

EarleyParser CreateParser() {
    auto cfg = CreateCFG();
    EarleyParser algo{cfg};
    algo.configs = std::vector<Configuration>(4, Configuration{});
    Rule initial_rule{0, {1}};
    algo.configs[0].emplace(initial_rule, 0, 0);
    return algo;
}

template<class T>
bool Equal(const std::set<T> &lhs, const std::set<T> &rhs) {
    for (const T &item : lhs) {
        if (rhs.find(item) == rhs.end()) {
            return false;
        }
    }
    return lhs.size() == rhs.size();
}

TEST(TestFunctionality, TestPredict) {
std::set<State> correct_set = {
        {{0, {1}},                0, 0},
        {{1, {1, 4}},             0, 0},
        {{1, {2, 2, 1, 3}},       0, 0},
        {{1, {2, 2, 1, 3, 3, 3}}, 0, 0},
        {{1, {4}},                0, 0},
        {{1, {4, 1, 3}},          0, 0}
};
auto parser = CreateParser();
parser.Predict(0);
ASSERT_TRUE(Equal(parser.configs[0], correct_set));
}

TEST(TestFunctionality, TestScan) {
auto parser = CreateParser();
parser.Predict(0);
parser.Scan("cc", 0);
State result{{1, {4, 1, 3}}, 1, 0};
ASSERT_TRUE(parser.configs[1].find(result) != parser.configs[1].end());
}

TEST(TestFunctionality, TestComplete) {
auto parser = CreateParser();
parser.Predict(0);
parser.Scan("cc", 0);
parser.Predict(1);
parser.Complete(1);
Configuration correct_set = {
        {{0, {1}},                1, 0},
        {{1, {1, 4}},             0, 1},
        {{1, {1, 4}},             1, 0},
        {{1, {2, 2, 1, 3}},       0, 1},
        {{1, {2, 2, 1, 3, 3, 3}}, 0, 1},
        {{1, {4}},                0, 1},
        {{1, {4}},                1, 0},
        {{1, {4, 1, 3}},          0, 1},
        {{1, {4, 1, 3}},          1, 0}};
ASSERT_TRUE(Equal(parser.configs[1], correct_set));
}

TEST(TestFunctionality, TestParser) {
auto cfg = CreateCFG();
EarleyParser parser{cfg};
ASSERT_TRUE(parser.predict("aaaacbbbb"));
ASSERT_FALSE(parser.predict("cccba"));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
