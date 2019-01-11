#include "common.inc"

uniform sampler2D uDiffuse;

uniform mat4 uMVPTransform;

varying vec2 vUV0;
varying vec4 vColor0;

void main ()
{
  vUV0 = cTexCoords0;
  vColor0 = cColor0.zyxw;
  
  gl_Position = cPosition * uMVPTransform;
}


