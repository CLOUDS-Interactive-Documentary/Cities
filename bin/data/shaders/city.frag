#version 120
#extension GL_ARB_texture_rectangle : enable

//uniform sampler2DRect pong;
//uniform float randSeed;

uniform sampler2DRect facadeTexture;

varying vec4 col;
varying vec3 norm;
varying vec4 lPos;
varying vec3 ePos;
varying vec4 ecPosition;
varying vec2 uv;

//uniform vec3 ambientColor = vec3(.1);
//uniform vec3 diffuseColor = vec3(.9);
//uniform vec3 specularColor = vec3(1.);
uniform float shininess = 64.;
uniform float edgeAlphaScl = 1.5;


void main(void)
{
	vec3 n = normalize( norm );
	vec3 diffuse, ambient, specular;
	
	vec3 VP = normalize( lPos.xyz - ecPosition.xyz );//no attenuation yet... so we don't need distance
	vec3 halfVector = normalize(VP + ePos);
	
    float nDotVP = abs( dot(n, VP));	//	max(0.0, dot(n, VP));
    float nDotHV = abs( dot(n, halfVector));	//	max(0.0, dot(n, halfVector));
	
	float fr = abs(dot( -normalize(ePos), normalize( norm ) ) );
	
	//lighting
    ambient = gl_LightSource[0].ambient.xyz;
    diffuse = gl_LightSource[0].diffuse.xyz * nDotVP;
//	diffuse *= texture2DRect( facadeTexture, uv );
    specular = gl_LightSource[0].specular.xyz * pow(nDotHV, shininess);;
	
	//Lars: I added the color from the texture here... 
	diffuse *= col.xyz;

	float edgeAlpha = min(1., 1. - pow( edgeAlphaScl * length(abs(uv*2.-1.)), 2.) );
	if(edgeAlpha < .001)	discard;
	gl_FragColor = vec4( diffuse + ambient + specular, col.w * edgeAlpha);
	//gl_FragColor =  vec4(n*.5+.5, 1.);
}

