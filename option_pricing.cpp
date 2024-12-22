#include <iostream>
#include <cmath>

// Standard normal cumulative distribution function
double norm_cdf(double x) {
    return 0.5 * std::erfc(-x * M_SQRT1_2);
}

// Standard normal probability density function
double norm_pdf(double x) {
    return std::exp(-0.5 * x * x) / std::sqrt(2 * M_PI);
}

// d1 calculation
double d1(double S, double K, double r, double sigma, double T) {
    return (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
}

// d2 calculation
double d2(double S, double K, double r, double sigma, double T) {
    return d1(S, K, r, sigma, T) - sigma * std::sqrt(T);
}

// Delta for call option
double delta_call(double S, double K, double r, double sigma, double T) {
    return norm_cdf(d1(S, K, r, sigma, T));
}

// Delta for put option
double delta_put(double S, double K, double r, double sigma, double T) {
    return norm_cdf(d1(S, K, r, sigma, T)) - 1;
}

// Gamma for both call and put options
double gamma(double S, double K, double r, double sigma, double T) {
    return norm_pdf(d1(S, K, r, sigma, T)) / (S * sigma * std::sqrt(T));
}

// Theta for call option
double theta_call(double S, double K, double r, double sigma, double T) {
    double d1_val = d1(S, K, r, sigma, T);
    double d2_val = d2(S, K, r, sigma, T);
    return - (S * norm_pdf(d1_val) * sigma) / (2 * std::sqrt(T))
           - r * K * std::exp(-r * T) * norm_cdf(d2_val);
}

// Theta for put option
double theta_put(double S, double K, double r, double sigma, double T) {
    double d1_val = d1(S, K, r, sigma, T);
    double d2_val = d2(S, K, r, sigma, T);
    return - (S * norm_pdf(d1_val) * sigma) / (2 * std::sqrt(T))
           + r * K * std::exp(-r * T) * norm_cdf(-d2_val);
}

// Vega for both call and put options
double vega(double S, double K, double r, double sigma, double T) {
    return S * norm_pdf(d1(S, K, r, sigma, T)) * std::sqrt(T);
}

// Rho for call option
double rho_call(double S, double K, double r, double sigma, double T) {
    return K * T * std::exp(-r * T) * norm_cdf(d2(S, K, r, sigma, T));
}

// Rho for put option
double rho_put(double S, double K, double r, double sigma, double T) {
    return -K * T * std::exp(-r * T) * norm_cdf(-d2(S, K, r, sigma, T));
}

int main() {
    double S = 100.0;    // Underlying asset price
    double K = 100.0;    // Strike price
    double r = 0.05;     // Risk-free interest rate
    double sigma = 0.2;  // Volatility
    double T = 1.0;      // Time to maturity in years

    std::cout << "Delta (Call): " << delta_call(S, K, r, sigma, T) << std::endl;
    std::cout << "Delta (Put): " << delta_put(S, K, r, sigma, T) << std::endl;
    std::cout << "Gamma: " << gamma(S, K, r, sigma, T) << std::endl;
    std::cout << "Theta (Call): " << theta_call(S, K, r, sigma, T) << std::endl;
    std::cout << "Theta (Put): " << theta_put(S, K, r, sigma, T) << std::endl;
    std::cout << "Vega: " << vega(S, K, r, sigma, T) << std::endl;
    std::cout << "Rho (Call): " << rho_call(S, K, r, sigma, T) << std::endl;
    std::cout << "Rho (Put): " << rho_put(S, K, r, sigma, T) << std::endl;

    return 0;
}
