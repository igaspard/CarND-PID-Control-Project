# PID Control Project - Gaspard Shen
In this PID control project, I implement the proportional-integral-derivative(PID) controller to drive the simulator's Vehicle in the lake race from the CarND Term1 project Behavioral Cloning Project. By using the Twiddle algorithm for PIC controller parameter tuning, in the end the Vehicle can drive the whole lap in the lake race with the 40 MPH.

## Implementation
PID control was control loop feedback mechanism widely used in the industrial control system. A PID controller continuously calculates an error value e(t) as the difference between a desired setpoint (SP) and a measured process variable (PV) and applies a correction based on proportional, integral, and derivative terms (denoted P, I, and D respectively) which give the controller its name.

Base this project starter code, first thing is the initialize the Kp, Ki and Kd in the `PID::Init()`.
Second update the `PID::UpdateError()` according to the simulator send Cross Track Error(CTE).
Then base on the PID control's formula calculates the total CTE in `PID::TotalError()`.

![](/output/PID.svg)

## Reflection
**Describe the effect each of the P, I, D components had in your implementation.**
- The P errors is the proportional to the current CTE value. If the error is large and positive, the control output will be proportionately large and positive. To increase the weight Kp can hep to handle the sharp turns proactively. However, if the value was too large the vehicle will much easily drive out of the track.
- The D errors is the best estimates of future trend based on the current rate of change at t and t-1. It is used to reduce the overshooting and the oscillations caused by P. In my experiments, this take most the impact to make the vehicle driving on the track.
- The I errors is taking the accumulating the CTE over the past time. That can help to sustain after the long period systematic bias. During toggle the Ki parameters, look like in this case the effect of the Ki was not that significant.

**Describe how the final hyperparameters were chosen.**
I implement the Sebastian's twiddle algorithm in the `PID::Twiddle()`. I set a interval `max_n` that every `max_n` cte update, running the twiddle algorithms. Everytime the vehicle crash or out of the road, I base on the end of tunning parameters and run the twiddle over and over again. After serveral iterations, the vehicle can run on track without driving out of the road. In the end I got `(Kp, Ki, Kd) = {0.0903947, 0.000501463, 2.32055}`.

## Simulation
Below is the video I uploaded on Vimeo with the final parameters. The Vehicle can successfully drive the whole lap around the track without roll over any surfaces or pop up onto the ledges.

[PID Control Result Video][203ad241]

  [203ad241]: https://vimeo.com/263104177 "PID Control Result Video"
