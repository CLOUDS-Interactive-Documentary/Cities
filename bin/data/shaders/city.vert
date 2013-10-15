#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect displacment;
uniform vec2 displacmentDim;
uniform vec4 color = vec4(1., 1. ,0., 1.);
uniform vec2 texSize = vec2(500., 500.);

uniform float maxCubeScale = 20.;
//uniform float rExpo = 2.;
//uniform float rScale = 1.5;
uniform float maxHeight = 10.;
uniform float minHeight = .1;

varying vec4 col;
varying vec3 norm;

void main()
{
	
	vec2 uv = gl_MultiTexCoord0.xy;
	//	float r = texture2DRect( randomness, uv ).r;
	vec3 displacmentSample = texture2DRect( displacment, uv * displacmentDim ).xyz;
	float disp = displacmentSample.b;//
	
	col = vec4( displacmentSample.xyz, 1.);//color * pow( r * rScale, rExpo );
	
	norm = gl_NormalMatrix * gl_Normal;
//	vec3 vPos = gl_Vertex.xyz;
//	float cubeScale = r * maxCubeScale;
//	vPos.y *= cubeScale;
	
//	//move the cubes up and down if they're hitting the top or bottom
//	float cubeTop = cubeCenter.y + cubeScale * .5;
//	float cubeBot = cubeCenter.y - cubeScale * .5;
//	if( cubeBot < minY )
//	{
//		cubeCenter.y += distance( minY, cubeBot );
//	}
//	else if( cubeTop > maxY )
//	{
//		cubeCenter.y -= distance( maxY, cubeTop );
//	}
	
	vec3 vPos = gl_Vertex.xyz;
	vPos.y *= disp * maxHeight + minHeight;
	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4( vPos, 1.);
	
}