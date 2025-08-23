struct RandomNumberGenerator {
    random_device seed_gen;
    mt19937_64 engine;
    
    RandomNumberGenerator() : engine(seed_gen()) {}
    
    template <class T>
    T operator()(T a, T b) {
        uniform_int_distribution<T> dist(a, b - 1);
        return dist(engine);
    }
    
    long double operator()() {
        uniform_real_distribution<long double> dist;
        return dist(engine);
    }
} rng;
