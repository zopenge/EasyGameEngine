//! @file     script_callfunc_x86.cpp
//! @author   LiCode
//! @version  1.1.0.613
//! @date     2011/01/17
//! Copyright ...

#include "EGEScript.h"

#pragma managed(push, off)

//----------------------------------------------------------------------------
// x86:ASM Implementation
//----------------------------------------------------------------------------

#ifndef CLEAR_FPU_STACK
#define CLEAR_FPU_STACK fninit
#endif

// On GCC we need to prevent the compiler from inlining these assembler routines when
// optimizing for speed (-O3), as the loop labels get duplicated which cause compile errors.

void NOINLINE CallCDeclFunction(const _dword* args, int paramSize, size_t func)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

		// Call function
		call [func]

		// Pop arguments from stack
		add  esp, paramSize

		// Restore registers
		pop  ecx

		// return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  12(%ebp), %eax \n" // paramSize
		"addl  $4, %eax       \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"movl  12(%ebp), %ecx \n" // paramSize
		"movl  8(%ebp), %eax  \n" // args
		"addl  %ecx, %eax     \n" // push arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy        \n"
		"copyloop:            \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop       \n"
		"endcopy:             \n"
		"call  *16(%ebp)      \n"
		"addl  12(%ebp), %esp \n" // pop arguments

		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallCDeclFunctionObjLast(const _void* obj, const _dword* args, int paramSize, size_t func)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Push the object pointer as the last argument to the function
		push obj

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

		// Call function
		call [func]

		// Pop arguments from stack
		add  esp, paramSize
		add  esp, 4

		// Restore registers
		pop  ecx

		// return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(obj);
	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  16(%ebp), %eax \n" // paramSize
		"addl  $8, %eax       \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"pushl 8(%ebp)        \n"
		"movl  16(%ebp), %ecx \n" // paramSize
		"movl  12(%ebp), %eax \n" // args
		"addl  %ecx, %eax     \n" // push arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy8       \n"
		"copyloop8:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop8      \n"
		"endcopy8:            \n"
		"call  *20(%ebp)      \n"
		"addl  16(%ebp), %esp \n" // pop arguments
		"addl  $4, %esp       \n"

		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallCDeclFunctionObjFirst(const _void* obj, const _dword* args, int paramSize, size_t func)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

		// push object as first parameter
		push obj

		// Call function
		call [func]

		// Pop arguments from stack
		add  esp, paramSize
		add  esp, 4

		// Restore registers
		pop  ecx

		// return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(obj);
	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  16(%ebp), %eax \n" // paramSize
		"addl  $8, %eax       \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"movl  16(%ebp), %ecx \n" // paramSize
		"movl  12(%ebp), %eax \n" // args
		"addl  %ecx, %eax     \n" // push arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy6       \n"
		"copyloop6:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop6      \n"
		"endcopy6:            \n"
		"pushl 8(%ebp)        \n" // push obj
		"call  *20(%ebp)      \n"
		"addl  16(%ebp), %esp \n" // pop arguments
		"addl  $4, %esp       \n"

		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallCDeclFunctionRetByRefObjFirst_impl(const _void* obj, const _dword* args, int paramSize, size_t func, _void* retPtr)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

		// Push the object pointer
		push obj

		// Push the return pointer
		push retPtr;

		// Call function
		call [func]

		// Pop arguments from stack
		add  esp, paramSize

#ifndef CALLEE_POPS_HIDDEN_RETURN_POINTER
		// Pop the return pointer
		add  esp, 8
#else
		add  esp, 4
#endif
		// Restore registers
		pop  ecx

		// return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(obj);
	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);
	UNUSED_VAR(retPtr);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  16(%ebp), %eax \n" // paramSize
		"addl  $12, %eax      \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"movl  16(%ebp), %ecx \n" // paramSize
		"movl  12(%ebp), %eax \n" // args
		"addl  %ecx, %eax     \n" // push arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy5       \n"
		"copyloop5:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop5      \n"
		"endcopy5:            \n"
		"pushl 8(%ebp)        \n" // push object first
		"pushl 24(%ebp)       \n" // retPtr
		"call  *20(%ebp)      \n" // func
		"addl  16(%ebp), %esp \n" // pop arguments
#ifndef CALLEE_POPS_HIDDEN_RETURN_POINTER
		"addl  $8, %esp       \n" // Pop the return pointer and object pointer
#else
		"addl  $4, %esp       \n" // Pop the object pointer
