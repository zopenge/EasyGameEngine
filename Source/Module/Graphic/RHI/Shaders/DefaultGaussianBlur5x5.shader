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
        new_uv.x = (sUV.x + (-2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-2.0 / sTextureSize.y));
        float tmpvar_1;
        tmpvar_1 = texture2D (cTexSampler0, new_uv).w;
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-2.0 / sTextureSize.y));
        float tmpvar_2;
        tmpvar_2 = (tmpvar_1 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-2.0 / sTextureSize.y));
        float tmpvar_3;
        tmpvar_3 = (tmpvar_2 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (-2.0 / sTextureSize.y));
        float tmpvar_4;
        tmpvar_4 = (tmpvar_3 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-2.0 / sTextureSize.y));
        float tmpvar_5;
        tmpvar_5 = (tmpvar_4 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (-2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_6;
        tmpvar_6 = (tmpvar_5 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_7;
        tmpvar_7 = (tmpvar_6 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_8;
        tmpvar_8 = (tmpvar_7 + (texture2D (cTexSampler0, new_uv).w * 4.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_9;
        tmpvar_9 = (tmpvar_8 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (-1.0 / sTextureSize.y));
        float tmpvar_10;
        tmpvar_10 = (tmpvar_9 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (-2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_11;
        tmpvar_11 = (tmpvar_10 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_12;
        tmpvar_12 = (tmpvar_11 + (texture2D (cTexSampler0, new_uv).w * 4.0));
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_13;
        tmpvar_13 = (tmpvar_12 + (texture2D (cTexSampler0, new_uv).w * 8.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_14;
        tmpvar_14 = (tmpvar_13 + (texture2D (cTexSampler0, new_uv).w * 4.0));
        new_uv.x = (sUV.x + (2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (0.0 / sTextureSize.y));
        float tmpvar_15;
        tmpvar_15 = (tmpvar_14 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (-2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        float tmpvar_16;
        tmpvar_16 = (tmpvar_15 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        float tmpvar_17;
        tmpvar_17 = (tmpvar_16 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        float tmpvar_18;
        tmpvar_18 = (tmpvar_17 + (texture2D (cTexSampler0, new_uv).w * 4.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        float tmpvar_19;
        tmpvar_19 = (tmpvar_18 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (1.0/(sTextureSize.y)));
        float tmpvar_20;
        tmpvar_20 = (tmpvar_19 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (-2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (2.0 / sTextureSize.y));
        float tmpvar_21;
        tmpvar_21 = (tmpvar_20 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (-1.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (2.0 / sTextureSize.y));
        float tmpvar_22;
        tmpvar_22 = (tmpvar_21 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (0.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (2.0 / sTextureSize.y));
        float tmpvar_23;
        tmpvar_23 = (tmpvar_22 + (texture2D (cTexSampler0, new_uv).w * 2.0));
        new_uv.x = (sUV.x + (1.0/(sTextureSize.x)));
        new_uv.y = (sUV.y + (2.0 / sTextureSize.y));
        float tmpvar_24;
        tmpvar_24 = (tmpvar_23 + texture2D (cTexSampler0, new_uv).w);
        new_uv.x = (sUV.x + (2.0 / sTextureSize.x));
        new_uv.y = (sUV.y + (2.0 / sTextureSize.y));
        vec4 tmpvar_25;
        tmpvar_25.xyz = sBlurColor.xyz;
        tmpvar_25.w = (((tmpvar_24 + texture2D (cTexSampler0, new_uv).w) * sBlurRate) / 52.0);
      </Text>
      <ReturnOp>tmpvar_25</ReturnOp>
    </Code>
	</PSMain>
</Shader>
