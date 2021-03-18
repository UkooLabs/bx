/*
 * Copyright 2010-2021 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx#license-bsd-2-clause
 */

#ifndef BX_CPU_H_HEADER_GUARD
#define BX_CPU_H_HEADER_GUARD

#include "bx.h"

#if BX_COMPILER_MSVC
#  if BX_PLATFORM_XBOX360
#	include <ppcintrinsics.h>
#	include <xtl.h>
#   else
#	include <math.h> // math.h is included because VS bitches:
					 // warning C4985: 'ceil': attributes not present on previous declaration.
					 // must be included before intrin.h.
#	include <intrin.h>
#	include <windows.h>
# endif
#	if BX_PLATFORM_WINRT
#		define _InterlockedExchangeAdd64 InterlockedExchangeAdd64
#	endif // BX_PLATFORM_WINRT
extern "C" void _ReadBarrier();
extern "C" void _WriteBarrier();
extern "C" void _ReadWriteBarrier();
#	pragma intrinsic(_ReadBarrier)
#	pragma intrinsic(_WriteBarrier)
#	pragma intrinsic(_ReadWriteBarrier)
#	pragma intrinsic(_InterlockedExchangeAdd)
#	pragma intrinsic(_InterlockedCompareExchange)
#endif // BX_COMPILER_MSVC

namespace bx
{
	///
	void readBarrier();

	///
	void writeBarrier();

	///
	void readWriteBarrier();

	///
	inline void memoryBarrier()
	{
#if BX_PLATFORM_XBOX360
        __lwsync();
#elif BX_PLATFORM_WINRT
		MemoryBarrier();
#elif BX_COMPILER_MSVC
		_mm_mfence();
#else
		__sync_synchronize();
//		asm volatile("mfence":::"memory");
#endif // BX_COMPILER
	}

	///
	template<typename Ty>
	Ty atomicFetchAndAdd(volatile Ty* _ptr, Ty _value);

	///
	template<typename Ty>
	Ty atomicAddAndFetch(volatile Ty* _ptr, Ty _value);

	///
	template<typename Ty>
	Ty atomicFetchAndSub(volatile Ty* _ptr, Ty _value);

	///
	template<typename Ty>
	Ty atomicSubAndFetch(volatile Ty* _ptr, Ty _value);

	///
	template<typename Ty>
	Ty atomicCompareAndSwap(volatile Ty* _ptr, Ty _old, Ty _new);

	///
	template<typename Ty>
	Ty atomicFetchTestAndAdd(volatile Ty* _ptr, Ty _test, Ty _value);

	///
	template<typename Ty>
	Ty atomicFetchTestAndSub(volatile Ty* _ptr, Ty _test, Ty _value);

	///
	template<typename Ty>
	Ty atomicFetchAndAddsat(volatile Ty* _ptr, Ty _value, Ty _max);

	///
	template<typename Ty>
	Ty atomicFetchAndSubsat(volatile Ty* _ptr, Ty _value, Ty _min);

	///
	void* atomicExchangePtr(void** _ptr, void* _new);

} // namespace bx

#include "inline/cpu.inl"

#endif // BX_CPU_H_HEADER_GUARD
