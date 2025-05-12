#include <cmath>
#include "Environment.h"

Environment::Environment(Pair start, Pair goal,
                         const std::vector<Tuple>& obstacles)
    : start_(start), goal_(goal), obstacles_(obstacles) {}

const Pair& Environment::getGoal() const { return goal_; }
const std::vector<Tuple>& Environment::getObstacles() const { return obstacles_; }

bool Environment::isColliding(const Pair& position) const {
    for (const auto& obstacle : obstacles_) {
        auto [x, y, radius] = obstacle;
        double dist = std::sqrt(std::pow(position.first - x, 2) + std::pow(position.second - y, 2));
        if (dist <= radius) return true;
    }
    return false;
}