#shader vertex

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texLight;

out vec2 v_TexCoord;
uniform mat4 m_MVP;
uniform float uTime;
out vec4 v_texLight;

void main(){
   vec4 pos = position;
   //pos.z += uTime * 100;
   gl_Position = m_MVP * pos;
   v_TexCoord = texCoord;
   v_texLight = vec4(texLight, texLight, texLight, 1.0);
};

#shader fragment

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_texLight;

uniform sampler2D uTexture;
uniform float uTime;

void main(){
   vec4 texColor = texture(uTexture, v_TexCoord);
   color = texColor * v_texLight;
};