#endif
		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallCDeclFunctionRetByRef_impl(const _dword* args, int paramSize, size_t func, _void* retPtr)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

		// Push the return pointer
		push retPtr;

		// Call function
		call [func]

		// Pop arguments from stack
		add  esp, paramSize

#ifndef CALLEE_POPS_HIDDEN_RETURN_POINTER
		// Pop the return pointer
		add  esp, 4
#endif
		// Restore registers
		pop  ecx

		// return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);
	UNUSED_VAR(retPtr);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  12(%ebp), %eax \n" // paramSize
		"addl  $8, %eax       \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"movl  12(%ebp), %ecx \n" // paramSize
		"movl  8(%ebp), %eax  \n" // args
		"addl  %ecx, %eax     \n" // push arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy7       \n"
		"copyloop7:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop7      \n"
		"endcopy7:            \n"
		"pushl 20(%ebp)       \n" // retPtr
		"call  *16(%ebp)      \n" // func
		"addl  12(%ebp), %esp \n" // pop arguments
#ifndef CALLEE_POPS_HIDDEN_RETURN_POINTER
		"addl  $4, %esp       \n" // Pop the return pointer
#endif
		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallCDeclFunctionRetByRefObjLast_impl(const _void* obj, const _dword* args, int paramSize, size_t func, _void* retPtr)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		push obj

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

		// Push the return pointer
		push retPtr;

		// Call function
		call [func]

		// Pop arguments from stack
		add  esp, paramSize
		add  esp, 4

#ifndef CALLEE_POPS_HIDDEN_RETURN_POINTER
		// Pop the return pointer
		add  esp, 4
#endif
		// Restore registers
		pop  ecx

		// return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(obj);
	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);
	UNUSED_VAR(retPtr);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  16(%ebp), %eax \n" // paramSize
		"addl  $12, %eax      \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"pushl 8(%ebp)        \n"
		"movl  16(%ebp), %ecx \n" // paramSize
		"movl  12(%ebp), %eax \n" // args
		"addl  %ecx, %eax     \n" // push arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy4       \n"
		"copyloop4:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop4      \n"
		"endcopy4:            \n"
		"pushl 24(%ebp)       \n" // retPtr
		"call  *20(%ebp)      \n" // func
		"addl  16(%ebp), %esp \n" // pop arguments
#ifndef CALLEE_POPS_HIDDEN_RETURN_POINTER
		"addl  $8, %esp       \n" // Pop the return pointer
#else
		"addl  $4, %esp       \n" // Pop the return pointer
#endif
		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallSTDCallFunction(const _dword* args, int paramSize, size_t func)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

		// Call function
		call [func]

		// The callee already removed parameters from the stack

		// Restore registers
		pop  ecx

		// return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  12(%ebp), %eax \n" // paramSize
		"addl  $4, %eax       \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"movl  12(%ebp), %ecx \n" // paramSize
		"movl  8(%ebp), %eax  \n" // args
		"addl  %ecx, %eax     \n" // push arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy2       \n"
		"copyloop2:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop2      \n"
		"endcopy2:            \n"
		"call  *16(%ebp)      \n" // callee pops the arguments

		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallThisCallFunction(const _void* obj, const _dword* args, int paramSize, size_t func)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

#ifdef THISCALL_PASS_OBJECT_POINTER_ON_THE_STACK
		// Push the object pointer on the stack
		push obj
#else
		// Move object pointer to ECX
		mov  ecx, obj
#endif

		// Call function
		call [func]

#ifndef THISCALL_CALLEE_POPS_ARGUMENTS
		// Pop arguments
		add  esp, paramSize
#ifdef THISCALL_PASS_OBJECT_POINTER_ON_THE_STACK
		// Pop object pointer
		add esp, 4
#endif
#endif

		// Restore registers
		pop  ecx

		// Return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(obj);
	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  16(%ebp), %eax \n" // paramSize
		"addl  $8, %eax       \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"movl  16(%ebp), %ecx \n" // paramSize
		"movl  12(%ebp), %eax \n" // args
		"addl  %ecx, %eax     \n" // push all arguments on the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy1       \n"
		"copyloop1:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop1      \n"
		"endcopy1:            \n"
		"movl  8(%ebp), %ecx  \n" // move obj into ECX
		"pushl 8(%ebp)        \n" // push obj on the stack
		"call  *20(%ebp)      \n"
		"addl  16(%ebp), %esp \n" // pop arguments
		"addl  $4, %esp       \n" // pop obj

		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

