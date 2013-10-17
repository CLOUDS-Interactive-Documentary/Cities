#version 120
#extension GL_ARB_texture_rectangle : enable

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform sampler2DRect displacment;
uniform sampler2DRect overlayMap;
uniform vec2 overlayDim;
uniform int bUseOverlay = 0;

uniform vec2 displacmentDim;
uniform vec2 texSize = vec2(500., 500.);

uniform float maxCubeScale = 20.;
uniform float blocksMinDist = .5;
uniform float blockSize = 2.;
uniform float blocksMinSize = 1.;

uniform float blocksAlpha = 1.;

uniform float maxHeight = 10.;
uniform float minHeight = 1.;

varying vec4 col;
varying vec3 norm;
varying vec3 ePos;
varying vec4 lPos;
varying vec4 ecPosition;

void main()
{
	
	vec2 uv = gl_MultiTexCoord0.xy;
	
	//	float r = texture2DRect( randomness, uv ).r;
	vec3 displacmentSample = texture2DRect( displacment, uv * displacmentDim ).xyz;
	float disp = displacmentSample.y;
	
	if(bUseOverlay == 1)
	{
		disp *= texture2DRect( overlayMap, uv * overlayDim ).x;
	}
	
	col = vec4( displacmentSample, max( blocksAlpha, disp * .78 + .22));//<-- aplha taken from the original render algorthim
	norm = gl_NormalMatrix * gl_Normal;
	
	//emulating particio's scaling algorithm in the x & z axis
	vec3 vPos = gl_Vertex.xyz;
	vec2 cubeCenter = ( uv - displacmentDim/2.) * .5;
	vec2 localPos = vPos.xz - cubeCenter;
	localPos *= (1.0-blocksMinDist) - disp * blocksMinSize;//scale it 
	
	//reposition our vertex
	vPos.xz = localPos + cubeCenter;//back to world space
	vPos.y *= disp * maxHeight + minHeight;
	
	lPos = gl_ModelViewMatrix * gl_LightSource[0].position;
	ecPosition = gl_ModelViewMatrix * vec4(vPos, 1.);
	
	ePos = normalize(ecPosition.xyz/ecPosition.w);
	gl_Position = gl_ProjectionMatrix * ecPosition;
}