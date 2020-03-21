#shader vertex

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texLight;

out vec2 v_TexCoord;
out vec4 v_texLight;
out vec4 v_Position;
uniform mat4 m_MVP;
uniform mat4 m_M;

void main(){
   gl_Position = m_MVP * position;
   v_Position = m_M * position;
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
in vec4 v_Position;

uniform sampler2D uTexture;
uniform float uTime;

vec4 getLight(float time){
   vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
   vec4 darkColor = vec4(0.2, 0.2, 0.2, 1.0);
   vec4 sunriseColor = vec4(1.0, 0.8, 0.8, 1.0);
   vec4 startColor;
   vec4 endColor;
   vec4 lightResult;

   if(time <= 0.25){
      float bias = time * 4;
      lightResult = sunriseColor * (1.0 - bias) + lightColor * bias;
   }else if(time <= 0.35){
      lightResult = lightColor;
   }else if(time <= 0.5){
      float bias = (time - 0.35)/(0.5 - 0.35);
      lightResult = lightColor * (1.0 - bias) + sunriseColor * bias;
   }else if(time <= 0.6){
      float bias = (time - 0.5)/(0.6 - 0.5);
      lightResult = sunriseColor * (1.0 - bias) + darkColor * bias;
   }else if(time <= 0.75){
      lightResult = darkColor;
   }else{
      float bias = (time - 0.75)/(1.0 - 0.75);
      lightResult = darkColor * (1.0 - bias) + sunriseColor * bias;
   }

   return lightResult;
}

void main(){
   vec4 texColor = texture(uTexture, v_TexCoord);
   color = texColor * getLight(uTime) * v_texLight;
   if (color.a != 1) discard;
};