void NOINLINE CallThisCallFunctionRetByRef_impl(const _void* obj, const _dword* args, int paramSize, size_t func, _void* retPtr)
{
#if defined ASM_INTEL

	// Copy the data to the real stack. If we fail to do
	// this we may run into trouble in case of exceptions.
	__asm
	{
		// We must save registers that are used
		push ecx

		// Clear the FPU stack, in case the called function doesn't do it by itself
		CLEAR_FPU_STACK

		// Copy arguments from script
		// stack to application stack
		mov  ecx, paramSize
		mov  eax, args
		add  eax, ecx
		cmp  ecx, 0
		je   endcopy
copyloop:
		sub  eax, 4
		push dword ptr [eax]
		sub  ecx, 4
		jne  copyloop
endcopy:

#ifdef THISCALL_PASS_OBJECT_POINTER_ON_THE_STACK
		// Push the object pointer on the stack
		push obj
#else
		// Move object pointer to ECX
		mov  ecx, obj
#endif

		// Push the return pointer
		push retPtr

		// Call function
		call [func]

#ifndef THISCALL_CALLEE_POPS_HIDDEN_RETURN_POINTER
		// Pop the return pointer
		add  esp, 4
#endif

#ifndef THISCALL_CALLEE_POPS_ARGUMENTS
		// Pop arguments
		add  esp, paramSize
#ifdef THISCALL_PASS_OBJECT_POINTER_ON_THE_STACK
		// Pop object pointer
		add esp, 4
#endif
#endif

		// Restore registers
		pop  ecx

		// Return value in EAX or EAX:EDX
	}

#elif defined ASM_AT_N_T

	UNUSED_VAR(obj);
	UNUSED_VAR(args);
	UNUSED_VAR(paramSize);
	UNUSED_VAR(func);
	UNUSED_VAR(retPtr);

	asm("pushl %ecx           \n"
		_S(CLEAR_FPU_STACK)  "\n"

		// Need to align the stack pointer so that it is aligned to 16 bytes when making the function call.
		// It is assumed that when entering this function, the stack pointer is already aligned, so we need
		// to calculate how much we will put on the stack during this call.
		"movl  16(%ebp), %eax \n" // paramSize
		"addl  $12, %eax      \n" // counting esp that we will push on the stack
		"movl  %esp, %ecx     \n"
		"subl  %eax, %ecx     \n"
		"andl  $15, %ecx      \n"
		"movl  %esp, %eax     \n"
		"subl  %ecx, %esp     \n"
		"pushl %eax           \n" // Store the original stack pointer

		"movl  16(%ebp), %ecx \n" // paramSize
		"movl  12(%ebp), %eax \n" // args
		"addl  %ecx, %eax     \n" // push all arguments to the stack
		"cmp   $0, %ecx       \n"
		"je    endcopy3       \n"
		"copyloop3:           \n"
		"subl  $4, %eax       \n"
		"pushl (%eax)         \n"
		"subl  $4, %ecx       \n"
		"jne   copyloop3      \n"
		"endcopy3:            \n"
		"movl  8(%ebp), %ecx  \n" // move obj into ECX
		"pushl 8(%ebp)        \n" // push obj on the stack
		"pushl 24(%ebp)       \n" // push retPtr on the stack
		"call  *20(%ebp)      \n"
#ifndef THISCALL_CALLEE_POPS_HIDDEN_RETURN_POINTER
		"addl  $4, %esp       \n" // pop return pointer
#endif
		"addl  16(%ebp), %esp \n" // pop arguments
		"addl  $4, %esp       \n" // pop the object pointer
		                          // the return pointer was popped by the callee
		// Pop the alignment bytes
		"popl  %esp           \n"

		"popl  %ecx           \n");

#endif
}

_dword GetReturnedFloat()
{
	_dword f;

#if defined ASM_INTEL

	// Get the float value from ST0
	__asm fstp dword ptr [f]

#elif defined ASM_AT_N_T

	asm("fstps %0 \n" : "=m" (f));

#endif

	return f;
}

_qword GetReturnedDouble()
{
	_qword d;

#if defined ASM_INTEL

	// Get the double value from ST0
	__asm fstp qword ptr [d]

#elif defined ASM_AT_N_T

	asm("fstpl %0 \n" : "=m" (d));

#endif

	return d;
}

// The ASM -> C function conversion
typedef _qword (*t_CallCDeclQW)(const _dword*, int, size_t);
typedef _qword (*t_CallCDeclQWObj)(void* obj, const _dword*, int, size_t);
typedef _dword (*t_CallCDeclRetByRef)(const _dword*, int, size_t, void*);
typedef _dword (*t_CallCDeclObjRetByRef)(void* obj, const _dword*, int, size_t, void*);
typedef _qword (*t_CallSTDCallQW)(const _dword*, int, size_t);
typedef _qword (*t_CallThisCallQW)(const void*, const _dword*, int, size_t);
typedef _dword (*t_CallThisCallRetByRef)(const void*, const _dword*, int, size_t, void*);

