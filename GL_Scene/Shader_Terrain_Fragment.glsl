#version 330

in  float intensity;
out vec4  fragment_color;

void main()
{
    fragment_color = vec4(intensity, intensity, intensity, 1.0);
}
