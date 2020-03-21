#shader vertex

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec4 position;
layout(location = 2) in float texLight;

out vec3 v_TexCoord;
uniform mat4 m_MVP;

void main(){
   gl_Position = m_MVP * position;
   v_TexCoord = vec3(position.x * -1, position.y, position.z);
};

#shader fragment

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

uniform samplerCube uTexture;
uniform float uTime;

vec4 applySunrise(vec3 value, vec4 nightColor){
   vec4 middleColor = vec4(1.0, 0.1, 0.1, 1.0);
   float minY = 0.4;
   float maxY = 0.6;
   float y = (normalize(value).y + 1) / 2;
   y = (y - minY)/(maxY - minY);
   if(y > 1.0){
      y = 1.0;
   }
   if(y < 0.0){
      y = 0.0;
   }
   vec4 colorResult = middleColor * (1.0 - y) + nightColor * y;
   return colorResult;
}

vec4 applyLight(vec3 value, float time){
   vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
   vec4 darkColor = vec4(0.2, 0.2, 0.2, 1.0);
   vec4 sunriseColor = applySunrise(value, darkColor);
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
   texColor = texColor * applyLight(v_TexCoord, uTime);
   color = texColor;
};