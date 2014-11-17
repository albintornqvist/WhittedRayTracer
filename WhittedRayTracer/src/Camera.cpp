#include "../include/Camera.h"
#include "../include/Pixel.h"
#include "../include/Scene.h"
#include <iostream>
#include <fstream>
#include <algorithm>


Camera::Camera(int h, int w, int rpp, double vpd)
{
    position = glm::vec3(0,0,0);
    viewDirection = glm::vec3(0,1,0);
    viewPlaneDistance = vpd;
    raysPerPixel = rpp;
    height = h;
    width = w;
    image = new glm::vec3[width*height];
}

Camera::~Camera()
{

}

//loop over all pixels
void Camera::renderImage(Scene &world)
{
    glm::vec3 *pixelValue = image;

    float normW = 0, normH = 0;

    glm::vec3 right = glm::vec3(1, 0, 0);
    glm::vec3 down = glm::vec3(0, 0, -1);
    glm::vec3 imagePoint;

    std::cout << "looping through pixels in image plane with resolution: " << width << "x" << height << std::endl;

    int counter = 0;

    for(unsigned h = 1; h<=height; ++h)
    {
        for(unsigned w = 1; w<=width; ++w, ++pixelValue)
        {
            float viewRatio = (float)width/height;

            float dx = 1/(float)width;
            float dy = 1/(float)height;

            normW = ((w/(float)width) - 0.5 - dx)*viewRatio;
            normH = (h/(float)height) - 0.5 - dy;

            imagePoint = normW*right + normH*down + viewDirection*viewPlaneDistance;

            //std::cout << "ray direction: " << imagePoint.x << ", " << imagePoint.y << ", " << imagePoint.z << std::endl;

            Pixel *pix = new Pixel(imagePoint, right*dx, down*dy, glm::vec3(0,0,0), raysPerPixel, world);//unfinished specs

            //std::cout << "shooting ray from pixel" << std::endl;

            counter++;
            //std::cout << "working on pixel nr: " << counter << std::endl;
            pix->shootRays();

            *pixelValue = pix->getColor();


            delete pix;
        }
    }


    std::cout << "Writing data to .ppm-file" << std::endl;
    //Writes image values to file here...
    // Save result to a PPM image (keep these flags if you compile under Windows)
    //std::ofstream ofs("./whitted.ppm", std::ios::out | std::ios::binary);
	std::ofstream ofs("Documents/Github/Raytracerzz/Raytracerzz/whitted.ppm", std::ios::out | std::ios::binary);

	ofs << "P6\n" << width << " " << height << "\n255\n";

	for (unsigned i = 0; i < width * height; ++i)
    {
		ofs << (unsigned char)(std::min(1.0f, image[i].x) * 255) <<
		(unsigned char)(std::min(1.0f, image[i].y) * 255) <<
		(unsigned char)(std::min(1.0f, image[i].z) * 255);
	}

	ofs.close();

	delete [] image;

}

//convert radiometric pixel colour to photometric
void Camera::mappingFunction()
{

}

//plot the figure or save it as an image
void Camera::displayImage()
{

}
