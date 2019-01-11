#ifdef _PS_

vec4 Texture2D(sampler2D tex, vec2 uv)
{
	vec4 tex_color = texture2D(tex, uv);
	return tex_color;
}

vec4 Texture2D(sampler2D tex, vec2 uv, vec4 color)
{
	return Texture2D(tex, uv) * color;
}

#endif