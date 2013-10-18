#version 120
#extension GL_ARB_texture_rectangle : enable

//uniform sampler2DRect pong;
//uniform float randSeed;

uniform sampler2DRect facadeTexture;
uniform vec2 facadeTextureDim;
uniform float maxHeight;

varying vec4 col;
varying vec3 norm;
varying vec4 lPos;
varying vec3 ePos;
varying vec4 ecPosition;
varying vec2 uv;
varying vec2 facadeUV;
varying vec3 vertex;

//uniform vec3 ambientColor = vec3(.1);
//uniform vec3 diffuseColor = vec3(.9);
//uniform vec3 specularColor = vec3(1.);
uniform float shininess = 16.;
uniform float edgeAlphaScl = 1.5;
uniform float facadeTextureAmount = .125;

float toGreyScale( vec3 c ){
	return c.x * .3 + c.y*.59 + c.z * .11;
}

void main(void)
{
	
	float edgeAlpha = min(1., 1.5 - pow( edgeAlphaScl * length(abs(uv*2.-1.)), 2.) );
	if(edgeAlpha < .001)	discard;
	
	vec3 n = normalize( norm );
	vec3 diffuse, ambient, specular;
	
	vec3 VP = normalize( lPos.xyz - ecPosition.xyz );//no attenuation yet... so we don't need distance
	vec3 halfVector = normalize(VP + ePos);
	
    float nDotVP = max(0.0, dot(n, VP));
    float nDotHV = max(0.0, dot(n, halfVector));
	
	float fr = max(0.,dot( -normalize(ePos), normalize( norm ) ) );
	
	//facade texturing
	vec2 fuv = mod(facadeUV, vec2(1.));
	vec3 fcdVl = texture2DRect( facadeTexture, fuv * facadeTextureDim ).xyz;
	vec3 facadeVal = fcdVl * facadeTextureAmount + (1.- facadeTextureAmount);
	
	//lighting
    ambient = gl_LightSource[0].ambient.xyz;
    diffuse = gl_LightSource[0].diffuse.xyz * fr;//nDotVP; // temp solution for avoiding poorly positioned lights
	float specVal = pow(nDotVP, shininess * 10.);
    specular = gl_LightSource[0].specular.xyz * (specVal + (fcdVl*facadeTextureAmount));
	
//	diffuse *= facadeVal;
	
	
	//super fake AO
	diffuse *= pow(min(1., 1.01 * vertex.y ), 2.);
	
	//Lars: I added the color from the texture here... 
	diffuse *= min( pow(toGreyScale( col.xyz ) * 10., 2.), 1.) ;

	
	gl_FragColor = vec4( diffuse + ambient + specular, col.w * edgeAlpha);
	//gl_FragColor =  vec4(n*.5+.5, 1.);
//	gl_FragColor = vec4(fuv, 1. ,1.);
}

