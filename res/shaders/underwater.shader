#shader vertex

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) in vec4 position;

out vec2 v_Uv;

void main(){
   gl_Position = position;
   v_Uv = (vec2(position.x, position.y) + 1.0) / 2.0;
};

#shader fragment

#version 130
#extension GL_ARB_explicit_attrib_location : require
#extension GL_ARB_explicit_uniform_location : require

layout(location = 0) out vec4 color;

in vec2 v_Uv;

void main(){
   vec4 colorTop = vec4(0.3, 0.3, 0.7, 0.8);
   vec4 colorBottom = vec4(0.7, 0.7, 1.0, 0.3);
   float y = v_Uv.y;
   float minY = 0.0;
   float maxY = 1.0;
   y = (y - minY)/(maxY - minY);
   if(y > 1.0){
      y = 1.0;
   }
   if(y < 0.0){
      y = 0.0;
   }
   vec4 colorResult = colorBottom * (1.0 - y) + colorTop * y;
   color = colorResult;
};