#ifndef PLANNER_H
#define PLANNER_H
#include <vector>
#include "Environment.h"
#include "Robot.h"

class Planner {
public:
    Planner(double max_x, double max_y, double max_theta, const Environment& env, Robot& robot);

    void configureAccessibility(double length, double width, double yaw);
    std::vector<Tuple> generateActionSpace() const;
    double calculateReward() const;
    int predictSteps() const;
    void planPathIteratively(int max_steps, double place_threshold);

private:
    double max_x_, max_y_, max_theta_;
    double accessibility_length_, accessibility_width_, accessibility_yaw_; //batas akses
    const Environment& env_;
    Robot& robot_;
};

#endif // PLANNER_H
