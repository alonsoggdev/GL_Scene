#version 330

uniform sampler2D texture0;

in  vec2 texture_uv;
out vec4 fragment_color;

void main()
{
    fragment_color = vec4(texture (texture0, texture_uv.st).rgb, 1.0);
}
