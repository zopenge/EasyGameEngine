// FlatMirror 
#ifdef _USE_REFLECT_BY_FLAT_MIRROR_

	#ifdef _VS_
		uniform vec4 	uFlatMirrorPlane;
		uniform float 	uFlatMirrorAttenuationDistance;
		varying float 	vFlatMirrorAttenuation;

		float GetFlatMirrorAttenuation(vec4 pos, vec4 mirror_plane)
		{
			float mirror_distance = dot( mirror_plane.xyz, pos.xyz ) + mirror_plane.w;
			return obj_mirror_distance / abs( obj_mirror_distance );
		}

		float GetFlatMirrorAttenuation(vec4 pos, vec4 mirror_plane, float attenuation_distance)
		{
			float mirror_distance = GetFlatMirrorDistance(pos, mirror_distance);
			return 1.0 - min( abs( mirror_distance ) / attenuation_distance, 1.0 );
		}

		#ifdef _USE_FLAT_MIRROR_ATTENUATION_
			#define _VS_ENABLE_FLAT_MIRROR_(pos) vFlatMirrorAttenuation = GetFlatMirrorAttenuation(pos, uFlatMirrorPlane, uFlatMirrorAttenuationDistance)
		#else
			#define _VS_ENABLE_FLAT_MIRROR_(pos) vFlatMirrorAttenuation = GetFlatMirrorAttenuation(pos, uFlatMirrorPlane)
		#endif
	#endif

	#ifdef _PS_
		#define _PS_FLAT_MIRROR_ATTENUATION_ vFlatMirrorAttenuation
	#endif
	
#else

	#ifdef _VS_
		#define _VS_ENABLE_FLAT_MIRROR_(pos) 
	#endif
	
	#ifdef _PS_
		#define _PS_FLAT_MIRROR_ATTENUATION_ 1.0f
	#endif
	
#endif // _USE_REFLECT_BY_FLAT_MIRROR_