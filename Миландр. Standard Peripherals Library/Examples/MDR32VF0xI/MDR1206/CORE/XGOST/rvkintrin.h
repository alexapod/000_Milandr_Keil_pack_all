#ifndef _RVKINTRIN_H_
#define _RVKINTRIN_H_

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
//	rvkintrin.h
//	2021-02-13	Markku-Juhani O. Saarinen <mjos@pqshield.com>
//	Copyright (c) 2021, PQShield Ltd. All rights reserved.

//	RISC-V "K" extension proposal intrinsics

static inline uint64_t _rv_rev8(uint64_t rs)
{
    uint64_t rd;
    __asm__("rev8 %0, %1" : "=r"(rd) : "r"(rs));
    return rd;
}
#if __riscv_xlen == 64
static inline uint64_t _rv32_rev8(uint64_t rs)
{
    uint64_t rd;
    __asm__("rev8 %0, %1;\n\rsrl %0, %0, 32" : "=r"(rd) : "r"(rs));
    return rd;
}
#endif

static inline uint32_t _rv32_ror(uint32_t rs1, uint8_t rs2)
{
    rs2 &= 31;
    return ((uint32_t)rs1 >> rs2) | (rs1 << (32 - rs2));
}
#if __riscv_xlen == 64
static inline uint64_t _rv64_ror(uint64_t rs1, uint8_t rs2)
{
    rs2 &= 63;
    return ((uint64_t)rs1 >> rs2) | (rs1 << (64 - rs2));
}
#endif

#if __riscv_xlen == 32
static inline int32_t _rv32_unzip(int32_t rs1)
{
    int32_t rd;
    __asm__("unzip %0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline int32_t _rv32_zip(int32_t rs1)
{
    int32_t rd;
    __asm__("zip %0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
#endif

#ifdef __riscv_zknh
//	=== SHA256: Zkn (RV32, RV64), Zknh

static inline long _rv_sha256sig0(long rs1)
{
    long rd;
    __asm__("sha256sig0	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline long _rv_sha256sig1(long rs1)
{
    long rd;
    __asm__("sha256sig1	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline long _rv_sha256sum0(long rs1)
{
    long rd;
    __asm__("sha256sum0	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline long _rv_sha256sum1(long rs1)
{
    long rd;
    __asm__("sha256sum1	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}

//	=== SHA512: Zkn (RV32), Zknh

#if __riscv_xlen == 32
static inline int32_t _rv32_sha512sig0l(int32_t rs1, int32_t rs2)
{
    int32_t rd;
    __asm__("sha512sig0l	%0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2));
    return rd;
}
static inline int32_t _rv32_sha512sig0h(int32_t rs1, int32_t rs2)
{
    int32_t rd;
    __asm__("sha512sig0h	%0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2));
    return rd;
}
static inline int32_t _rv32_sha512sig1l(int32_t rs1, int32_t rs2)
{
    int32_t rd;
    __asm__("sha512sig1l	%0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2));
    return rd;
}
static inline int32_t _rv32_sha512sig1h(int32_t rs1, int32_t rs2)
{
    int32_t rd;
    __asm__("sha512sig1h	%0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2));
    return rd;
}
static inline int32_t _rv32_sha512sum0r(int32_t rs1, int32_t rs2)
{
    int32_t rd;
    __asm__("sha512sum0r	%0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2));
    return rd;
}
static inline int32_t _rv32_sha512sum1r(int32_t rs1, int32_t rs2)
{
    int32_t rd;
    __asm__("sha512sum1r	%0, %1, %2" : "=r"(rd) : "r"(rs1), "r"(rs2));
    return rd;
}
#endif

//	=== SHA512: Zkn (RV64), Zknh

#if __riscv_xlen == 64
static inline int64_t _rv64_sha512sig0(int64_t rs1)
{
    int64_t rd;
    __asm__("sha512sig0	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline int64_t _rv64_sha512sig1(int64_t rs1)
{
    int64_t rd;
    __asm__("sha512sig1	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline int64_t _rv64_sha512sum0(int64_t rs1)
{
    int64_t rd;
    __asm__("sha512sum0	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline int64_t _rv64_sha512sum1(int64_t rs1)
{
    int64_t rd;
    __asm__("sha512sum1	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
#endif
#endif // __riscv_zknh

#ifdef __riscv_zksh
//	=== SM3:	Zks (RV32, RV64), Zksh

static inline long _rv_sm3p0(long rs1)
{
    long rd;
    __asm__("sm3p0	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
static inline long _rv_sm3p1(long rs1)
{
    long rd;
    __asm__("sm3p1	%0, %1" : "=r"(rd) : "r"(rs1));
    return rd;
}
#endif // __riscv_zksh

#ifdef __riscv_zksed
//	=== SM4:	Zks (RV32, RV64), Zksed // never used

static inline long _rv_sm4ks(int32_t rs1, int32_t rs2, int bs)
{
    long rd;
    __asm__("sm4ks %0, %1, %2, %3" : "=r"(rd) : "r"(rs1), "r"(rs2), "i"(bs));
    return rd;
}
static inline long _rv_sm4ed(int32_t rs1, int32_t rs2, int bs)
{
    long rd;
    __asm__("sm4ed %0, %1, %2, %3" : "=r"(rd) : "r"(rs1), "r"(rs2), "i"(bs));
    return rd;
}
#endif // __riscv_zksed

#endif // _RVKINTRIN_H_


