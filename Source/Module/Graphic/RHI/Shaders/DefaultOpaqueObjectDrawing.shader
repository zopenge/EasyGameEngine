<?xml version="1.0" encoding="utf-8"?>
<Shader>
	<Declaration>
    <Variable qualifier="uniform" type="mat4" name="rViewProjection"/>
    <Variable qualifier="uniform" type="sampler2D" name="cTexSampler0"/>
    <Variable qualifier="attribute" type="vec4" name="cPosition"/>
    <Variable qualifier="attribute" type="vec4" name="cColor0"/>
    <Variable qualifier="attribute" type="vec2" name="cTexCoords0"/>
    <Variable qualifier="varying" precision="lowp" type="vec2" name="sUV"/>
    <Variable qualifier="varying" precision="lowp" type="vec4" name="sPrimColor"/>
  </Declaration>
	<VSMain>
		<Code>
			<Text>
        sPrimColor = cColor0;
        sUV = cTexCoords0;
      </Text>
			<ReturnOp>cPosition * rViewProjection</ReturnOp>
		</Code>
	</VSMain>
	<PSMain>
		<Code>
      <Variable precision="lowp" type="vec4" name="tex_color" default_value="texture2D(cTexSampler0, sUV)"/>
      <Text>
        if ( tex_color.w &lt; 1.0 )
          discard;
        tex_color.xyzw *= sPrimColor.zyxw;
      </Text>
			<ReturnOp>tex_color</ReturnOp>
		</Code>
	</PSMain>
</Shader>
