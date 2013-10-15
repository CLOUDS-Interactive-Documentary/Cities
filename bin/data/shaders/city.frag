#version 120
#extension GL_ARB_texture_rectangle : enable

//uniform sampler2DRect pong;
//uniform float randSeed;

varying vec4 col;
varying vec3 norm;
varying vec2 uv;

void main(void)
{
//	float r = rand( uv + vec2( 0., randSeed ) ) * .002;
//	r += texture2DRect( pong, uv ).r;
//	if(r > 1.) r = 0.;
	vec3 n = normalize( norm );// * .5 + .5;
	gl_FragColor = col;
}

