#include "../include/Wall.h"
#include "../include/Ray.h"

//perfect diffuse reflectors
Wall::Wall()
{
    //ctor
}

Wall::~Wall()
{
    //dtor
}

bool Wall::intersection(Ray r)
{
    return false;
}

glm::vec3 Wall::getColor()
{
    return objectColor;
}

glm::vec3 Wall::getLatestIntersection()
{
    return glm::vec3(0,0,0);
}

float Wall::getIntersectionDistance()
{
    return intersectionDistance;
}
