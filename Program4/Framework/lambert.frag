#version 130 

in vec3 fs_color;
in vec3 fs_light;
in vec3 fs_normal;
in vec3 fs_eye;

out vec4 out_Color;

void main() {
    vec3 ambientContrib = fs_color * 0.1;
	vec4 diffuseColor = vec4(fs_color, 1.0);
	vec4 specColor = vec4(1, 1, 1, 1);

	//TODO: complete this using the diffuse equation from class!
	float intensity = 1.0;
	float diffuseTerm = intensity * (dot(fs_light, fs_normal));

	vec3 l = normalize(fs_light);
	vec3 v = normalize(fs_eye);
	vec3 h = normalize(l+v);
	vec3 r = -l - dot(fs_normal, -l)*fs_normal * 2.0;
	
	float i = pow(max(dot(h, fs_normal), 0), 128);

	//float i = 0;
	//float ndoth = dot(fs_normal, h);
	//float i = pow(clamp(ndoth, 0, 1), 16);
	
	//TODO: replace above out_Color with below once the diffuse term works.
    out_Color = i * specColor + diffuseTerm * diffuseColor + ambientContrib;
}