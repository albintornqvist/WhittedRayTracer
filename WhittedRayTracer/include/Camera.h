#include "../lib/glm/glm/glm.hpp"

#ifndef CAMERA_H
#define CAMERA_H


class Pixel;
class Scene;

class Camera
{
    public:
        Camera(int h, int w, int rpp, double vpd);
        ~Camera();

        void renderImage(Scene &world); //loop over all pixels
        void mappingFunction(); //convert radiometric pixel colour to photometric
        void displayImage(); //plot the figure or save it as an image

    protected:
    private:
        glm::vec3 position;
        glm::vec3 viewDirection;
        float viewPlaneDistance;
        int height;
        int width;
        int raysPerPixel;
        glm::vec3 *image;
};

#endif // CAMERA_H
