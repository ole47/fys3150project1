#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <algorithm>

double general_algorithm_error(std::vector<double> a, std::vector<double> b, std::vector<double> c, double v_0,double v_end,int n_steps)
{
  double div_n = (double)n_steps;
  double stepsize = 1./div_n;

  std::vector<double> x(n_steps+1);
  for (int i=0; i < x.size(); i++){  //evenly distributed x-values
     x[i] = 0.0 + i*stepsize*(1.0-0.0);
   }

  std::vector<double> b_tilde(n_steps-1);
  fill(b_tilde.begin(),b_tilde.end(),0);
  b_tilde[0] = b[0];
  //boundaries in v
  std::vector<double> v(n_steps+1);
  fill(v.begin(),v.end(),0);
  v[0] = v_0;
  v.back() = v_end;

  std::vector<double> g(n_steps-1);
  g[0] = pow(stepsize,2)*100.*exp(-10.*x[1])+v_0;
  g.back() = pow(stepsize,2)*100.*exp(-10.*x.back())+v_end;
  for (int i=1; i < g.size()-1; i++){
     g[i] = pow(stepsize,2)*100.*exp(-10.*x[i+1]);
   }
  std::vector<double> g_tilde(n_steps-1);
  fill(g_tilde.begin(),g_tilde.end(),0);
  g_tilde[0] = g[0];


  for (int i=1; i < b_tilde.size(); i++){ //b_tilde and g_tilde calculations
    b_tilde[i] = b[i] - (a[i]/b_tilde[i-1])*c[i-1];
    g_tilde[i] = g[i] - (a[i]/b_tilde[i-1])*g_tilde[i-1];
  }

  v[n_steps-1] = g_tilde[n_steps-2]/b_tilde[n_steps-2];
  for (int i = (n_steps-2); i > 0; i--){ //calculating v
    v[i] = (g_tilde[i-1]-c[i-1]*v[i+1])/b_tilde[i-1];
  }

  //exact solution
  std::vector<double> u(n_steps+1);
  for (int i=0; i < x.size(); i++){
     u[i] = 1.0 - (1.0-exp(-10.0))*x[i]-exp(-10.0*x[i]);
   }

  //relative error
  std::vector<double> rel_err(n_steps-1);
  for (int i=0; i < rel_err.size(); i++){
      rel_err[i] = fabs((u[i+1]-v[i+1])/u[i+1]);  //The indices are like this because we dont include the boundaries
    }

  double max = *max_element(rel_err.begin(), rel_err.end());

  return max;
}

int main()
{
  // Print a message to screen
  std::cout << "Hello, World!\n";

  std::vector<int> n_steps_{10,100,1000,10000,(int)pow(10,5),(int)pow(10,6),(int)pow(10,7)};
  std::vector<double> maxs(n_steps_.size());
  std::vector<double> n_steps_new(n_steps_.size());

  for (int i=0; i<n_steps_.size(); i++){
    //Setting up a, b and c
    std::vector<double> a(n_steps_[i]-1);
    fill(a.begin(),a.end(),-1);
    a[0] = 0;
    std::vector<double> b(n_steps_[i]-1);
    fill(b.begin(),b.end(),2);
    std::vector<double> c(n_steps_[i]-1);
    fill(c.begin(),c.end(),-1);
    c.back() = 0;
    maxs[i] = general_algorithm_error(a,b,c,0.0,0.0,n_steps_[i]);
    n_steps_new[i] = (double)n_steps_[i];  //Just for the output to look nicer
  }

  std::ofstream outfile;
  std::string file_name = "max_rel_err.dat";
  outfile.open(file_name);
  outfile << " n_steps    " << " " << "max_rel_err" << std::endl;

  for (int i=0; i < n_steps_new.size(); i++) {
    outfile << std::fixed << std::setprecision(4) << std::scientific << n_steps_new[i] << " " << maxs[i]<< std::endl;
  }
  outfile.close();

  // Return 0 when done
  return 0;
}
