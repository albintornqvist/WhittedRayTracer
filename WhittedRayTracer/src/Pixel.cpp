#include "../include/Pixel.h"
#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/SceneObject.h"
#include <iostream>


Pixel::Pixel(glm::vec3 c, glm::vec3 right, glm::vec3 down, glm::vec3 cPos, int rpps, Scene &w)
{
    corner = c;
    rightAxis = right;
    downAxis = down;
    cameraPos = cPos;
    raysPerPixel = rpps;
    world = &w;
    pixColor = glm::vec3(0,0,0);
}

Pixel::~Pixel()
{
    //dtor
}

glm::vec3 Pixel::getColor()
{
    return pixColor;
}

void Pixel::shootRays()
{
    for(int i=0; i<raysPerPixel; i++)
    {
        glm::vec3 newPoint = corner + rightAxis*static_cast<float>(rand())/static_cast<float>(RAND_MAX) + downAxis*static_cast<float>(rand())/static_cast<float>(RAND_MAX);

        glm::vec3 rayDir = glm::normalize(newPoint - cameraPos);

        Ray pixelRay = Ray(cameraPos, rayDir, (float)1.0, world);

        pixColor += pixelRay.rayTracedColor(0);
    }

    pixColor /= raysPerPixel;


}
