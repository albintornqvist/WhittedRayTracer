#include "../lib/glm/glm/glm.hpp"

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

class Ray;

class SceneObject
{
    public:
        SceneObject();
        virtual ~SceneObject();
        virtual bool intersection(Ray r) = 0;
        virtual glm::vec3 getLatestIntersection() = 0;
        virtual float getIntersectionDistance() = 0;
        virtual glm::vec3 getColor() = 0;
        virtual glm::vec3 getIntersectionNormal() = 0;
        virtual glm::vec3 calculateReflectedRay(Ray r) = 0;
        virtual glm::vec3 calculateRefractedRay(Ray r) = 0;
        virtual bool isDiffuse() = 0;
        virtual bool isTransparent() = 0;
        virtual float getDiffuseIndex() = 0;
        virtual glm::vec3 getPosition() = 0;
        virtual glm::vec3 getSecondIntersection() = 0;
        virtual float getRefractiveIndex() = 0;


    private:
};

#endif // SCENEOBJECT_H
