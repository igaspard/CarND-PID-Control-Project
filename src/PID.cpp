#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  this->p_error = 0.0;
  this->i_error = 0.0;
  this->d_error = 0.0;

  bFirstTwiddle = true;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error; // CTEt - CTEt-1
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() {
  return -Kp * p_error - Kd * d_error - Ki * i_error;
}

bool PID::Twiddle() {
  if (bFirstTwiddle) {
    total_cte = 0.0;
    best_error = numeric_limits<double>::max();
    err = 0.0;
    tol = 0.2;
    it = 0;
    idx = 2;
    init_sum = 0.0;
    n = 0;
    max_n = 200;
     // p.push_back(0.05);  p.push_back (0.0001); p.push_back(1.5);
     // p.push_back(0.06);  p.push_back(0.0003),  p.push_back(1.7);
     p.push_back(0.0764954); p.push_back(0.0004); p.push_back(2.03116);     
    dp.push_back(0.01); dp.push_back(0.0001); dp.push_back(0.1);

    bFirstTwiddle = false;
    return true;
  } else {
    total_cte = total_cte + p_error * p_error;
    n++;
    if (n > max_n) { // sampling rate
      err = total_cte / max_n;
      p[idx] += dp[idx];

      cout << "Interation: " << it << ", Best Error: " << best_error << ", idx: " << idx << endl;
      cout << " p[0]  p[1]  p[2]: " <<  p[0] << " " <<  p[1] << " " <<  p[2] << endl;
      cout << "dp[0] dp[1] dp[2]: " << dp[0] << " " << dp[1] << " " << dp[2] << endl;

      if ( err < best_error ) {
        best_error = err;
        dp[idx] *= 1.1;
      } else {
        p[idx] -= 2 * dp[idx];

        if (err < best_error) {
          best_error = err;
          dp[idx] *= 1.1;
        } else {
          p[idx] += dp[idx];
          dp[idx] *= 0.9;
        }
      }
      idx = (idx+1) % 3;
      it++;
      total_cte = 0.0;
      n = 0;
      if ( accumulate(dp.begin(), dp.end(), init_sum) < tol ) {
        return true;
      } else {
        return false;
      }
    } else {
      return true;
    }
  }
}