// Initialize function pointers
const t_CallCDeclQW CallCDeclFunctionQWord = (t_CallCDeclQW)CallCDeclFunction;
const t_CallCDeclQWObj CallCDeclFunctionQWordObjLast = (t_CallCDeclQWObj)CallCDeclFunctionObjLast;
const t_CallCDeclQWObj CallCDeclFunctionQWordObjFirst = (t_CallCDeclQWObj)CallCDeclFunctionObjFirst;
const t_CallCDeclRetByRef CallCDeclFunctionRetByRef = (t_CallCDeclRetByRef)CallCDeclFunctionRetByRef_impl;
const t_CallCDeclObjRetByRef CallCDeclFunctionRetByRefObjLast = (t_CallCDeclObjRetByRef)CallCDeclFunctionRetByRefObjLast_impl;
const t_CallCDeclObjRetByRef CallCDeclFunctionRetByRefObjFirst = (t_CallCDeclObjRetByRef)CallCDeclFunctionRetByRefObjFirst_impl;
const t_CallSTDCallQW CallSTDCallFunctionQWord = (t_CallSTDCallQW)CallSTDCallFunction;
const t_CallThisCallQW CallThisCallFunctionQWord = (t_CallThisCallQW)CallThisCallFunction;
const t_CallThisCallRetByRef CallThisCallFunctionRetByRef = (t_CallThisCallRetByRef)CallThisCallFunctionRetByRef_impl;

//----------------------------------------------------------------------------
// _scriptCallFunc:x86 Implementation
//----------------------------------------------------------------------------

_qword _scriptCallFunc::CallNativeFunc( ScriptVMRegisters& vm_registers, const ScriptNativeFuncInfo& func_info, _void* object, _dword* args )
{
	// The return value
	_qword ret = 0;

	// Call it
	switch ( func_info.mCallConv )
	{
		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL:
		{
			ret = CallCDeclFunctionQWord( args, func_info.mParamSize, (size_t) func_info.mFuncPointer );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL_RETURN_IN_MEM:
		{
			ret = CallCDeclFunctionRetByRef( args, func_info.mParamSize, (size_t) func_info.mFuncPointer, vm_registers.mObjectRegister );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_STDCALL:
		{
			ret = CallSTDCallFunctionQWord( args, func_info.mParamSize, (size_t) func_info.mFuncPointer );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_THISCALL:
		{
			ret = CallThisCallFunctionQWord( object, args, func_info.mParamSize, (size_t) func_info.mFuncPointer );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_THISCALL_RETURN_IN_MEM:
		{
			ret = CallThisCallFunctionRetByRef( object, args, func_info.mParamSize, (size_t) func_info.mFuncPointer, vm_registers.mObjectRegister );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL:
		{
			// Get virtual function table from the object pointer
			_dword* vftable = *(_dword**) object;

			ret = CallThisCallFunctionQWord( object, args, func_info.mParamSize, vftable[ size_t( func_info.mFuncPointer ) >> 2 ] );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_VIRTUAL_THISCALL_RETURN_IN_MEM:
		{
			// Get virtual function table from the object pointer
			_dword* vftable = *(_dword**) object;

			ret = CallThisCallFunctionRetByRef( object, args, func_info.mParamSize, vftable[ size_t( func_info.mFuncPointer ) >> 2 ], vm_registers.mObjectRegister );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJLAST:
		{
			ret = CallCDeclFunctionQWordObjLast( object, args, func_info.mParamSize, (size_t) func_info.mFuncPointer );
		}
		break;

		case _SCRIPT_FUNC_INTERNAL_CALL_CDECL_OBJFIRST:
		{
			ret = CallCDeclFunctionQWordObjFirst( object, args, func_info.mParamSize, (size_t) func_info.mFuncPointer );
		}
		break;

		default:
			break;
	}

	// If the return is a float value we need to get the value from the FP register
	if ( func_info.mRetFlags.HasFlags( ScriptNativeFuncInfo::_RET_FLAG_AS_FLOAT ) )
	{
		if ( func_info.mHostReturnSize == 4 )
			*(_dword*) &ret = GetReturnedFloat( );
		else
			ret = GetReturnedDouble( );
	}

	return ret;
}

#pragma managed(pop)
