#include "PID.h"

PID::PID() = default;

PID::~PID() = default;

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  is_initialized = false;
}

void PID::UpdateError(double cte) {
  if (is_initialized) {
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    double dt = (tv.tv_sec - last_tv.tv_sec) + (tv.tv_usec - last_tv.tv_usec) / 1e6;
    last_tv = tv;

    d_error = (cte - p_error) / dt;  // Calculate d_error first because p_error = prev_cte for now
    p_error = cte;
    i_error += cte * dt;
  } else {
    gettimeofday(&last_tv, nullptr);
    d_error = 0;
    p_error = cte;
    i_error = 0;

    is_initialized = true;
  }
}

double PID::TotalError() {
  return -Kp * p_error - Ki * i_error - Kd * d_error;
}

