#include "../include/Sphere.h"
#include "../include/Ray.h"
#include <iostream>
#include <math.h>

//one transperent and one perfect reflector
Sphere::Sphere(glm::vec3 pos, float rad, float diffIdx, float refract, glm::vec3 theColor, bool trans)
{
    position = pos;
    radius = rad;
    diffuseIndex = diffIdx;
    refractiveIndex = refract;
    color = theColor;
    diffuse = false;
    transparent = trans;
    diffuseIndex = diffIdx;
}

Sphere::~Sphere()
{
    //dtor
}

bool Sphere::intersection(Ray r)
{
    glm::vec3 L = position - r.startingPoint; //L is the vector between the ray.starting point and the sphere center

    float Tca = glm::dot(L,glm::normalize(r.direction));
    if(Tca < 0)
    {
        return false;
    }

    float d2 =  glm::dot(L,L) - Tca * Tca;
    //float d = math::sqrt(d2);
    if(d2 > radius*radius) // d !?
    {
        return false;
    }

    float Thc = sqrt(radius*radius - d2);

    t0 = Tca - Thc; //t0 = distance from ray.startingPoint to the first intersection ANVÄND DESSA!
    t1 = Tca + Thc; //t1 = distance from ray.startingPoint to the second intersection ANVÄND DESSA!

    p0 = r.startingPoint + r.direction*t0;
    p1 = r.startingPoint + r.direction*t1;

    return true;
}

glm::vec3 Sphere::calculateReflectedRay(Ray r)
{
    glm::vec3 normal = glm::normalize(p0 - position); //normal of p0 intersection

    return glm::normalize((r.direction - 2*(glm::dot(r.direction,normal))*normal));
}

glm::vec3 Sphere::calculateRefractedRay(Ray r)
{


    if(r.insideObject)
    {
        //std::cout << "r.direction: " << r.direction.x << ", " << r.direction.y << ", " << r.direction.z << std::endl;
        glm::vec3 normal = glm::normalize(position - p1);
        float cosi = -glm::dot(normal, r.direction);
        //std::cout << "dot(normal, r.direction) = " << cosi << std::endl;

        float q = 1-refractiveIndex*refractiveIndex*(1-cosi*cosi);

        if(q<0)
        {
            return glm::normalize((r.direction - 2*(glm::dot(r.direction,normal))*normal));
        }

        return glm::normalize(refractiveIndex*r.direction + normal*(-refractiveIndex*glm::dot(normal, r.direction) - (float)sqrt(q))); //T is the refracted ray out of the sphere
    }
    else
    {
        glm::vec3 normal = glm::normalize(p0 - position);
        return glm::normalize((1/refractiveIndex)*r.direction + normal*(-1/refractiveIndex*glm::dot(normal,(r.direction)) - (float)sqrt(1-pow(1/refractiveIndex,2)*(1-pow(glm::dot(normal,r.direction),2))))); //T is the refracted ray into the sphere
    }
}

glm::vec3 Sphere::getLatestIntersection()
{
    return p0;
}

float Sphere::getIntersectionDistance()
{
    return t0;
}

glm::vec3 Sphere::getIntersectionNormal()
{

    return glm::normalize(p0 - position);
}

glm::vec3 Sphere::getColor()
{
    return color;
}

glm::vec3 Sphere::getP0()
{
    return p0;
}

glm::vec3 Sphere::getSecondIntersection()
{
    return p1;
}

float Sphere::getDistanceT0()
{
    return 0;
}

float Sphere::getDistanceT1()
{
    return 0;
}

bool Sphere::isDiffuse()
{
    return diffuse;
}

bool Sphere::isTransparent()
{
    return transparent;
}

float Sphere::getDiffuseIndex()
{
    return diffuseIndex;
}

glm::vec3 Sphere::getPosition()
{
    return position;
}

float Sphere::getRefractiveIndex()
{
    return refractiveIndex;
}

