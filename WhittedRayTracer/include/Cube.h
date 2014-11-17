#include "../include/SceneObject.h"
#include <vector>

#ifndef CUBE_H
#define CUBE_H

class Rectangle;
class Ray;

class Cube : public SceneObject
{
    public:
        Cube(glm::vec3 pos, double d, bool t, double idx, glm::vec3 theColor);
        virtual ~Cube();

        void initialize();
        glm::vec3 calculateReflectedRay(Ray r);
        glm::vec3 calculateRefractedRay(Ray r);
		bool intersection(Ray r);
		glm::vec3 getLatestIntersection();
		glm::vec3 getSecondIntersection();
		float getIntersectionDistance();
		glm::vec3 getIntersectionNormal();
		glm::vec3 getColor();
		glm::vec3 getPosition();
		float getRefractiveIndex();

		std::vector<Rectangle*> *walls;
		bool isDiffuse();
		bool isTransparent();
		float getDiffuseIndex();

    private:
		glm::vec3 position;
        float size;
        double refractiveIndex;
        glm::vec3 objectColor;

        glm::vec3 intersectionPoint;
        float intersectionDistance;
        glm::vec3 intersectionNormal;
        bool diffuse;
        bool transparent;
        float diffuseIndex;

		//corner points
		glm::vec3 p0, p1, p2, p3, p4, p5, p6, p7;

};

#endif // CUBE_H
