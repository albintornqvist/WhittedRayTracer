#include <vector>
#include "../lib/glm/glm/glm.hpp"
#include "../include/SceneObject.h"

#ifndef SPHERE_H
#define SPHERE_H

class Ray;

class Sphere : public SceneObject
{
    public:
        Sphere(glm::vec3 pos, float rad, float diffIdx, float refract, glm::vec3 color, bool trans);
        virtual ~Sphere();

        //calculates the intersection of a ray and a shpere
        bool intersection(Ray r);
        glm::vec3 getLatestIntersection();
        float getIntersectionDistance();
        glm::vec3 getIntersectionNormal();
        glm::vec3 getSecondIntersection();
        //depends on the texture of the spheress
        glm::vec3 calculateReflectedRay(Ray r);
        glm::vec3 calculateRefractedRay(Ray r);

        glm::vec3 getP0();
        float getDistanceT0();
        float getDistanceT1();
        glm::vec3 getColor();
        bool isDiffuse();
        bool isTransparent();
        float getDiffuseIndex();
        glm::vec3 getPosition();
        float refractiveIndex; //>1.0, <1.5
        float getRefractiveIndex();

    protected:
    private:
        glm::vec3 position;
        float radius;

        glm::vec3 color;
        float t0;
        float t1;
        glm::vec3 p0;
        glm::vec3 p1;
        glm::vec3 intersectionNormal;
        bool diffuse;
        bool transparent;
        float diffuseIndex;
};

#endif // SPHERE_H
