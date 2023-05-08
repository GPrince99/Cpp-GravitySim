#include <iostream>
#include <array>
#include <tuple>
#include <vector>
#include <cmath>

const long double G = 6.67408e-11;

class Orbital
{
private:
    double c_mass;
    double i_pos;
    double i_vel;
    int step;
    int end;

public:
    Orbital(double orbiting_mass, double central_mass, double init_pos, double init_vel, int time, int time_step)
    {
        c_mass = central_mass;
        i_pos = init_pos;
        i_vel = init_vel;
        step = time_step;
        end = time;

    }
    
    std::vector<double> timearray()
    {

        std::vector<double> linspaced;

        double start = 0;
        double num = end/step;

        if (num == 0) { return linspaced; }
        if (num == 1) 
            {
            linspaced.push_back(start);
            return linspaced;
            }

        double delta = (end - start) / (num - 1);

        for(int i=0; i < num-1; ++i)
            {
            linspaced.push_back(start + delta * i);
            }
        linspaced.push_back(end);

        return linspaced;
    }

    double vx(double x, double y)
    {
        return -(G * c_mass * x) / (pow((pow(x, 2) + pow(y, 2)),(3/2)));
    }

    double vy(double x, double y)
    {
        return -(G * c_mass * y) / (pow((pow(x, 2) + pow(y, 2)),(3/2)));
    }

    std::tuple<std::array<double, 4>,std::array<double, 4>,std::array<double, 4>,std::array<double, 4>> RK4(double x_pos, double y_pos, double x_vel, double y_vel)
    {
        double k1x = x_vel;
        double k1y = y_vel;
        double k1vx = vx(x_pos, y_pos);
        double k1vy = vy(x_pos, y_pos);

        double k2x = x_vel + (step * k1vx) / 2;
        double k2y = y_vel + (step * k1vy) / 2;
        double k2vx = vx(x_pos + (step * k1x) / 2, y_pos + (step * k1y) / 2);
        double k2vy = vy(x_pos + (step * k1x) / 2, y_pos + (step * k1y) / 2);

        double k3x = x_vel + (step * k2vx) / 2;
        double k3y = y_vel + (step * k2vy) / 2;
        double k3vx = vx(x_pos + (step * k2x) / 2, y_pos + (step * k2y) / 2);
        double k3vy = vy(x_pos + (step * k2x) / 2, y_pos + (step * k2y) / 2);

        double k4x = x_vel + step * k3vx;
        double k4y = y_vel + step * k3vy;
        double k4vx = vx(x_pos + step * k3x, y_pos + step * k3y);
        double k4vy = vy(x_pos + step * k3x, y_pos + step * k3y);

        return {{k1x, k2x, k3x, k4x}, {k1y, k2y, k3y, k4y}, {k1vx, k2vx, k3vx, k4vx}, {k1vy, k2vy, k3vy, k4vy}};
    }

};








int main()
{
    Orbital Orbit(100,100,100,100,100,2);
    std::vector<double> time = Orbit.timearray();
    for (double d : time)
        std::cout << d << " ";
    return 0;
}