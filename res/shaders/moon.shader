#shader vertex

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 m_MVP;
uniform float uTime;

mat4 rotationX(float time){
    float angle = ((time * 360.0 + 180.0) * 3.14159265 / 180.0) * -1;
    return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

void main(){
    gl_Position = m_MVP * rotationX(uTime) * position;
    v_TexCoord = texCoord;
};

#shader fragment

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D uTexture;
uniform float uTime;

void main(){
   vec4 texColor = texture(uTexture, v_TexCoord);
   color = texColor * vec4(0.5, 0.5, 0.8, 1.0);
};