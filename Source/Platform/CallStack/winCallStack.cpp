#include "EGEPlatform.h"

extern "C" void* __cdecl _exception_info();

_ubool CallStackFrame::GetCurrentCallStack(CallStackFrame& callstack) {
	// First we try to get the callstack frame without exception occurred
	if (DebugSymbol::StackWalk(_null, OnCallStackFrameCallback, &callstack) == _true)
		return _true;

	// Because we get the callstack frame without exception occurred failed, now we bring the exception and try to get it again
	__try {
		*((_byte*)0) = 0;
	} __except (callstack.Create(_exception_info()), 1) {
	}

	return _true;
}

_void CallStackFrame::Create(_void* exception) {
	// Get exception function information
	EXCEPTION_POINTERS* exppointer = (EXCEPTION_POINTERS*)exception;
	CONTEXT* context = exppointer->ContextRecord;

	// Walk the callstack by context
	DebugSymbol::StackWalk(context, OnCallStackFrameCallback, this);
}