#include "Planner.h"
#include <cmath>
#include <iostream>
#define _USE_MATH_DEFINES

Planner::Planner(double max_x, double max_y, double max_theta, const Environment& env, Robot& robot)
    : max_x_(max_x), max_y_(max_y), max_theta_(max_theta), env_(env), robot_(robot),
      accessibility_length_(0.5), accessibility_width_(0.5), accessibility_yaw_(M_PI / 4.0) {}

void Planner::configureAccessibility(double length, double width, double yaw) {
    accessibility_length_ = length;
    accessibility_width_ = width;
    accessibility_yaw_ = yaw;
}

void Planner::planPathIteratively(int max_steps, double place_threshold) {
    int steps = 0;
    bool goal_reached = false;

    while (!goal_reached && steps<max_steps) {
        steps++;
        auto current_pos = robot_.getPosition();
        auto goal_pos = env_.getGoal();
        double dx = goal_pos.first - current_pos.first;
        double dy = goal_pos.second - current_pos.second;
        double error_distance = std::sqrt(dx * dx + dy * dy);
        double error_yaw = std::atan2(dy, dx);

        if (error_distance < place_threshold) { //place treshold nih batas yg bisa dianggap 'oke'
            goal_reached = true;
            std::cout << "Goal reached after " << steps << " steps!" << std::endl;
            break;
        }

        if (dx > accessibility_length_) dx = accessibility_length_;
        if (dx < -accessibility_length_) dx = -accessibility_length_;
        if (dy > accessibility_width_) dy = accessibility_width_;
        if (dy < -accessibility_width_) dy = -accessibility_width_;
        if (error_yaw > accessibility_yaw_) error_yaw = accessibility_yaw_;
        if (error_yaw < -accessibility_yaw_) error_yaw = -accessibility_yaw_;

        Tuple next_action = std::make_tuple(dx, dy, error_yaw); //apply action si robot
        if (!env_.isColliding({robot_.getPosition().first + dx, robot_.getPosition().second + dy})) {//ini case nabrak
            robot_.applyAction(next_action);
        } else {
            std::cout << "Step " << steps << ": Collision detected, skipping action." << std::endl;
        }
            std::cout << "Step " << steps << ": Moved to (" << robot_.getPosition().first
                      << ", " << robot_.getPosition().second << ") with yaw " << robot_.getOrientation() << std::endl;
    }

    if (!goal_reached) {
        std::cout << "Failed to reach goal within " << max_steps << " steps." << std::endl;
    }
}
