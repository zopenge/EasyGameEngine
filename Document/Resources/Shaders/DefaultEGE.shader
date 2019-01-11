<?xml version="1.0" encoding="utf-8"?>
<Root>
  <Shader version="1.2" embedded_version="1.0">
    <Include name="DefaultGL.xml"/>
    <Technique>
      <VSResidentCode>
        <![CDATA[
        $PositionSkin();
        $NormalSkin();
        $TangentSkin();
        ]]>
      </VSResidentCode>
      <VSFinishCode>
        <![CDATA[
        $GL_POS_DONE();
        ]]>
      </VSFinishCode>

      <!-- 2D Render Methods -->

      <RenderMethod name="_OVERLAY_VERTEX_COLOR">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
          $GL_COLOR_DONE($vColor0());
          ]]>
        </PSCode>
      </RenderMethod>
	  <RenderMethod name="_OVERLAY_AIO">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
			$TEXTURE2D(cDiffuse, out:tex_color);
			
			tex_color.w *= $vColor0().w;
			#if _DISCARD_TRANSPARENT_ || _DISCARD_OPACITY_
				#if _USE_DISCARD_ALPHA_VALUE_
					float discard_alpha_value = uDiscardAlphaValue;
				#else
					float discard_alpha_value = 0.5;
				#endif
				#if _DISCARD_TRANSPARENT_
					if ( tex_color.w < discard_alpha_value )
						discard;				
				#elif _DISCARD_OPACITY_
					if ( tex_color.w >= discard_alpha_value )
						discard;
				#endif
			#endif
		  
			#if _DIFFUSE_MAP_COLOR_OPERATION_ADD_
				tex_color.xyz += $vColor0().xyz;
			#elif _DIFFUSE_MAP_COLOR_OPERATION_SUB_
				tex_color.xyz -= $vColor0().xyz;
			#elif _DIFFUSE_MAP_COLOR_OPERATION_MIX_
				${lowp}$ vec4 color_mix = vec4( $vColor0().xyz, 0.5 );
				$MixColor(tex_color, color_mix, out:tex_color);
			#elif _DIFFUSE_MAP_COLOR_OPERATION_GREY_
				$GreyColor(tex_color, out:tex_color);
			#else
				tex_color.xyz *= $vColor0().xyz;
			#endif
			
			#if _COLOR_MASK_MAP_
				if ( uOverlayMaskPosXDir.z <= 0.1 || uOverlayMaskPosYDir.z <= 0.1 || uOverlayMaskUVRange.x == 0.0 || uOverlayMaskUVRange.y == 0.0 )
				{
					tex_color.w = 0.0;
				}
				else
				{
					vec2 dirm = $vPositionWorld().xy - uOverlayMaskPosMin.xy;
					float dot_xm = dot( uOverlayMaskPosXDir.xy, dirm );
					float dot_ym = dot( uOverlayMaskPosYDir.xy, dirm );
					vec2 mask_uv_alpha;
					mask_uv_alpha.x = dot_xm / uOverlayMaskPosXDir.z;
					mask_uv_alpha.y = dot_ym / uOverlayMaskPosYDir.z;
					
					if ( mask_uv_alpha.x < 0.0 || mask_uv_alpha.x > 1.0 || mask_uv_alpha.y < 0.0 || mask_uv_alpha.y > 1.0 )
					{
						tex_color.w = 0.0;
					}
					else
					{
						vec2 mask_uv;
						#if _COLOR_MASK_MAP_ROTATE_
						mask_uv.x = uOverlayMaskUVMin.x - (uOverlayMaskUVRange.x * mask_uv_alpha.x);
						#else
						mask_uv.x = uOverlayMaskUVMin.x + (uOverlayMaskUVRange.x * mask_uv_alpha.x);
						#endif
						mask_uv.y = uOverlayMaskUVMin.y + (uOverlayMaskUVRange.y * mask_uv_alpha.y);

						$TEXTURE2D_VEC2( cColorMaskMap, mask_uv, out:mask_tex_color );
						tex_color.w *= mask_tex_color.w;
					}
				}
			#endif
		  
			$GL_COLOR_DONE(tex_color);
          ]]>
        </PSCode>
      </RenderMethod>
      <RenderMethod name="_OVERLAY_TEX0">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  #if _WITH_USER_COLOR_
          $GL_COLOR_DONE(tex_color * $vVertexColor0());
		  #else
		  $GL_COLOR_DONE(tex_color * $vColor0());
		  #endif
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_TEX0_DISCARD_TRANSPARENT">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
          if ( tex_color.w < 0.25 )
            discard;
			
		  #if _WITH_USER_COLOR_
          $GL_COLOR_DONE(tex_color * $vVertexColor0());
		  #else
		  $GL_COLOR_DONE(tex_color * $vColor0());
		  #endif
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_TEX0_MIX_COLOR">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  ${lowp}$ vec4 color_mix = vec4( $vColor0().xyz, 0.5 );
		  $MixColor(tex_color, color_mix, out:tex_color);

		  $GL_COLOR_DONE(tex_color * $vColor0().w);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_TEX0_ADD_COLOR">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  tex_color.xyz += $vColor0().xyz;
		  
		  $GL_COLOR_DONE(tex_color * $vColor0().w);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_TEX0_SUB_COLOR">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  tex_color.xyz -= $vColor0().xyz;
		  
		  $GL_COLOR_DONE(tex_color * $vColor0().w);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_TEX0_MIX_COLOR2">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  ${lowp}$ vec4 color_mix = vec4( $vColor0().xyz, 0.5 );
		  $MixColor(tex_color, color_mix, out:tex_color);

          $GL_COLOR_DONE(tex_color * $vVertexColor() * $vColor0().w);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_TEX0_ADD_COLOR2">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  tex_color.xyz += $vColor0().xyz;
		  
          $GL_COLOR_DONE(tex_color * $vVertexColor() * $vColor0().w);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_TEX0_SUB_COLOR2">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  tex_color.xyz -= $vColor0().xyz;
		  
          $GL_COLOR_DONE(tex_color * $vVertexColor() * $vColor0().w);
          ]]>
        </PSCode>
      </RenderMethod>
			  
	 <RenderMethod name="_OVERLAY_TEX0_GREY">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  #if _WITH_USER_COLOR_
          tex_color *= $vVertexColor0();
		  #else
		  tex_color *= $vColor0();
		  #endif
		  
		  $GreyColor(tex_color, out:tex_color);
		  $GL_COLOR_DONE(tex_color);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_DRAW_TEXT">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
          ${lowp}$ vec4 color = vec4($vColor0().xyz, $vColor0().w * $GET_TEXTURE2D_W(cDiffuse));
          $GL_COLOR_DONE(color);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_OVERLAY_POST_EFFECT_GAUSSIAN_BLUR">
        <VSResidentCode>;</VSResidentCode>
        <VSFinishCode>$GL_OVERLAY_POS_DONE()</VSFinishCode>
        <PSCode>
          <![CDATA[
			${lowp}$ vec4 result_color = vec4( 0.0 );
			
			result_color += texture2D(cDiffuse, $vGaussianBlurCoordinate11());
			result_color += texture2D(cDiffuse, $vGaussianBlurCoordinate00());
			result_color += texture2D(cDiffuse, $vGaussianBlurCoordinate02());
			result_color += texture2D(cDiffuse, $vGaussianBlurCoordinate20());
			result_color += texture2D(cDiffuse, $vGaussianBlurCoordinate22());
			result_color *= 0.2;
			
			$GL_COLOR_DONE(result_color);
          ]]>
        </PSCode>
      </RenderMethod>

      <!-- 3D Render Methods -->

      <RenderMethod name="_PRIMITIVE_VERTEX_COLOR">
        <PSCode>
          <![CDATA[
          $GL_COLOR_DONE($vColor0());
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_PRIMITIVE_TEX0">
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  
		  #if _WITH_USER_COLOR_
          $GL_COLOR_DONE(tex_color * $vVertexColor0());
		  #else
		  $GL_COLOR_DONE(tex_color * $vColor0());
		  #endif
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_PRIMITIVE_TEX0_DISCARD_TRANSPARENT">
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
          if ( tex_color.w < 0.25 )
            discard;
			
		  #if _WITH_USER_COLOR_
          $GL_COLOR_DONE(tex_color * $vVertexColor0());
		  #else
		  $GL_COLOR_DONE(tex_color * $vColor0());
		  #endif
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_PRIMITIVE_TEX0_STROKE">
        <VSResidentCode>;</VSResidentCode>
        <RenderStats>
          <Rasterizer CullMode="CCW"></Rasterizer>
        </RenderStats>
        <Macros>
          <Macro name="vPositionScale" varying="true" type="vec4" default="cPosition + vec4( cNormal.xyz * uStrokeSize, 0.0 )"/>
        </Macros>
        <PSCode>
          <![CDATA[
          $GL_COLOR_DONE(uStrokeColor);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_PRIMITIVE_ZBUFFER" inherit="_PRIMITIVE_VERTEX_COLOR">
        <RenderStats>
          <Blend Enable="true" ColorSourceBlendFactor="Zero" ColorDestBlendFactor="One" AlphaSourceBlendFactor="Zero" AlphaDestBlendFactor="One" AlphaTest="Always" AlphaRef="0.0" />
        </RenderStats>
      </RenderMethod>

      <RenderMethod name="_PRIMITIVE_SKYBOX">
        <VSResidentCode>;</VSResidentCode>
        <PSCode>
          <![CDATA[
		  $TEXTURE2D(cDiffuse, out:tex_color);
		  $TEXTURECUBE(-$vPosToEyeDir(), out:cube_tex_color);
		  tex_color.xyz *= cube_tex_color.xyz;
      ${lowp}$ vec4 color = tex_color * $vVertexColor0();
      $GL_COLOR_DONE(color);
          ]]>
        </PSCode>
      </RenderMethod>

      <RenderMethod name="_PRIMITIVE_AIO">
        <PSCode>
          <![CDATA[
			vec2 diffuse_uv = $vUV0();
			#if _UV_OFFSET_X_
				diffuse_uv.x += uUVOffsetX;
			#endif
			#if _UV_OFFSET_Y_
				diffuse_uv.y += uUVOffsetY;
			#endif
			$TEXTURE2D_VEC2(cDiffuse, diffuse_uv, out:tex_color);
			
			#if _DISCARD_TRANSPARENT_ || _DISCARD_OPACITY_
				#if _USE_DISCARD_ALPHA_VALUE_
					float discard_alpha_value = uDiscardAlphaValue;
				#else
					float discard_alpha_value = 0.5;
				#endif
				#if _DISCARD_TRANSPARENT_
					if ( tex_color.w < discard_alpha_value )
						discard;				
				#elif _DISCARD_OPACITY_
					if ( tex_color.w >= discard_alpha_value )
						discard;
				#endif
			#endif
			
			$TEXTURE2D(cColorMaskMap, out:color_mask_map);
			vec3 diffusemap_color3 = uDiffuseMapColor.xyz;
			vec4 diffusemap_color4 = vec4(diffusemap_color3, 0.5);
			#if _DIFFUSE_MAP_COLOR_OPERATION_ADD_
				#if _COLOR_MASK_MAP_
					diffusemap_color3.xyz *= color_mask_map.x;
				#endif
				tex_color.xyz += diffusemap_color3.xyz;
			#elif _DIFFUSE_MAP_COLOR_OPERATION_SUB_
				#if _COLOR_MASK_MAP_
					diffusemap_color3.xyz *= color_mask_map.x;
				#endif
				tex_color.xyz -= diffusemap_color3.xyz;
			#elif _DIFFUSE_MAP_COLOR_OPERATION_MUL_
				#if _COLOR_MASK_MAP_
					diffusemap_color3.xyz *= color_mask_map.x;
					diffusemap_color3.x = min( diffusemap_color3.x + 1.0 - color_mask_map.x, 1.0 );
					diffusemap_color3.y = min( diffusemap_color3.y + 1.0 - color_mask_map.x, 1.0 );
					diffusemap_color3.z = min( diffusemap_color3.z + 1.0 - color_mask_map.x, 1.0 );
				#endif
				tex_color.xyz *= diffusemap_color3.xyz;
			#elif _DIFFUSE_MAP_COLOR_OPERATION_MIX_
				#if _COLOR_MASK_MAP_
					diffusemap_color4.w *= color_mask_map.x;
				#endif
				$MixColor(tex_color, diffusemap_color4, out:tex_color);
			#elif _DIFFUSE_MAP_COLOR_OPERATION_GREY_
				#if _COLOR_MASK_MAP_
					if ( color_mask_map.x != 0.0 )
						$GreyColor(tex_color, out:tex_color);
				#else
					$GreyColor(tex_color, out:tex_color);
				#endif
			#endif
			
			#if _LIGHT_MAP_
				$TEXTURE2D_UV(cBakeLightMap, 1, out:light_map_color);
				tex_color.xyz *= light_map_color.xyz * ( uLightMapRange.y - uLightMapRange.x ) + vec3( uLightMapRange.x );
			#endif
			
			#if _NORMAL_MAP_
				$TEXTURE2D(cNormalMap, out:normal_map_color);
				vec3 normal = normal_map_color.xyz;
				normal = normalize( normal * 2.0 - vec3( 1.0, 1.0, 1.0 ) );
				normal = normalize( normal * $vMatTBNInvert() );
				vec3 tangent = normalize( cross( vec3(0,1,0), normal ) );
				vec3 bitangent = normalize( cross( normal, tangent ) );
				
				vec3 world_normal = normal;
				vec3 viewdir = normalize( $vPosToEyeDir() );
				vec3 reflect_eyedir = normalize( reflect( -viewdir, normal ) );
				
				//vec3 world_normal = normalize( normal * $vMatTBNInvert() );
				//vec3 viewdir = normalize( $vPosToEyeDirTBN() );
				//vec3 reflect_eyedir = normalize( reflect( -$vPosToEyeDir(), world_normal ) );
			#else
				vec3 normal = normalize( $vNormalWorld() );
				vec3 tangent = normalize( $vTangent() );
				vec3 bitangent = normalize( $vBiTangent() );
				vec3 world_normal = normal;
				vec3 viewdir = normalize( $vPosToEyeDir() );
				vec3 reflect_eyedir = normalize( reflect( -viewdir, normal ) );
			#endif
			
			float DotNV = clamp( dot( normal, viewdir ), 0.0, 1.0 );
			
			#if _MATERIAL_MAP_
				$TEXTURE2D(cMaterialMap, out:material);
			#else
				vec4 material = vec4( uMetallic, uRoughness, 0.0, 1.0 );
			#endif
			
			#if _GAMMA_
				vec3 linear_space_color = pow( tex_color.xyz, vec3(2.2) );
			#else
				vec3 linear_space_color = tex_color.xyz;
			#endif
			
			#if _LIGHT_0 || _LIGHT_1 || _LIGHT_2 || _LIGHT_3 || _CUBE_MAP_ || _SPHERE_MAP_
				vec3 old_tex_color = tex_color.xyz;
				vec3 diffuse_color = (1.0 - material.x) * linear_space_color.xyz;
				vec3 specular_color = mix( vec3( 0.04 ), linear_space_color.xyz, material.x );
				
				$Fresnel_OPT( DotNV, Fresnel_DotNV );
				$EnvBRDFApproxFromTex( specular_color, material.y, DotNV, EnvBRDF );
				
				#if !_ONLY_PROJTEX_SPOT_LIGHT_ || _CUBE_MAP_ || _SPHERE_MAP_
					tex_color.xyz = vec3( 0.0 );
				#endif
			#endif
			
			#if _LIGHT_0 || _LIGHT_1 || _LIGHT_2 || _LIGHT_3
				vec3 light_result_color = vec3( 0.0 );
				
				$CalculateLightInfo( 0, normal, tangent, bitangent, viewdir, reflect_eyedir, lightdir, halfvector, DotNL, DotNH, DotXH, DotYH, DotLH, DotRL, DotNLNC );
				$CalculateLightInfo( 1, normal, tangent, bitangent, viewdir, reflect_eyedir, lightdir, halfvector, DotNL, DotNH, DotXH, DotYH, DotLH, DotRL, DotNLNC );
				$CalculateLightInfo( 2, normal, tangent, bitangent, viewdir, reflect_eyedir, lightdir, halfvector, DotNL, DotNH, DotXH, DotYH, DotLH, DotRL, DotNLNC );
				$CalculateLightInfo( 3, normal, tangent, bitangent, viewdir, reflect_eyedir, lightdir, halfvector, DotNL, DotNH, DotXH, DotYH, DotLH, DotRL, DotNLNC );
				
				#if _SPECULAR_MAP_
					$TEXTURE2D(cSpecularMap, out:specular_map_color);
					vec3 spec_refl_color = specular_map_color.xyz;
				#else
					vec3 spec_refl_color = vec3( 0.5 );
				#endif
				
				$CalculateBRDFApprox( 0, DotNV, DotRL, DotNL, DotLH, DotNH, DotXH, DotYH, DotNLNC, uAsnisoAspect, material.y, EnvBRDF, diffuse_color, linear_space_color, Fresnel_DotNV, tex_color );
				$CalculateBRDFApprox( 1, DotNV, DotRL, DotNL, DotLH, DotNH, DotXH, DotYH, DotNLNC, uAsnisoAspect, material.y, EnvBRDF, diffuse_color, linear_space_color, Fresnel_DotNV, tex_color );
				$CalculateBRDFApprox( 2, DotNV, DotRL, DotNL, DotLH, DotNH, DotXH, DotYH, DotNLNC, uAsnisoAspect, material.y, EnvBRDF, diffuse_color, linear_space_color, Fresnel_DotNV, tex_color );
				$CalculateBRDFApprox( 3, DotNV, DotRL, DotNL, DotLH, DotNH, DotXH, DotYH, DotNLNC, uAsnisoAspect, material.y, EnvBRDF, diffuse_color, linear_space_color, Fresnel_DotNV, tex_color );
				
				$CalculateProjTextureColor( 0, projtex_color );
				$CalculateProjTextureColor( 1, projtex_color );
				$CalculateProjTextureColor( 2, projtex_color );
				$CalculateProjTextureColor( 3, projtex_color );
				
				$AddProjTextureColor( 0, projtex_color, old_tex_color, tex_color );
				$AddProjTextureColor( 1, projtex_color, old_tex_color, tex_color );
				$AddProjTextureColor( 2, projtex_color, old_tex_color, tex_color );
				$AddProjTextureColor( 3, projtex_color, old_tex_color, tex_color );
			#endif
			
			// cubemap
			#if (_CUBE_MAP_ || _SPHERE_MAP_) ^^ _ENVIRONMENT_
				#if _SPHERE_MAP_
					vec2 sphere_env_map_uv = vec2( 0.5, 0.5 ) + ( reflect_eyedir.xy * 0.5 / ( reflect_eyedir.z + 1.01 ) );
					$TEXTURE2D_VEC2(cSphereEnvMap, sphere_env_map_uv, out:env_refl_color);
				#else
					vec4 env_refl_color = textureCube(cTexCubeEnv, reflect_eyedir, 7.0 * material.y);
				#endif
				#if _ENVIRONMENT_FACTOR_
					env_refl_color.xyz *= uEnvironmentFactor;
				#endif
				#if _GAMMA_
					vec3 linear_space_env_refl_color = pow( env_refl_color.xyz, vec3(2.2) );
				#endif
				
				tex_color.xyz += env_refl_color.xyz * EnvBRDF.xyz;
			#endif
				
			#if _MIRROR_ATTENUATION_ || _REFLECTED_BY_MIRROR_
				tex_color.w *= $vMirrorAttenuation();
			#endif
			
			#if _MIRROR_
				vec2 mirror_uv = ( $vPositionGL().xy / $vPositionGL().z ) * 0.5 + vec2( 0.5, 0.5 );
				$TEXTURE2D_VEC2(cMirrorMap, mirror_uv, out:mirror_color);
				
				#if _MIRROR_FRESNEL_
					float mirror_DotNV = dot( uMirrorPlane.xyz, viewdir );
					float mirror_fresnel_factor = ( 1.0 - mirror_DotNV ) / ( uMirrorFresnelPower - ( uMirrorFresnelPower - 1.0 ) * ( 1.0 - mirror_DotNV ) );
					mirror_color.xyz *= max( 0.0, mirror_fresnel_factor );
				#endif
				
				#if _MIRROR_OPERATION_ADD_
					tex_color.xyz += mirror_color.xyz * $vMirrorFactor();
				#elif _MIRROR_OPERATION_SUB_
					tex_color.xyz -= mirror_color.xyz * $vMirrorFactor();
				#elif _MIRROR_OPERATION_MIX_
					vec4 mirror_color_mix = vec4( mirror_color.xyz, $vMirrorFactor() );
					$MixColor(tex_color, mirror_color_mix, out:tex_color);
				#elif _MIRROR_OPERATION_MUL_
					mirror_color.xyz = mirror_color.xyz * mirror_color.w + vec3( 1.0 - mirror_color.w );
					tex_color.xyz *= mirror_color.xyz * $vMirrorFactor();
				#elif _MIRROR_OPERATION_RANGE_
					mirror_color.xyz = mirror_color.xyz * mirror_color.w + vec3( 1.0 - mirror_color.w );
					tex_color.xyz *= mirror_color.xyz * ( 1.0 + ( $vMirrorRange().y - $vMirrorRange().x - 1.0 ) * mirror_color.w ) + vec3( $vMirrorRange().x * mirror_color.w );
				#endif
			#endif
			
			#if _AMBIENT_FACTOR_
				#if _AMBIENT_RANGE_
					float ambient_value = ( tex_color.x + tex_color.y + tex_color.z ) / 3.0;
					float ambient_rate = 1.0 - clamp( ( ambient_value - uAmbientRange.x ) / ( uAmbientRange.y - uAmbientRange.x ), 0.0, 1.0 );
					tex_color.xyz += linear_space_color.xyz * ( ambient_rate * uAmbientFactor );
				#else
					tex_color.xyz += linear_space_color.xyz * uAmbientFactor;
				#endif
			#endif
			
			#if _FOG_
				${lowp}$ vec4 fog_color = mix(vec4(tex_color.xyz, 1.0), uFogColor, $vFogFactor());
				tex_color.xyz = fog_color.xyz;
				tex_color.w *= fog_color.w;
			#endif
			
			#if _GLASS_
				tex_color.w *= mix(uGlassFactor, 1.0, clamp(0.3 * tex_color.z + 0.6 * tex_color.y + 0.1 * tex_color.x, 0.0, 1.0 ));
			#endif
			
			#if _GAMMA_
				tex_color.xyz = pow( tex_color.xyz, vec3(0.45454545) );
			#endif
			
			tex_color *= uVertexColor;
			
			$GL_COLOR_DONE(tex_color);
          ]]>
        </PSCode>
      </RenderMethod>
    </Technique>
  </Shader>
</Root>