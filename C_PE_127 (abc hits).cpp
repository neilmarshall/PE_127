// Solution:    18407904

#include <iostream>
#include <vector>
#include <cmath>
#include <deque>

using namespace std;

vector<long long> generate_primes(long long);
vector<long long> factorise(long long, vector<long long>&);
long long RAD(vector<long long>&);

int main() {
    long long limit = 120000;
    vector<long long> primes = generate_primes(limit);
    vector<vector<long long> > prime_factors;
    for (long long n = 0; n <= limit; ++n) {
        prime_factors.push_back(factorise(n, primes));
    }
    long long c_total = 0;
    deque<vector<long long> > pairs;
    vector<long long> v1;
    v1.push_back(2);
    v1.push_back(1);
    pairs.push_back(v1);
    vector<long long> v2;
    v2.push_back(3);
    v2.push_back(1);
    pairs.push_back(v2);
    vector<long long> curr_pair;
    vector<long long> new_pair;
    long long c = 0;
    vector<long long> rF;
    long long r = 0;
    while (pairs.size() > 0) {
        curr_pair = pairs[0];
//        cout << "(" << curr_pair[0] << ", " << curr_pair[1] << "): ";
        pairs.pop_front();
        new_pair.clear();
        new_pair.push_back(2 * curr_pair[0] - curr_pair[1]);
        new_pair.push_back(curr_pair[0]);
        if (new_pair[0] + new_pair[1] < limit) {
            pairs.push_back(new_pair);
        }
        new_pair.clear();
        new_pair.push_back(2 * curr_pair[0] + curr_pair[1]);
        new_pair.push_back(curr_pair[0]);
        if (new_pair[0] + new_pair[1] < limit) {
            pairs.push_back(new_pair);
        }
        new_pair.clear();
        new_pair.push_back(curr_pair[0] + 2 * curr_pair[1]);
        new_pair.push_back(curr_pair[1]);
        if (new_pair[0] + new_pair[1] < limit) {
            pairs.push_back(new_pair);
        }
        c = curr_pair[0] + curr_pair[1];
        rF.clear();
        for (long long i = 0; i < prime_factors[curr_pair[0]].size(); ++i) {
            rF.push_back(prime_factors[curr_pair[0]][i]);
        }
        for (long long i = 0; i < prime_factors[curr_pair[1]].size(); ++i) {
            rF.push_back(prime_factors[curr_pair[1]][i]);
        }
        for (long long i = 0; i < prime_factors[c].size(); ++i) {
            rF.push_back(prime_factors[c][i]);
        }
//        for (long long i = 0; i < rF.size(); ++i) {
//            cout << rF[i] << ' ';
//        }
        r = RAD(rF);
//        cout << ":: " << r << '\n';
        if (r < c) {
            c_total += c;
        }
    }
    cout << c_total << endl;
}

vector<long long> generate_primes(long long limit) {
    vector<bool> indicators;
    for (long long i = 0; i < limit + 1; ++i) {
        indicators.push_back(true);
    }
    indicators[0] = false;
    indicators[1] = false;
    for (long long i = 2; i < limit / 2 + 1; ++i) {
        for (long long j = 2; j < limit / i + 1; ++j) {
            indicators[i * j] = false;
        }
    }
    vector<long long> primes;
    for (long long i = 0; i < indicators.size(); ++i) {
        if (indicators[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

vector<long long> factorise(long long n, vector<long long>& primes) {
    vector<long long> factors;
    if (n == 1) {
        factors.push_back(1);
    }
    else {
        for (long long i = 0; i < primes.size(); ++i) {
            if (primes[i] > sqrt(n)) {
                break;
            }
            while (n % primes[i] == 0) {
                factors.push_back(primes[i]);
                n = n / primes[i];
            }
        }
        if (n != 1) {
            factors.push_back(n);
        }
    }
    return factors;
}

long long RAD(vector<long long>& prime_factors) {
    long long x = 1;
    long long prev_fac = 0;
    for (long long i = 0; i < prime_factors.size(); ++i) {
        if (prime_factors[i] != prev_fac) {
            x *= prime_factors[i];
        }
        prev_fac = prime_factors[i];
    }
    return x;
}