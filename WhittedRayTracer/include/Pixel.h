#include <vector>
#include "../lib/glm/glm/glm.hpp"

#ifndef PIXEL_H
#define PIXEL_H

class Ray;
class Scene;

class Pixel
{
    public:
        Pixel(glm::vec3 c, glm::vec3 right, glm::vec3 down, glm::vec3 cPos, int rpp, Scene &w);
        virtual ~Pixel();

        void shootRays();
        glm::vec3 getColor();


    private:
        //std::vector<Ray*> *arrayOfRays; //holds the adress to all rays shot from the eye point
        glm::vec3 pixelColor;
        glm::vec3 corner, rightAxis, downAxis, cameraPos;
        int raysPerPixel;
        Scene *world;
        glm::vec3 pixColor;
};

#endif // PIXEL_H
