# oofrng
Thomas Wang's random number generation function implicitly parallelized &amp; pipelined at speed of:

## uint32_t between [0 and 2^32-1)
- 0.53 cycles per 32bit integer for Xeon Gold 5215 2.5GHz (1 thread, AVX512).
- - (with ```-O3 -march=native -mavx512f  -ffast-math -fno-math-errno ``` compiler flags used)
- 1.28 cycles per 32bit integer for Fx8150 (1 core/1 module, AVX)

## uint32_t between [0 and non-2^k)
- 2.1 cycles per 32bit integer for Xeon Gold 5215 2.5GHz (1 thread, AVX512).
- - (with ```-O3 -march=native -mavx512f  -ffast-math -fno-math-errno ``` compiler flags used)
- 4.5 cycles per 32bit integer for Fx8150 (1 core/1 module, AVX)

## uint32_t between [0 and 2^k)
- 0.76 cycles per 32bit integer for Xeon Gold 5215 2.5GHz (1 thread, AVX512).
- - (with ```-O3 -march=native -mavx512f  -ffast-math -fno-math-errno ``` compiler flags used)
- 1.8 cycles per 32bit integer for Fx8150 (1 core/1 module, AVX)

## float between [0 and 1)
- 1.12 cycles per 32bit float for Xeon Gold 5215 2.5GHz (1 thread, AVX512).
- 3 cycles per 32bit float for Fx8150 (1core/1module, AVX)

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
