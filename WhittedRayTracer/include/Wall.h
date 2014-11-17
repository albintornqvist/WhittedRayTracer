#include "../include/SceneObject.h"

#ifndef WALL_H
#define WALL_H

class Ray;

class Wall : SceneObject
{
    public:
        Wall();
        ~Wall();

        glm::vec3 position;
        double size;

        bool intersection(Ray r);
        void initialize();
        void computationOfIntersections();
        glm::vec3 getLatestIntersection();
        float getIntersectionDistance();
        glm::vec3 getColor();

    private:
        glm::vec3 objectColor;
        glm::vec3 intersectionPoint;
        float intersectionDistance;
};

#endif // WALL_H
