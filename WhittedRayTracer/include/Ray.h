#include "../lib/glm/glm/glm.hpp"

#ifndef RAY_H
#define RAY_H

class Scene;

class Ray
{
    public:
        Ray(glm::vec3 theStartingPoint, glm::vec3 theDirection, float theImportance, Scene *w);
        virtual ~Ray();

        glm::vec3 rayTracedColor(int iteration);

        int getIntersectedObject();
        //you shoot shadow rays from the ray-surface intersection point to the point light sources
        glm::vec3 getLocalColor(int objIdx);


        //the eye position
        glm::vec3 startingPoint;
        //diection of the random generated ray?
        glm::vec3 direction;

        bool insideObject;

    private:



        //how much importance this ray has from the parent ray
        float importance;
        //RGB vector of the ray
        glm::vec3 color;
        //if it finds the wall or left the room, leaves the room or is the last ray in the tree
        bool finalNode;
        //1 node for intransperent objects, 2 for transperent
        Ray *reflectedRay;
        Ray *refractedRay;
        //inside or outside an transperent object


        Scene *world;
        int refractedObject;


};

#endif // RAY_H
