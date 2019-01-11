// Version
#ifdef GLSL
	#version 1.0
#else
	#version 1.2
#endif

// Precision
#ifdef GLSL
	#define _lowp lowp
	#define _mediump mediump
	#define _highp highp
#else
	#define _lowp 
	#define _mediump 
	#define _highp 
#endif