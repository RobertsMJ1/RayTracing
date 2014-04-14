#version 130 

in vec3 fs_color;
in vec3 fs_light;
in vec3 fs_normal;

out vec4 out_Color;

void main() {
    vec3 ambientContrib = fs_color * 0.1;
	vec4 diffuseColor = vec4(fs_color, 1.0);

	//TODO: complete this using the diffuse equation from class!
	float intensity = 1.0;
	float diffuseTerm = intensity * (dot(fs_light, fs_normal));

	//out_Color = diffuseColor;
	
	//TODO: replace above out_Color with below once the diffuse term works.
    out_Color = diffuseTerm * diffuseColor + ambientContrib;
}