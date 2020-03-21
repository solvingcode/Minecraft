#shader vertex

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec4 position;

out vec2 v_Uv;
uniform mat4 m_MVP;

void main(){
   gl_Position = m_MVP * position;
   v_Uv = (normalize(vec2(position.x, position.y)) + 1.0) / 2.0;
};

#shader fragment

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) out vec4 color;

in vec2 v_Uv;
uniform float uTime;

vec4 getLight(float time){
   vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
   vec4 darkColor = vec4(0.05, 0.05, 0.05, 1.0);
   return lightColor * (1 - time) + darkColor * time;
}

void main(){
   vec4 colorTop = vec4(0.2, 0.67, 1.0, 1.0);
   vec4 colorBottom = vec4(0.65, 0.85, 1.0, 1.0);
   float y = v_Uv.y;
   float minY = 0.5;
   float maxY = 0.6;
   y = (y - minY)/(maxY - minY);
   if(y > 1.0){
      y = 1.0;
   }
   if(y < 0.0){
      y = 0.0;
   }
   vec4 colorResult = colorBottom * (1.0 - y) + colorTop * y;
   color = colorResult * getLight(uTime);
};