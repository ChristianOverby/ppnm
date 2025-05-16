#include "montecarlo.hpp"
#include <random>
#include <iostream>
#include <cassert>

namespace pp
{
    std::pair<double, double> plainmc(std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N)
    {
        int dim=a.size(); 
        double V=1; 
        for(int i=0;i<dim;i++) {V*=b[i]-a[i];}
        double sum=0,sum2=0;
	    pp::vector x(dim);
        std::random_device rd;  // Seed for the random number generator
        std::mt19937 gen(rd()); // Mersenne Twister engine
        std::uniform_real_distribution<NUMBER> dist(0, 1); // Uniform distribution
            for(int i=0;i<N;i++)
            {
                for(int k=0;k<dim;k++){x[k]=a[k]+dist(gen)*(b[k]-a[k]);}
                double fx=f(x); 
                sum+=fx; 
                sum2+=fx*fx;
            }
        double mean=sum/N;
        double sigma=std::sqrt(sum2/N-mean*mean);
        return {mean*V,sigma*V/std::sqrt(N)};
    }

    // Helper function to generate primes
    std::vector<int> generate_primes(int limit) {
        std::vector<int> primes;
        std::vector<bool> is_prime(limit + 1, true);
        is_prime[0] = is_prime[1] = false;

        for (int i = 2; i <= limit; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (int j = i * i; j <= limit; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        return primes;
    }

    double corput(int n, int b) {
        double q=0, bk = 1.0/b;
        while(n>0){ q += (n % b) * bk; n /= b ; bk /= b;}    
        return q;
    }

    void halton(int n, int d, double *points) {
        // assert the dimension
        assert(d > 0 && "Dimension must be greater than 0");
        static std::vector<int> primes = generate_primes(40);  // Generate first primes up to 40
        if (d > static_cast<int>(primes.size())) {
            std::cerr << "Err: The requested dimension exceeds generated primes. Generating more. \n";
            primes = generate_primes(d * 10);  // Regenerate primes if necessary
        }
        for (int i = 0; i < d; i++) {
            points[i] = corput(n, primes[i]);
        }
    }

    void lattice_rule(int n, int d, double *points){
         // assert the dimension
        assert(d > 0 && "Dimension must be greater than 0");
        static std::vector<int> primes = generate_primes(40);  // Generate first primes up to 40
        if (d > static_cast<int>(primes.size())) {
            std::cerr << "Err: The requested dimension exceeds generated primes. Generating more. \n";
            primes = generate_primes(d * 10);  // Regenerate primes if necessary
        }
        for (int i = 0; i < d; i++) {
            double sqrtprim = std::sqrt(primes[i]);
            points[i] = std::fmod(static_cast<double>(sqrtprim) * n, 1.0);
    }
    }
    
    std::pair<double, double> quasi_mc(std::function<double(pp::vector&)> f,const pp::vector& a,const pp::vector& b,const int N)
    {
        int dim=a.size(); 
        double V=1; 
        for(int i=0;i<dim;i++) {V*=b[i]-a[i];}
        double sum_h=0,sum_l=0;
	    pp::vector x_h(dim), x_l(dim);
            for(int i=0;i<N;i++)
            {
                halton(i, dim, &x_h[0]);
                for(int k=0;k<dim;k++){x_h[k]=a[k]+x_h[k]*(b[k]-a[k]);}
                double fx_h=f(x_h); 
                sum_h+=fx_h;

                lattice_rule(i, dim, &x_l[0]);
                for(int k=0;k<dim;k++){x_l[k]=a[k]+x_l[k]*(b[k]-a[k]);}
                double fx_l=f(x_l); 
                sum_l+=fx_l;
            }
        double mean_h=sum_h/N;
        double mean_l = sum_l/N;
        double sigma=std::abs(mean_h-mean_l)    ;
        double integral = (mean_l*V+mean_h*V)/2;
        return {integral,sigma};
    }

    std::pair<double, double> strata_mc(
        std::function<double(pp::vector&)> f,
        const pp::vector& a,
        const pp::vector& b,
        int N,
        int n_min)
    {
        assert(a.size() == b.size());
        int dim = a.size();

        if (N < n_min) {
            return plainmc(f, a, b, N);
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<NUMBER> dist(0.0, 1.0);

        std::vector<pp::vector> samples(n_min, pp::vector(dim));
        std::vector<double> values(n_min);
        pp::vector x(dim);
        
        for (int i = 0; i < n_min; ++i) {
            for (int j = 0; j < dim; ++j)
                samples[i][j] = a[j] + dist(gen) * (b[j] - a[j]);
            values[i] = f(samples[i]);
        }

        double volume = 1.0;
        for (int i = 0; i < dim; ++i)
            volume *= (b[i] - a[i]);

        double mean = std::accumulate(values.begin(), values.end(), 0.0) / n_min;
        double var = 0.0;
        for (double v : values)
            var += (v - mean) * (v - mean);
        var /= n_min;

        // Subvariance by dimension
        std::vector<double> sub_var(dim, 0.0);
        std::vector<int> count_left(dim, 0), count_right(dim, 0);
        std::vector<double> sum_left(dim, 0.0), sum_right(dim, 0.0);

        for (int i = 0; i < n_min; ++i) {
            for (int d = 0; d < dim; ++d) {
                double mid = (a[d] + b[d]) / 2.0;
                if (samples[i][d] < mid) {
                    count_left[d]++;
                    sum_left[d] += values[i];
                } else {
                    count_right[d]++;
                    sum_right[d] += values[i];
                }
            }
        }

        for (int d = 0; d < dim; ++d) {
            double mean_l = count_left[d] > 0 ? sum_left[d] / count_left[d] : 0.0;
            double mean_r = count_right[d] > 0 ? sum_right[d] / count_right[d] : 0.0;
            sub_var[d] = std::abs(mean_l - mean_r);
        }

        // Choose dimension with highest subvariance
        int split_dim = std::distance(sub_var.begin(), std::max_element(sub_var.begin(), sub_var.end()));
        double split_mid = (a[split_dim] + b[split_dim]) / 2.0;

        // Create new bounds
        pp::vector a1 = a, b1 = b;
        pp::vector a2 = a, b2 = b;
        b1[split_dim] = split_mid;
        a2[split_dim] = split_mid;

        // Allocate remaining samples
        int N_left = (int)((count_left[split_dim] / (double)n_min) * (N - n_min));
        int N_right = (N - n_min) - N_left;

        auto [I1, err1] = strata_mc(f, a1, b1, N_left + n_min / 2, n_min);
        auto [I2, err2] = strata_mc(f, a2, b2, N_right + n_min / 2, n_min);

        double total_integral = I1 + I2;
        double total_error = std::sqrt(err1 * err1 + err2 * err2);

        return {total_integral, total_error};
    }
    

}