#include "../lib/glm/glm/glm.hpp"

#ifndef LIGHT_H
#define LIGHT_H


class Light
{
    public:
        Light(glm::vec3 pos, glm::vec3 col, float r);
        virtual ~Light();

        float radiance;
        glm::vec3 position;
        glm::vec3 color;

        //void randomPosition();

    private:
};

#endif // LIGHT_H
