/*
 * Generator.h
 *
 *  Created on: Mar 8, 2022
 *      Author: tugrul
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

template < int LANES = 64 >
    class Generator 
    {
        public:
            Generator(): seed(LANES) 
            {
                ptrL = & seedL[0];

                while (((size_t) ptrL) % 4096 != 0)
                    ptrL++;
                    
                for (size_t i = 0; i < LANES; i++) 
                {
                    ptrL[i] = i;
                }
            }

        const uint32_t generate1() 
        {
            return rnd(seed);
        }

        void generate(uint32_t *
            const __restrict__ out,
                const size_t n) 
        {

            const size_t nL = n - n % LANES;
            for (size_t i = 0; i < nL; i += LANES) 
            {
                rndL(ptrL, out + i);
            }

            for (size_t i = nL; i < n; i++) 
            {
                out[i] = rnd(seed);
            }
        }

        private:
            uint32_t * ptrL;
        uint32_t seedL[LANES + 4096];
        uint32_t seed;
        const uint32_t rnd(uint32_t & seed) 
        {
            // Thomas Wang's invention
            seed = (seed ^ 61) ^ (seed >> 16);
            seed *= 9;
            seed = seed ^ (seed >> 4);
            seed *= 0x27d4eb2d;
            seed = seed ^ (seed >> 15);
            return seed;
        }

        inline
        void rndL(uint32_t *
            const __restrict__ seed, uint32_t *
                const __restrict__ out) 
        {

            for (int i = 0; i < LANES; i += 2) {
                const uint32_t sd = seed[i];
                const uint32_t sd_ = seed[i + 1];

                const uint32_t sd2 = (sd ^ 61) ^ (sd >> 16);
                const uint32_t sd2_ = (sd_ ^ 61) ^ (sd_ >> 16);

                const uint32_t sd3 = sd2 * 9;
                const uint32_t sd3_ = sd2_ * 9;

                const uint32_t sd4 = sd3 ^ (sd3 >> 4);
                const uint32_t sd4_ = sd3_ ^ (sd3_ >> 4);

                const uint32_t sd5 = sd4 * 0x27d4eb2d;
                const uint32_t sd5_ = sd4_ * 0x27d4eb2d;

                const uint32_t sd6 = sd5 ^ (sd5 >> 15);
                const uint32_t sd6_ = sd5_ ^ (sd5_ >> 15);

                out[i] = sd6;
                out[i + 1] = sd6_;

                seed[i] = sd6;
                seed[i + 1] = sd6_;

            }
        }
    };

#endif /* GENERATOR_H_ */
