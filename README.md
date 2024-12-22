
## Black-Scholes Option Pricing Model in C++

This project provides a C++ implementation of the Black-Scholes model. Additionally, it computes the option Greeks.

### Features

- Option Pricing (European call and put)
- Greeks Calculation:
  - Delta
  - Gamma
  - Theta
  - Vega
  - Rho

### Prerequisites

C++

### Compilation

```bash
g++ -std=c++11 -o option_pricing option_pricing.cpp  -lm
```
### Usage



```bash
./option_pricing
```

### Mathematical Formulas


#### Call Option Price (C):

$$C = S_0 \times N(d_1) - K \times e^{-r \times T} \times N(d_2)$$


#### Put Option Price (P):

$$P = K \times e^{-r \times T} \times N(-d_2) - S_0 \times N(-d_1)$$

Where:

- $S_0$: Current price of the underlying asset
- $K$: Strike price of the option
- $r$: Risk-free interest rate
- $T$: Time to expiration (in years)
- $N(\cdot)$: Cumulative distribution function of the standard normal distribution
- $d_1$ and $d_2$ are calculated as:

$$d_1 = \frac{\ln(\frac{S_0}{K}) + (r + \frac{\sigma^2}{2}) \times T}{\sigma \times \sqrt{T}}$$

$$d_2 = d_1 - \sigma \times \sqrt{T}$$

- $\sigma$: Volatility of the underlying asset's returns

### Option Greeks:

- **Delta (Δ)**: Measures the sensitivity of the option's price to changes in the price of the underlying asset.
  - Call Option: $\Delta_{\text{call}} = N(d_1)$
  - Put Option: $\Delta_{\text{put}} = N(d_1) - 1$

- **Gamma (Γ)**: Measures the rate of change of Delta with respect to changes in the underlying asset's price.
 $$\Gamma = \frac{N'(d_1)}{S_0 \times \sigma \times \sqrt{T}}$$

- **Theta (Θ)**: Measures the sensitivity of the option's price to the passage of time.
  - Call Option: 
   $$\Theta_{\text{call}} = -\frac{S_0 \times N'(d_1) \times \sigma}{2 \times \sqrt{T}} - r \times K \times e^{-r \times T} \times N(d_2)$$
  - Put Option: 
   $$\Theta_{\text{put}} = -\frac{S_0 \times N'(d_1) \times \sigma}{2 \times \sqrt{T}} + r \times K \times e^{-r \times T} \times N(-d_2)$$

- **Vega (ν)**: Measures the sensitivity of the option's price to changes in the volatility of the underlying asset.
 $$\nu = S_0 \times N'(d_1) \times \sqrt{T}$$

- **Rho (ρ)**: Measures the sensitivity of the option's price to changes in the risk-free interest rate.
  - Call Option: 
   $$\rho_{\text{call}} = K \times T \times e^{-r \times T} \times N(d_2)$$
  - Put Option: 
   $$\rho_{\text{put}} = -K \times T \times e^{-r \times T} \times N(-d_2)$$



### References

- [Black–Scholes model - Wikipedia](https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model)
- [European vanilla option pricing with C++ and analytic formulae](https://www.example.com)
- [Black-Scholes Model - GeeksforGeeks](https://www.geeksforgeeks.org/black-scholes-model/)


 
