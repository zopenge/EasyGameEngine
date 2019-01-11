// SpriteMask 
#ifdef _USE_SPRITE_MASK_

	#ifdef _PS_
		uniform sampler2D uSpriteMaskTex;

		uniform vec2 uSpriteMaskPosMin;
		uniform vec3 uSpriteMaskPosXDir;
		uniform vec3 uSpriteMaskPosYDir;
		uniform vec2 uSpriteMaskUVMin;
		uniform vec2 uSpriteMaskUVRange;

		float GetSpriteMaskAlpha(vec4 pos, vec4 mask_pos_x_dir, vec4 mask_pos_y_dir, vec2 mask_uv_min, vec2 mask_uv_range, vec2 mask_pos_min, sampler2D mask_tex)
		{
			if ( mask_pos_x_dir.z <= 0.1 || mask_pos_y_dir.z <= 0.1 || mask_uv_range.x == 0.0 || mask_uv_range.y == 0.0 )
				return 0.0;

			vec2 dirm = pos.xy - mask_pos_min.xy;
			float dot_xm = dot( mask_pos_x_dir.xy, dirm );
			float dot_ym = dot( mask_pos_y_dir.xy, dirm );
			vec2 mask_uv_alpha;
			mask_uv_alpha.x = dot_xm / mask_pos_x_dir.z;
			mask_uv_alpha.y = dot_ym / mask_pos_y_dir.z;
			
			if ( mask_uv_alpha.x < 0.0 || mask_uv_alpha.x > 1.0 || mask_uv_alpha.y < 0.0 || mask_uv_alpha.y > 1.0 )
				return 0.0;

			vec2 mask_uv;
			#if _USE_SPRITE_MASK_WITH_ROTATION_
			mask_uv.x = mask_uv_min.x - (mask_uv_range.x * mask_uv_alpha.x);
			#else
			mask_uv.x = mask_uv_min.x + (mask_uv_range.x * mask_uv_alpha.x);
			#endif
			mask_uv.y = mask_uv_min.y + (mask_uv_range.y * mask_uv_alpha.y);

			vec4 mask_tex_color = Texture2D(mask_tex, mask_uv);
			return mask_tex_color.w;
		}
				
		#define _PS_SPRITE_MASK_ALPHA GetSpriteMaskAlpha(uSpriteMaskPosXDir, uSpriteMaskPosYDir, uSpriteMaskUVMin, uSpriteMaskUVRange, uSpriteMaskPosMin, uSpriteMaskTex)
	#endif
	
#else

	#ifdef _PS_
		#define _PS_SPRITE_MASK_ALPHA 1.0f
	#endif
	
#endif // _USE_SPRITE_MASK_