#include "../lib/glm/glm/glm.hpp"
#include "../include/SceneObject.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Ray;

class Rectangle : public SceneObject
{
    public:
        Rectangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4, glm::vec3 n, glm::vec3 theColor);
        virtual ~Rectangle();

        bool intersection(Ray r);
        glm::vec3 calculateReflectedRay(Ray r);
        glm::vec3 calculateRefractedRay(Ray r);
        glm::vec3 getLatestIntersection();
        glm::vec3 getSecondIntersection();
        float getIntersectionDistance();
        glm::vec3 getIntersectionNormal();
        glm::vec3 getColor();
        bool isDiffuse();
        bool isTransparent();
        float getDiffuseIndex();
        glm::vec3 getPosition();
        float getRefractiveIndex();

    protected:
    private:
		glm::vec3 corner1, corner2, corner3, corner4;
        glm::vec3 basV1, basV2;
		glm::vec3 normal;
		float distance;
		glm::vec3 P;
		glm::vec3 objectColor;

		float refractiveIndex;
		bool diffuse;
		bool transparent;
		float diffuseIndex;

};

#endif // RECTANGLE_H
