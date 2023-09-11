#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

void special_algorithm(double v_0,double v_end,int n_steps)
{
  double div_n = (double)n_steps;
  double stepsize = 1./div_n;

  std::vector<double> x(n_steps+1);
  for (int i=0; i < x.size(); i++){  //evenly distributed x-values
     x[i] = 0.0 + i*stepsize*(1.0-0.0);
   }

  std::vector<double> b_tilde(n_steps-1);
  fill(b_tilde.begin(),b_tilde.end(),0);
  b_tilde[0] = 2; //b_0
  //boundaries in v
  std::vector<double> v(n_steps+1);
  fill(v.begin(),v.end(),0);
  v[0] = v_0;
  v.back() = v_end;

  std::vector<double> g(n_steps-1);
  for (int i=0; i < g.size(); i++){
     g[i] = pow(stepsize,2)*100.*exp(-10.*x[i+1]); //v_start=0, and v_end=0 so we can write it like this
   }

  std::vector<double> g_tilde(n_steps-1);
  fill(g_tilde.begin(),g_tilde.end(),0);
  g_tilde[0] = g[0];


  for (int i=1; i < b_tilde.size(); i++){ //b_tilde and g_tilde calculations
    b_tilde[i] = 2 - 1/b_tilde[i-1];
    g_tilde[i] = g[i] + g_tilde[i-1]/b_tilde[i-1];
  }

  v[n_steps-1] = g_tilde[n_steps-2]/b_tilde[n_steps-2];
  for (int i = (n_steps-2); i > 0; i--){ //calculating v
    v[i] = (g_tilde[i-1]+v[i+1])/b_tilde[i-1];
  }

  std::ofstream outfile;
  std::string file_name = "special_solution_n="+std::to_string(n_steps)+".dat";
  outfile.open(file_name);
  outfile << "    x    " << "    " << "v" << std::endl;

  for (int i=0; i < x.size(); i++) {
    outfile << std::fixed << std::setprecision(4) << std::scientific << x[i] << " " << v[i]<< std::endl;
  }
  outfile.close();
}

int main()
{
  // Print a message to screen
  std::cout << "Hello, World!\n";

  std::vector<int> n_steps_{10,100,1000,10000};

  for (int i=0; i<n_steps_.size(); i++){
     special_algorithm(0.0,0.0,n_steps_[i]);
  }

  // Return 0 when done
  return 0;
}
