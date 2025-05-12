#include <iostream>
#include <cmath>
#include "Environment.h"
#include "Robot.h"
#include "Planner.h"
#define _USE_MATH_DEFINES
using namespace std;

void run_once(int n){
    int obs_num, step_num;
    Pair d, eror, r, t;
    vector<Tuple> obs_det;
    cout << "Robot start  position(X, Y)           : "; cin >> r.first >> r.second;
    cout << "Target(ball) position(X, Y)           : "; cin >> t.first >> t.second;
    cout << "Number of obsatcle                    : "; cin >> obs_num;
    cout << "X change per step(Dx)                 : "; cin >> d.first;
    cout << "Max Y(robot cannot move exceed Max Y) : "; cin >> d.second;
    cout << "Max Iteration(number of steps)        : "; cin >> step_num;
    cout << "Obstacle (X, Y, Radius)\n";
    for(int i=0; i<obs_num; i++){
        double obs_x, obs_y, obs_r;
        cout << i+1 << ". "; cin >> obs_x >> obs_y >> obs_r;
        obs_det.emplace_back(obs_x, obs_y, obs_r);
    }
    Environment env({r.first, r.second}, {t.first, t.second}, obs_det);
    Robot robot(r);
    Planner planner(0, 0, 0, env, robot);
    planner.configureAccessibility(d.first, d.second, M_PI/6);
    planner.planPathIteratively(step_num, 0.1);
}

int main() {
    int n, m;
    cout << "Testcase : "; cin >> n;
    m=n;
    while(n--){
        cout <<"Case : " << m-n+1 << endl;
        run_once(n);
        cout << endl;
    }
    return 0;
}