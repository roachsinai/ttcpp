#include <vector>
// #include <fmt/format.h>
#include <fmt/ranges.h>

#ifdef __AVX2__
  #include <immintrin.h>
#else
  #warning No AVX support - will not compile
#endif

void addindex_vec2(double *x, int n) {
    __m256d x_vec, incr, ind;
    ind = _mm256_set_pd(3, 2, 1, 0);
    incr = _mm256_set1_pd(4);
    for (int i = 0; i < n; i+=4) {
        x_vec = _mm256_loadu_pd(x+i); // load 4 doubles
        x_vec = _mm256_add_pd(x_vec, ind); // add the two
        ind = _mm256_add_pd(ind, incr); // update ind
        _mm256_storeu_pd(x+i, x_vec); // store back
    }
}

int main()
{
    // double d[8]{0};
    // addindex_vec2(d, 8);

    std::vector<double> d(8, 0.0);
    addindex_vec2(d.data(), 8);
    fmt::print("{}\n", d);

	return 0;
}
