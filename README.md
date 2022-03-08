# oofrng
Thomas Wang's random number generation function implicitly parallelized &amp; pipelined at speed of:

- 0.6 cycles per 32bit integer for Xeon Gold 5215 2.5GHz (1 thread, AVX512).
- - 0.53 cycles/integer if  ```-O3 -march=native -mavx512f  -ffast-math -fno-math-errno ``` compiler flags used
- 1.28 cycles per 32bit integer for Fx8150 (1 core/1 module, AVX)

```C++
constexpr int n = 1024*16;

// 64 is the internal width of vectorization 
// (can be set to power of 2 greater than or equal to 2)
oofrng::Generator<64> gen;

// to help compiler use aligned vector instructions
alignas(4096)
uint32_t r[n];

// 3409 nanoseconds to fill n-element array with random numbers 
// (or 4.8 Giga-integers per second, on Xeon Gold 5215)
gen.generate(r,n); 
```
