#include "../include/Cube.h"
#include "../include/SceneObject.h"
#include "../include/Rectangle.h"
#include "../include/Ray.h"
#include <iostream>

//one
Cube::Cube(glm::vec3 pos, double d, bool t, double idx, glm::vec3 color)
{
    position = pos;
	size = d;
	refractiveIndex = idx;
	objectColor = color;
	walls = new std::vector<Rectangle*>();
	diffuse = true;
	transparent = t;
	diffuseIndex = 1;
}

Cube::~Cube(){}

void Cube::initialize()
{
	//Defining corner points, scaling and translation to world coordinates

	//Bottom four points
	p0 = glm::vec3(0, 0, 0)*size + position;
	p1 = glm::vec3(0, 1, 0)*size + position;
	p2 = glm::vec3(1, 1, 0)*size + position;
	p3 = glm::vec3(1, 0, 0)*size + position;

	//top four points
	p4 = glm::vec3(0, 0, 1)*size + position;
	p5 = glm::vec3(0, 1, 1)*size + position;
	p6 = glm::vec3(1, 1, 1)*size + position;
	p7 = glm::vec3(1, 0, 1)*size + position;


	walls->push_back(new Rectangle(p0, p1, p2, p3, glm::vec3(0, 0, -1), objectColor)); //bottom
	walls->push_back(new Rectangle(p0, p4, p5, p1, glm::vec3(-1, 0, 0), objectColor)); //left
	walls->push_back(new Rectangle(p1, p5, p6, p2, glm::vec3(0, 1, 0), objectColor)); //back
	walls->push_back(new Rectangle(p3, p2, p6, p7, glm::vec3(1, 0, 0), objectColor)); //right
	walls->push_back(new Rectangle(p0, p3, p7, p4, glm::vec3(0, -1, 0), objectColor)); //front
	walls->push_back(new Rectangle(p4, p7, p6, p5, glm::vec3(0, 0, 1), objectColor)); //top
}

bool Cube::intersection(Ray r)
{
    float minDist = 99999999;
    int rectangleIdx = -1;

    for(unsigned i=0; i<walls->size(); i++)
    {
        if(walls->at(i)->intersection(r))
        {
            if(walls->at(i)->getIntersectionDistance() < minDist)
            {
                minDist = walls->at(i)->getIntersectionDistance();
                rectangleIdx = i;
            }
        }
    }

    if(rectangleIdx != -1)
    {
        intersectionDistance = minDist;
        intersectionPoint = walls->at(rectangleIdx)->getLatestIntersection();
        intersectionNormal = walls->at(rectangleIdx)->getIntersectionNormal();
        return true;
    }
    else
        return false;
}

glm::vec3 Cube::getColor()
{
    return objectColor;
}

glm::vec3 Cube::getLatestIntersection()
{
    return intersectionPoint;
}

glm::vec3 Cube::getSecondIntersection()
{
    return glm::vec3(0,0,0); //not implemented yet
}

float Cube::getIntersectionDistance()
{
    return intersectionDistance;
}

glm::vec3 Cube::getIntersectionNormal()
{
    return intersectionNormal;
}

glm::vec3 Cube::calculateReflectedRay(Ray r)
{
    return glm::vec3(0,0,1);
}


glm::vec3 Cube::calculateRefractedRay(Ray r)
{
    return glm::vec3(0,0,1);
}

bool Cube::isDiffuse()
{
    return diffuse;
}

bool Cube::isTransparent()
{
    return transparent;
}

float Cube::getDiffuseIndex()
{
    return diffuseIndex;
}

glm::vec3 Cube::getPosition()
{
    return position;
}

float Cube::getRefractiveIndex()
{
    return refractiveIndex;
}
