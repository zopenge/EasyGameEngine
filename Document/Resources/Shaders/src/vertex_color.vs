#include "common.inc"

uniform mat4 uMVPTransform;

varying vec4 vColor0;

void main ()
{
  vColor0 = cColor0.zyxw;
  
  gl_Position = cPosition * uMVPTransform;
}


