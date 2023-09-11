#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

void general_algorithm_error(std::vector<double> a, std::vector<double> b, std::vector<double> c, double v_0,double v_end,int n_steps)
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
  //absolute error
  std::vector<double> abs_err(n_steps-1);
  for (int i=0; i < abs_err.size(); i++){
      abs_err[i] = log10(fabs(u[i+1]-v[i+1])); //The indices are like this because we dont include the boundaries
    }

  std::ofstream outfile;
  std::string file_name = "abs_err_n="+std::to_string(n_steps)+".dat";
  outfile.open(file_name);
  outfile << "    x    " << " " << "log10(abs_err)" << std::endl;

  for (int i=0; i < abs_err.size(); i++) {
    outfile << std::fixed << std::setprecision(4) << std::scientific << x[i+1] << " " << abs_err[i]<< std::endl;
  }
  outfile.close();

  //relative error
  std::vector<double> rel_err(n_steps-1);
  for (int i=0; i < abs_err.size(); i++){
      rel_err[i] = log10(fabs((u[i+1]-v[i+1])/u[i+1]));  //The indices are like this because we dont include the boundaries
    }

  std::ofstream new_outfile;
  std::string new_file_name = "rel_err_n="+std::to_string(n_steps)+".dat";
  new_outfile.open(new_file_name);
  new_outfile << "    x    " << " " << "log10(rel_err)" << std::endl;

  for (int i=0; i < abs_err.size(); i++) {
    new_outfile << std::fixed << std::setprecision(4) << std::scientific << x[i+1] << " " << rel_err[i]<< std::endl;
  }
  new_outfile.close();
}

int main()
{
  // Print a message to screen
  std::cout << "Hello, World!\n";

  std::vector<int> n_steps_{10,100,1000,10000};

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
    general_algorithm_error(a,b,c,0.0,0.0,n_steps_[i]);
  }

  // Return 0 when done
  return 0;
}
