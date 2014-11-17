#include "../include/Rectangle.h"
#include "../include/Ray.h"
#include <iostream>
#include <cmath>

Rectangle::Rectangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, glm::vec3 n, glm::vec3 theColor)
{
    corner1 = v1;
    corner2 = v2;
    corner3 = v3;
    corner4 = v4;
    basV1 = v1 - v2;
    basV2 = v3 - v2;
	normal = n;
	objectColor = theColor;
	refractiveIndex = 1.0;
	diffuse = true;
	transparent = false;
	diffuseIndex = 1;
}

bool Rectangle::intersection(Ray r)
{

    float denom = -(glm::dot(normal, r.direction));

    if(denom > 1e-6)   // if the angle between the normal and the vector from the ray is perpenduícular then denum is Zero, and no intersection is made.
    {

        glm::vec3 dist = -(corner1 - r.startingPoint);
        distance = glm::dot(dist, normal)/denom; //distance is the distance from the ray.startingPoint to the intersected point on the plane

        if (distance >= 0)
        {

            glm::vec3 tempP = r.startingPoint + distance * glm::normalize(r.direction); //the intersection point
            glm::vec3 vecP = tempP - corner2; //vector from the intersection point to corner2 of the rectangle

            float lenghtBasV1 = glm::length(basV1);
            float lenghtBasV2 = glm::length(basV2);

            float dot1 = glm::dot(vecP, glm::normalize(basV1));
            float dot2 = glm::dot(vecP, glm::normalize(basV2));

            if(dot1 <= lenghtBasV1 && dot1 >= 0 && dot2 <= lenghtBasV2  && dot2 >= 0)
            {
                P = tempP;
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

 glm::vec3 Rectangle::calculateReflectedRay(Ray r)
{
    return (r.direction - 2*(glm::dot(r.direction,normal))*normal);
}

glm::vec3 Rectangle::calculateRefractedRay(Ray r)
{
    if(r.insideObject)
    {
        r.insideObject = false;
        return (refractiveIndex*r.direction + normal*(-refractiveIndex*glm::dot(normal,-(r.direction)) - (float)sqrt(1-pow(refractiveIndex,2)*(1-pow(glm::dot(normal,r.direction),2))))); //T is the refracted ray out of the sphere
    }
    else
    {
        r.insideObject = true;
        return ((1/refractiveIndex)*r.direction + normal*(-1/refractiveIndex*glm::dot(normal,-(r.direction)) - (float)sqrt(1-pow(1/refractiveIndex,2)*(1-pow(glm::dot(normal,r.direction),2))))); //T is the refracted ray into the sphere
    }
}

Rectangle::~Rectangle()
{
    //dtor
}

glm::vec3 Rectangle::getLatestIntersection()
{
    return P;
}

float Rectangle::getIntersectionDistance()
{
    return distance;
}

glm::vec3 Rectangle::getIntersectionNormal()
{
    return normal;
}

glm::vec3 Rectangle::getColor()
{
    return objectColor;
}

bool Rectangle::isDiffuse()
{
    return diffuse;
}

bool Rectangle::isTransparent()
{
    return transparent;
}

float Rectangle::getDiffuseIndex()
{
    return diffuseIndex;
}

glm::vec3 Rectangle::getSecondIntersection()
{
    return glm::vec3(0,0,0);
}

glm::vec3 Rectangle::getPosition()
{
    return corner1;
}

float Rectangle::getRefractiveIndex()
{
    return refractiveIndex;
}
