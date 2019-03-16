<?xml version="1.0" encoding="utf-8"?>
<Shader version="1.2">
  <Declaration>
		<Variable qualifier="uniform" type="mat4" name="rViewProjection"/>
		<Variable qualifier="attribute" type="vec4" name="cPosition"/>
		<Variable qualifier="attribute" type="vec4" name="cColor0"/>
		<Variable qualifier="varying" precision="lowp" type="vec4" name="sPrimColor"/>
	</Declaration>
	<VSMain>
		<Code>
			<Text>
				sPrimColor = cColor0;
			</Text>
			<ReturnOp>cPosition * rViewProjection</ReturnOp>
		</Code>
	</VSMain>
	<PSMain>
		<Code>
      <Variable precision="lowp" type="vec4" name="tmpvar_1"/>
      <Text>
        tmpvar_1.xyz = sPrimColor.zyx;
        tmpvar_1.w = sPrimColor.w;
      </Text>
			<ReturnOp>tmpvar_1</ReturnOp>
		</Code>
	</PSMain>
</Shader>
