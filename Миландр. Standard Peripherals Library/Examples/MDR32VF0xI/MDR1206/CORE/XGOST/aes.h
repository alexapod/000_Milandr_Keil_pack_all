
#ifndef _AES_H_
#define _AES_H_

#include <stddef.h>
#include <stdint.h>

#define AES_ROUNDS   ((BITS) / 32 + 6)
#define AES_RK_WORDS (4 * ((AES_ROUNDS) + 1))

#if __riscv_xlen == 32

#define SAES_ROUND(imm, r, s, a, b, c, d, i)                                        \
    __asm__(#imm " %0, %1, %2, %3" : "=r"(r##a) : "r"(*(rk i)), "r"(s##a), "i"(0)); \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##a) : "r"(s##b), "i"(1));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##a) : "r"(s##c), "i"(2));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##a) : "r"(s##d), "i"(3));               \
    __asm__(#imm " %0, %1, %2, %3" : "=r"(r##b) : "r"(*(rk i)), "r"(s##b), "i"(0)); \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##b) : "r"(s##c), "i"(1));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##b) : "r"(s##d), "i"(2));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##b) : "r"(s##a), "i"(3));               \
    __asm__(#imm " %0, %1, %2, %3" : "=r"(r##c) : "r"(*(rk i)), "r"(s##c), "i"(0)); \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##c) : "r"(s##d), "i"(1));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##c) : "r"(s##a), "i"(2));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##c) : "r"(s##b), "i"(3));               \
    __asm__(#imm " %0, %1, %2, %3" : "=r"(r##d) : "r"(*(rk i)), "r"(s##d), "i"(0)); \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##d) : "r"(s##a), "i"(1));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##d) : "r"(s##b), "i"(2));               \
    __asm__(#imm " %0, %0, %1, %2" : "+r"(r##d) : "r"(s##c), "i"(3));

#define SAES_ENC_ODD_ROUND  SAES_ROUND(aes32esmi, u, t, 0, 1, 2, 3, ++)
#define SAES_ENC_EVEN_ROUND SAES_ROUND(aes32esmi, t, u, 0, 1, 2, 3, ++)
#define SAES_ENC_LAST_ROUND SAES_ROUND(aes32esi, t, u, 0, 1, 2, 3, ++)
#define SAES_DEC_ODD_ROUND  SAES_ROUND(aes32dsmi, u, t, 3, 2, 1, 0, --)
#define SAES_DEC_EVEN_ROUND SAES_ROUND(aes32dsmi, t, u, 3, 2, 1, 0, --)
#define SAES_DEC_LAST_ROUND SAES_ROUND(aes32dsi, t, u, 3, 2, 1, 0, --)
#define SAES_INIT           uint32_t u0, u1, u2, u3, t0, t1, t2, t3;
#define SAES_ENC_INIT       SAES_INIT
#define SAES_DEC_INIT                                      \
    rk += AES_RK_WORDS - __riscv_xlen / (sizeof(*rk) * 8); \
    SAES_INIT

#define SAES_LOAD(a, b, c, d, i)               \
    t##a = ((const uint32_t*)pt)[a] ^ *(rk i); \
    t##b = ((const uint32_t*)pt)[b] ^ *(rk i); \
    t##c = ((const uint32_t*)pt)[c] ^ *(rk i); \
    t##d = ((const uint32_t*)pt)[d] ^ *(rk i);

#define SAES_ENC_LOAD SAES_LOAD(0, 1, 2, 3, ++)
#define SAES_DEC_LOAD SAES_LOAD(3, 2, 1, 0, --)

#define SAES_STORE(a, b, c, d) \
    ((uint32_t*)ct)[0] = t##a; \
    ((uint32_t*)ct)[1] = t##b; \
    ((uint32_t*)ct)[2] = t##c; \
    ((uint32_t*)ct)[3] = t##d;

#define SAES_ENC_STORE   SAES_STORE(0, 1, 2, 3)
#define SAES_DEC_STORE   SAES_STORE(0, 1, 2, 3)

#define SAES_CONVERT_KEY dec_invmc((uint32_t*)keys);

const uint8_t aes_rcon[] = { // no hardware constants in rv32/rvk
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

static inline void aes_enc_key(uint32_t rk[AES_RK_WORDS], const uint8_t key[BITS / 8])
{
    uint32_t i;
    for (i = 0; i < BITS / 32; ++i)
        rk[i] = *(uint32_t*)(key + i * 4);
    while (1) {
        uint32_t tmp = (rk[i - 1] >> 8) | (rk[i - 1] << 24);

        __asm__("aes32esi %0, %1, %2, %3" : "=r"(rk[i]) : "r"(rk[i - (BITS / 32)] ^ (aes_rcon[i / (BITS / 32) - 1])), "r"(tmp), "i"(0));
        __asm__("aes32esi %0, %0, %1, %2" : "+r"(rk[i]) : "r"(tmp), "i"(1));
        __asm__("aes32esi %0, %0, %1, %2" : "+r"(rk[i]) : "r"(tmp), "i"(2));
        __asm__("aes32esi %0, %0, %1, %2" : "+r"(rk[i]) : "r"(tmp), "i"(3));
        ++i;
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
        if (i == AES_RK_WORDS)
            return;
#if BITS == 192
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
#elif BITS == 256 // ^^^ BITS == 192 ^^^
        __asm__("aes32esi %0, %1, %2, %3" : "=r"(rk[i]) : "r"(rk[i - (BITS / 32)]), "r"(rk[i - 1]), "i"(0));
        __asm__("aes32esi %0, %0, %1, %2" : "+r"(rk[i]) : "r"(rk[i - 1]), "i"(1));
        __asm__("aes32esi %0, %0, %1, %2" : "+r"(rk[i]) : "r"(rk[i - 1]), "i"(2));
        __asm__("aes32esi %0, %0, %1, %2" : "+r"(rk[i]) : "r"(rk[i - 1]), "i"(3));
        ++i;
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
        rk[i] = rk[i - BITS / 32] ^ rk[i - 1];
        ++i;
#endif            // ^^^ BITS == 256
    }
}

static inline void dec_invmc(uint32_t* v)
{
    for (size_t i = 4; i < AES_RK_WORDS - 4; i++) {
        uint32_t temp;
        __asm__("aes32esi  %0,zero,%1, %2" : "=r"(temp) : "r"(v[i]), "i"(0));
        __asm__("aes32esi  %0, %0, %1, %2" : "+r"(temp) : "r"(v[i]), "i"(1));
        __asm__("aes32esi  %0, %0, %1, %2" : "+r"(temp) : "r"(v[i]), "i"(2));
        __asm__("aes32esi  %0, %0, %1, %2" : "+r"(temp) : "r"(v[i]), "i"(3));

        __asm__("aes32dsmi %0,zero,%1, %2" : "=r"(v[i]) : "r"(temp), "i"(0));
        __asm__("aes32dsmi %0, %0, %1, %2" : "+r"(v[i]) : "r"(temp), "i"(1));
        __asm__("aes32dsmi %0, %0, %1, %2" : "+r"(v[i]) : "r"(temp), "i"(2));
        __asm__("aes32dsmi %0, %0, %1, %2" : "+r"(v[i]) : "r"(temp), "i"(3));
    }
}
#else // ^^^ __riscv_xlen == 32 ^^^ | vvv __riscv_xlen == 64 vvv

#define SAES_ROUND(imm, r, s)                                        \
    __asm__(#imm " %0, %1, %2" : "=r"(r##0) : "r"(s##0), "r"(s##1)); \
    __asm__(#imm " %0, %1, %2" : "=r"(r##1) : "r"(s##1), "r"(s##0));

#define SAES_ENC_ROUND(imm, r, s) \
    SAES_ROUND(imm, r, s);        \
    REKEY(r);
#define SAES_DEC_ROUND(imm, r, s) \
    s##1 ^= *(kp--);              \
    s##0 ^= *(kp--);              \
    SAES_ROUND(imm, r, s);
#define SAES_ENC_EVEN_ROUND SAES_ENC_ROUND(aes64esm, t, u);
#define SAES_ENC_ODD_ROUND  SAES_ENC_ROUND(aes64esm, u, t);
#define SAES_ENC_LAST_ROUND SAES_ENC_ROUND(aes64es, t, u);
#define SAES_DEC_EVEN_ROUND SAES_DEC_ROUND(aes64dsm, t, u);
#define SAES_DEC_ODD_ROUND  SAES_DEC_ROUND(aes64dsm, u, t);
#define SAES_DEC_LAST_ROUND SAES_DEC_ROUND(aes64ds, t, u);

#define SAES_INIT                             \
    const uint64_t* kp = (const uint64_t*)rk; \
    const uint64_t* pp = (const uint64_t*)pt; \
    uint64_t*       cp = (uint64_t*)ct;       \
    uint64_t        t0, t1, u0, u1;

#define SAES_DEC_INIT                                      \
    rk += AES_RK_WORDS - __riscv_xlen / (sizeof(*rk) * 8); \
    SAES_INIT

#define SAES_ENC_LOAD       \
    t0 = *(pp++) ^ *(kp++); \
    t1 = *(pp++) ^ *(kp++);

#define SAES_DEC_LOAD \
    t0 = *(pp++);     \
    t1 = *(pp++);

#define SAES_ENC_STORE \
    *(cp++) = t0;      \
    *(cp++) = t1;

#define SAES_DEC_STORE    \
    t1 ^= *kp--;          \
    *(cp++) = t0 ^ *kp--; \
    *(cp++) = t1;

#ifdef OTF
#define SAES_ENC_INIT                         \
    uint64_t ks, ka[BITS / 64], *kp = ka;     \
    for (int i = 0; i < BITS / 64; ++i)       \
        ka[i] = ((uint64_t*)rk)[i];           \
    const uint64_t* pp = (const uint64_t*)pt; \
    uint64_t*       cp = (uint64_t*)ct;       \
    uint64_t        t0, t1, u0, u1;           \
    enum { COUNTER_BASE = __COUNTER__ + 1 };

#if BITS == 192
#define HREK192(s, i)                                                                           \
    s##i ^= *(kp++);                                                                            \
    if (kp - ka == 3) {                                                                         \
        kp = ka;                                                                                \
        __asm__("aes64ks1i %0, %1, %2" : "=r"(ks) : "r"(ka[2]),                                 \
                                                    "i"((__COUNTER__ - COUNTER_BASE + 2) / 3)); \
        __asm__("aes64ks2 %0, %1, %0" : "+r"(ka[0]) : "r"(ks));                                 \
        __asm__("aes64ks2 %0, %1, %0" : "+r"(ka[1]) : "r"(ka[0]));                              \
        __asm__("aes64ks2 %0, %1, %0" : "+r"(ka[2]) : "r"(ka[1]));                              \
    }
#define REKEY(s)   \
    HREK192(s, 0); \
    HREK192(s, 1);
#else // ^^^ BITS == 192 ^^^ | vvv BITS == 128 or 256 vvv
#define REKEY(r)                                                                                                       \
    __asm__("aes64ks1i %0, %1, %2" : "=r"(ks) : "r"(ka[(kp + 2 - ka + 3) % (BITS / 64)]), "i"(r##RNUM));               \
    __asm__("aes64ks2 %0, %1, %0" : "+r"(ka[(kp + 2 - ka) % (BITS / 64)]) : "r"(ks));                                  \
    __asm__("aes64ks2 %0, %1, %0" : "+r"(ka[(kp + 2 - ka + 1) % (BITS / 64)]) : "r"(ka[(kp + 2 - ka) % (BITS / 64)])); \
    if (kp - ka == BITS / 64) {                                                                                        \
        kp = ka;                                                                                                       \
    }                                                                                                                  \
    r##0 ^= *(kp++);                                                                                                   \
    r##1 ^= *(kp++);
#define uRNUM (__COUNTER__ - COUNTER_BASE)
#if BITS == 128
#define tRNUM (__COUNTER__ - COUNTER_BASE)
#else // ^^^ BITS == 128 ^^^ | vvv BITS == 256 vvv
#define tRNUM (10)
#endif // ^^^ BITS == 256 ^^^
#endif // ^^^ BITS == 128 or 256 ^^^
#else  // ^^^ rv64 OTF ^^^ | vvv rv64 !OTF vvv
#define SAES_ENC_INIT SAES_INIT
#define REKEY(r)     \
    r##0 ^= *(kp++); \
    r##1 ^= *(kp++);
#endif // ^^^ !OTF ^^^
#define SAES_KEY_INIT                               \
    uint64_t*       kp = (uint64_t*)rk;             \
    static uint64_t ka[BITS / 64 + 1], *k = ka + 1; \
    enum { COUNTER_BASE = __COUNTER__ + 1 };

#define SAES_KEY_LOAD                      \
    for (size_t i = 0; i < BITS / 64; ++i) \
        k[i] = *(((const uint64_t*)key) + i);

#define SAES_KEY_ROUND                                                                                      \
    for (size_t j = 0; j < BITS / 64; ++j)                                                                  \
        *(kp++) = k[j];                                                                                     \
    __asm__("aes64ks1i %0, %1, %2" : "=r"(k[-1]) : "r"(k[BITS / 64 - 1]), "i"(__COUNTER__ - COUNTER_BASE)); \
    for (size_t j = 0; j < BITS / 64; ++j) {                                                                \
        if (j == 2 && BITS == 256)                                                                          \
            __asm__("aes64ks1i %0, %1, %2" : "=r"(k[-1]) : "r"(k[1]), "i"(10));                             \
        __asm__("aes64ks2 %0, %1, %0" : "+r"(k[j]) : "r"(k[(j == 2 && BITS == 256 ? 0 : j) - 1]));          \
    }

#define SAES_KEY_STORE \
    *(kp++) = k[0];    \
    *(kp++) = k[1];

static inline void aes_enc_key(uint32_t rk[44], const uint8_t key[16])
{
    SAES_KEY_INIT
    SAES_KEY_LOAD
    SAES_KEY_ROUND
    SAES_KEY_ROUND
    SAES_KEY_ROUND
    SAES_KEY_ROUND
    SAES_KEY_ROUND
    SAES_KEY_ROUND
    SAES_KEY_ROUND
#if BITS != 256
    SAES_KEY_ROUND
#if BITS == 128
    SAES_KEY_ROUND
    SAES_KEY_ROUND
#endif
#endif
    SAES_KEY_STORE
}

// Helper: apply inverse mixcolumns to a vector

static inline void dec_invmc(uint64_t* v)
{
    for (size_t i = 2; i < AES_RK_WORDS / 2 - 2; i++)
        __asm__("aes64im %0, %0" : "+r"(v[i]));
}
#define SAES_CONVERT_KEY dec_invmc((uint64_t*)keys);
#endif // ^^^ __riscv_xlen == 64 ^^^

__attribute__((always_inline)) static inline void aes_enc_ecb(uint8_t ct[], const uint8_t pt[], const uint32_t rk[])
{
    SAES_ENC_INIT
    SAES_ENC_LOAD
    SAES_ENC_ODD_ROUND
    SAES_ENC_EVEN_ROUND
    SAES_ENC_ODD_ROUND
    SAES_ENC_EVEN_ROUND
    SAES_ENC_ODD_ROUND
    SAES_ENC_EVEN_ROUND
    SAES_ENC_ODD_ROUND
    SAES_ENC_EVEN_ROUND
    SAES_ENC_ODD_ROUND
#if AES_ROUNDS > 10
    SAES_ENC_EVEN_ROUND
    SAES_ENC_ODD_ROUND
#if AES_ROUNDS > 12
    SAES_ENC_EVEN_ROUND
    SAES_ENC_ODD_ROUND
#endif
#endif
    SAES_ENC_LAST_ROUND
    SAES_ENC_STORE
}

__attribute__((always_inline)) static inline void aes_dec_ecb(uint8_t ct[], const uint8_t pt[], const uint32_t rk[])
{
    SAES_DEC_INIT
    SAES_DEC_LOAD
    SAES_DEC_ODD_ROUND
    SAES_DEC_EVEN_ROUND
    SAES_DEC_ODD_ROUND
    SAES_DEC_EVEN_ROUND
    SAES_DEC_ODD_ROUND
    SAES_DEC_EVEN_ROUND
    SAES_DEC_ODD_ROUND
    SAES_DEC_EVEN_ROUND
    SAES_DEC_ODD_ROUND
#if AES_ROUNDS > 10
    SAES_DEC_EVEN_ROUND
    SAES_DEC_ODD_ROUND
#if AES_ROUNDS > 12
    SAES_DEC_EVEN_ROUND
    SAES_DEC_ODD_ROUND
#endif
#endif
    SAES_DEC_LAST_ROUND
    SAES_DEC_STORE
}
#endif //  _AES_H_


