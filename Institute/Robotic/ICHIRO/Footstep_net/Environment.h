#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <vector>
#include <tuple>
#include <utility>

using Pair = std::pair<double, double>;
using Tuple = std::tuple<double, double, double>;

class Environment {
public:
    Environment(Pair start, Pair goal,
                const std::vector<Tuple>& obstacles);

    const Pair& getGoal() const;
    const std::vector<Tuple>& getObstacles() const;
    bool isColliding(const Pair& position) const;


private:
    Pair start_;
    Pair goal_;
    std::vector<Tuple> obstacles_;
};

#endif // ENVIRONMENT_H

/*
set environment, isinya :
1. posisi awal(robot)
2. target(bola, atau goal aja biar gampang)
3. obstacle(robot lain atau apa aja), mereka di defined jadi lingkaran gitu

*/