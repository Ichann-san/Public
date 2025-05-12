#include "Robot.h"

Robot::Robot(const Pair& start)
    : position_(start), orientation_(0.0), is_right_foot_support_(true) {}

const Pair& Robot::getPosition() const { return position_; }
double Robot::getOrientation() const { return orientation_; }
bool Robot::isRightFootSupport() const { return is_right_foot_support_; }

void Robot::applyAction(const Tuple& action) {
    auto [dx, dy, dtheta] = adjustActionForFoot(action);
    position_.first += dx;
    position_.second += dy;
    orientation_ += dtheta;
    is_right_foot_support_ = !is_right_foot_support_;
}

Tuple Robot::adjustActionForFoot(const Tuple& action) const {
    auto [dx, dy, dtheta] = action;
    return is_right_foot_support_ ? action : Tuple(dx, -dy, -dtheta);
}
