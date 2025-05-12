#ifndef ROBOT_H
#define ROBOT_H
#include <tuple>
#include <utility>

using Pair = std::pair<double, double>;
using Tuple = std::tuple<double, double, double>;

class Robot {
public:
    Robot(const Pair& start);
    const Pair& getPosition() const;
    double getOrientation() const;
    bool isRightFootSupport() const;
    void applyAction(const Tuple& action);

private:
    Pair position_;
    double orientation_;
    bool is_right_foot_support_;
    Tuple adjustActionForFoot(const Tuple& action) const;
};

#endif // ROBOT_H

/*
1. pendefinisian
2. ngambil input sesuai yg di jurnal
3. apply action
*/