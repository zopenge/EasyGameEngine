#ifdef _USE_REFLECT_BY_SPHERE_MIRROR_

	#ifdef _VS_
		vec4 GetSphereMirrorPos(vec4 pos)
		{
			vec4 pos_view = pos / length( pos.xyz );
			pos_view.xyz = pos_view.xyz / ( pos_view.z - 1.0 );

			return vec4( -pos_view.x, pos_view.y, pos_view.z, 1.0 );
		}

		#define _VS_GET_POS_BY_SPHERE_MIRROR(pos) GetSphereMirrorPos(pos)
	#endif

#else

	#ifdef _VS_
		#define _VS_GET_POS_BY_SPHERE_MIRROR(pos) pos
	#endif
	
#endif // _USE_REFLECT_BY_SPHERE_MIRROR_