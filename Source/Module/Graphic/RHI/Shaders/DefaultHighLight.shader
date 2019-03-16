<?xml version="1.0" encoding="utf-8"?>
<Shader version="1.2">
  <Declaration>
		<Variable qualifier="uniform" type="mat4" name="rViewProjection"/>
		<Variable qualifier="uniform" type="sampler2D" name="cTexSampler0"/>
    <Variable qualifier="uniform" type="vec4" name="cHighLightColor"/>
    <Variable qualifier="attribute" type="vec4" name="cPosition"/>
		<Variable qualifier="attribute" type="vec4" name="cColor0"/>
		<Variable qualifier="attribute" type="vec2" name="cTexCoords0"/>
		<Variable qualifier="varying" precision="lowp" type="vec2" name="sUV"/>
		<Variable qualifier="varying" precision="lowp" type="vec4" name="sPrimColor"/>
    <Variable qualifier="varying" precision="lowp" type="vec4" name="sHighLightColor"/>
  </Declaration>
	<VSMain>
		<Code>
			<Text>
        sPrimColor = cColor0;
        sHighLightColor = cHighLightColor;
        sUV = cTexCoords0;
      </Text>
			<ReturnOp>cPosition * rViewProjection</ReturnOp>
		</Code>
	</VSMain>
	<PSMain>
		<Code>
			<ReturnOp>sPrimColor * texture2D(cTexSampler0, sUV) + sHighLightColor</ReturnOp>
		</Code>
  </PSMain>
</Shader>