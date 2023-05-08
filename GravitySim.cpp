#include <iostream>
#include <array>
#include <vector>

template<typename T>
std::vector<double> linspace(T start_in, T end_in, int num_in)
{

  std::vector<double> linspaced;

  double start = static_cast<double>(start_in);
  double end = static_cast<double>(end_in);
  double num = static_cast<double>(num_in);

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
  linspaced.push_back(end); // I want to ensure that start and end
                            // are exactly the same as the input
  return linspaced;
}

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

};








int main()
{
    Orbital Orbit(100,100,100,100,100,2);
    std::vector<double> time = Orbit.timearray();
    for (double d : time)
        std::cout << d << " ";
    return 0;
}