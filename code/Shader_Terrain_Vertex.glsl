#version 330

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;

layout (location = 0) in vec2 vertex_xz;
layout (location = 4) in vec2 vertex_uv;

uniform sampler2D texture0;
uniform float     max_height;

out float intensity;

void main()
{
   float sample = texture (texture0, vertex_uv).r;
   intensity    = clamp(sample * 0.75 + 0.25, 0.0, 1.0);
   float height = sample * max_height;
   vec4  xyzw   = vec4(vertex_xz.x, vertex_xz.y, height, 1.0);
   gl_Position  = projection_matrix * model_view_matrix * xyzw;
}
