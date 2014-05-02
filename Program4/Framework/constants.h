#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#define Matrix glm::mat4
#define Vec4 glm::vec4
#define Vec3 glm::vec3

#define RED Vec4(1, 0, 0, 1)
#define YELLOW Vec4(1, 1, 0, 1)
#define BLUE Vec4(0, 0, 1, 1)
#define ORANGE Vec4(1, 0.5, 0, 1)
#define WHITE Vec4(1, 1, 1, 1)
#define GREEN Vec4(0, 1, 0, 1)

const float PI = 3.14159265358979323f;

enum GEOMETRYTYPE {FURNITURE = 0, MESH = 1};

#define VERTEX_SHADER "lambert.vert"
#define FRAGMENT_SHADER "lambert.frag"

#endif