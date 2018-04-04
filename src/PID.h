#ifndef PID_H
#define PID_H
#include <vector> // vector
#include <numeric> // accumulate
#include <iostream> // istream, ostream
#include <limits> // numeric_limits

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  /*
  * Twiddle variables
  */
  bool bFirstTwiddle;
  double total_cte;
  double best_error;
  double err;
  double tol;
  unsigned int it;
  unsigned int idx;
  unsigned int n, max_n;
  double init_sum;
  std::vector<double> p;
  std::vector<double> dp;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Twiddle the params
  */
  bool Twiddle();
};

#endif /* PID_H */
