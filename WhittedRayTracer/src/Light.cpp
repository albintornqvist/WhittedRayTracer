#include "../include/Light.h"

Light::Light(glm::vec3 pos, glm::vec3 col, float r)
{
    position = pos;
    color = col;
    radiance = r;
}

Light::~Light()
{
    //dtor
}
