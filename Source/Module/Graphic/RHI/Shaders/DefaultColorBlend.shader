<?xml version="1.0" encoding="utf-8"?>
<Shader version="1.2">
	<Declaration>
		<Variable qualifier="uniform" type="mat4" name="rViewProjection"/>
		<Variable qualifier="uniform" type="sampler2D" name="cTexSampler0"/>
    <Variable qualifier="uniform" type="vec4" name="cBlendColor"/>
    <Variable qualifier="attribute" type="vec4" name="cPosition"/>
		<Variable qualifier="attribute" type="vec4" name="cColor0"/>
		<Variable qualifier="attribute" type="vec2" name="cTexCoords0"/>
		<Variable qualifier="varying" precision="lowp" type="vec2" name="sUV"/>
		<Variable qualifier="varying" precision="lowp" type="vec4" name="sPrimColor"/>
    <Variable qualifier="varying" precision="lowp" type="vec4" name="sBlendColor"/>
  </Declaration>
  <Functions>
    <Function name="mix_color" scope="PSMain">
      <Ret precision="lowp" type="vec4" />
      <Argument type="vec4" name="tex_color"/>
      <Code>
        <Text>
          return vec4(mix(tex_color, sBlendColor, sBlendColor.w).rgb, tex_color.w);
        </Text>
      </Code>
    </Function>
  </Functions>
	<VSMain>
		<Code>
			<Text>
        sPrimColor = cColor0;
        sBlendColor = cBlendColor;
        sUV = cTexCoords0;
      </Text>
			<ReturnOp>cPosition * rViewProjection</ReturnOp>
		</Code>
	</VSMain>
	<PSMain>
    <Declaration>
      <Precision type="float">lowp</Precision>
    </Declaration>
    <Code>
      <Variable precision="lowp" type="vec4" name="tex_color" default_value="texture2D(cTexSampler0, sUV)"/>
      <ReturnOp>mix_color(tex_color)</ReturnOp>
    </Code>
  </PSMain>
</Shader>