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
uniform float blockResolution = 43.;
uniform float blocksMinSize = 1.;

uniform float blocksAlpha = 1.;

uniform float maxHeight = 10.;
uniform float minHeight = .1;

varying vec4 col;
varying vec3 norm;
varying vec3 vertex;
varying vec3 ePos;
varying vec4 lPos;
varying vec4 ecPosition;
varying vec2 uv;
varying vec2 facadeUV;

void main()
{
	uv = gl_MultiTexCoord0.xy;
	vertex = gl_Vertex.xyz;
	
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
	vec2 cubeCenter = uv * vec2(blockResolution) - vec2(blockResolution)*.5;//( uv - displacmentDim/2.) * .5;
	vec2 localPos = vPos.xz - cubeCenter;
	
//	localPos *= blocksMinSize;
	
	localPos *= (1.0-blocksMinDist) - disp * blocksMinSize;//scale it
//	localPos *= max( .55, disp * blocksMinSize);//scale it
		
	//reposition our vertex
	vPos.xz = localPos + cubeCenter;//back to world space
	
	float vScl = 2.;
	if(vPos.y > .1){
		vPos.y += disp * maxHeight - .9 * vScl;
	}
	else{
		vPos.y = 0.;
	}
	
//	lPos = gl_ModelViewMatrix * vec4( -100.,10000., 0., 1.);//( vec4( 0.,0.,., 1.) );//gl_LightSource[0].position * vec4(vec3(10.),1.));
	lPos = vec4( gl_LightSource[0].position.xyz * 100., 1.);
	ecPosition = gl_ModelViewMatrix * vec4(vPos, 1.);
	
	ePos = normalize(ecPosition.xyz/ecPosition.w);
	gl_Position = gl_ProjectionMatrix * ecPosition;
	
	float facadeUVScl = .4;
	facadeUV.x = gl_Color.x * facadeUVScl + uv.x;
	facadeUV.y = gl_Color.y * facadeUVScl + uv.y;

	if(abs(gl_Normal.y) < .75 ){
		facadeUV.y = (1.-gl_Color.y) * disp * maxHeight - .9 * vScl;
		facadeUV.y *= facadeUVScl;
	}
}