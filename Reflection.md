## Reflection

### Describe the effect each of the P, I, D components had in your implementation.

At first I've read the PID control page in wikipedia, and this table and image can really describe how the PID components works.

| Parameter | Rise time | Overshoot | Settling time | Steady-state error | Stability |
| --- | --- | --- | --- | --- | --- |
| P | Decrease | Increase | Small change | Decrease | Degrade |
| I | Decrease | Increase | Increase | Eliminate | Degrade |
| D | Minor change | Decrease | Decrease | No effect in theory | Improve if D small |

![PID Compensation Animated](https://upload.wikimedia.org/wikipedia/commons/3/33/PID_Compensation_Animated.gif)

[Link to the wikipedia](https://en.wikipedia.org/wiki/PID_controller#Manual_tuning)

But for the driving case, these components has their special meanings:

- Increase P: Car can make turn more quickly, but the process will be less stable.
- Decrease P: Driving process will be more stable, but if we run into a bend in high speed, car will run out of the road.
- Increase I: Revise mechanical deviation, and it can also counteract the insufficient turning.
- Increase D: Make driving process more stable, but also make turning a little insufficient. And make driving process converge.


### Describe how the final hyperparameters were chosen.

First, I print the web socket messages, and found the count of message per second are not equals. So I've added time features and delta t in the PID control.

Then I've copy the twiddle algorithm and Robot class from lesson, transform all unit to suit this project. And I've also run with different speed and initialization position.

```
Final twiddle for speed 30, params is [1.338859149339369, 2.045178170127182, 0.008694542295379103]
Final twiddle for speed 31, params is [2.0726145087093695, 2.552384741249567, 0.06461081889226677]
Final twiddle for speed 32, params is [0.9999999999999989, 1.2548722204434561, 0.0]
...
Final twiddle for speed 67, params is [0.11903254002774018, -0.35385958166697107, 0.3138105960900003]
Final twiddle for speed 68, params is [0.9999999999999993, -0.7289999999999999, -0.3138105960900004]
Final twiddle for speed 69, params is [1.0877430873845597, -0.729, -0.0797664430768726]
```

And then I found that when speed is greater than 70mph, PID control can not converge. I choose the parameters for 50mph, in the simulator, the car is shaking in the lap. So I decrease P parameter and change a little I and D parameter, my vehicle can run over the lap.

But the speed is too slow, not cool!

So I've added one PID control to control the speed, and add a strategy to make brake when speed and CTE are too high. (That make sense, like human driving)
And then I increase the expected speed and brake throttle, and increase P and I parameter to make vehicle can turn over all the bends, at last, increase D parameter to make driving process more stable.

At last, I hit the special parameters, [0.15, 0.15, 0.15].
The driving process is a little unstable, but speed can hit 70 - 90 mph, that's so cool.

> One video is in the path: /resources/video.mp4
