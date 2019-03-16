<?xml version="1.0" encoding="utf-8"?>
<Shader version="1.2">
  <Declaration>
		<Variable qualifier="uniform" type="mat4" name="rViewProjection"/>
		<Variable qualifier="uniform" type="sampler2D" name="cTexSampler0"/>
    <Variable qualifier="uniform" type="vec4" name="cBlurColor"/>
    <Variable qualifier="uniform" type="vec2" name="cTextureSize"/>
    <Variable qualifier="uniform" type="float" name="cBlurRate"/>
    <Variable qualifier="attribute" type="vec4" name="cPosition"/>
		<Variable qualifier="attribute" type="vec4" name="cColor0"/>
		<Variable qualifier="attribute" type="vec2" name="cTexCoords0"/>
    <Variable qualifier="varying" precision="lowp" type="vec2" name="sUV"/>
    <Variable qualifier="varying" precision="lowp" type="vec2" name="sTextureSize"/>
    <Variable qualifier="varying" precision="lowp" type="float" name="sBlurRate"/>
    <Variable qualifier="varying" precision="lowp" type="vec4" name="sBlurColor"/>
  </Declaration>
	<VSMain>
		<Code>
			<Text>
        sBlurColor = cBlurColor;
        sUV = cTexCoords0;
        sTextureSize = cTextureSize;
        sBlurRate = cBlurRate;
      </Text>
			<ReturnOp>cPosition * rViewProjection</ReturnOp>
		</Code>
	</VSMain>
  <PSMain>
    <Declaration>
      <Precision type="float">lowp</Precision>
    </Declaration>
    <Code>
      <Variable precision="lowp" type="vec2" name="new_uv" default_value=""/>
      <Text>
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_1;
        tmpvar_1 = texture2D (cTexSampler0, new_uv).w;
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_2;
        tmpvar_2 = (tmpvar_1 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_3;
        tmpvar_3 = (tmpvar_2 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_4;
        tmpvar_4 = (tmpvar_3 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_5;
        tmpvar_5 = (tmpvar_4 + (texture2D (cTexSampler0, new_uv).w * 4.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_6;
        tmpvar_6 = (tmpvar_5 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        float tmpvar_7;
        tmpvar_7 = (tmpvar_6 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        float tmpvar_8;
        tmpvar_8 = (tmpvar_7 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        vec4 tmpvar_9;
        tmpvar_9.xyz = sBlurColor.xyz;
        tmpvar_9.w = (((tmpvar_8 + texture2D (cTexSampler0, new_uv).w) * sBlurRate) / 16.0);
      </Text>
      <ReturnOp>tmpvar_9</ReturnOp>
    </Code>
	</PSMain>
</Shader>
