#include "../include/Ray.h"
#include "../include/Scene.h"
#include "../include/SceneObject.h"
#include "../include/Light.h"
#include <iostream>
#include <math.h>

Ray::Ray(glm::vec3 theStartingPoint, glm::vec3 theDirection, float theImportance, Scene *w)
{
    startingPoint = theStartingPoint;
    direction = theDirection;
    importance = theImportance;
    world = w;
    insideObject = false;
    refractedObject = -1;
}

Ray::~Ray()
{
    //dtor
}

glm::vec3 Ray::rayTracedColor(int iteration)
{
    if(iteration<7 && importance>0.05)
    {

        if(insideObject && (refractedObject != -1)) //maybe limit depending on iterations
        {

            if(world->Objects->at(refractedObject)->intersection(*this))
            {
                glm::vec3 secondIntersection = world->Objects->at(refractedObject)->getSecondIntersection();
                glm::vec3 objectNormal = glm::normalize(secondIntersection - world->Objects->at(refractedObject)->getPosition());

                float cosi = glm::dot(objectNormal, direction);
                float refractiveIndex = world->Objects->at(refractedObject)->getRefractiveIndex();
                float q = 1-refractiveIndex*refractiveIndex*(1-cosi*cosi);

                glm::vec3 newRefractedDir = world->Objects->at(refractedObject)->calculateRefractedRay(*this);

                Ray refractedRay = Ray(secondIntersection, newRefractedDir, importance, world);

                if(q<0)
                {
                    refractedRay.insideObject = true;
                }

                return refractedRay.rayTracedColor(++iteration);
            }
            else
                return glm::vec3(0,0,0);
        }
        else
        {
            int objIdx = getIntersectedObject();

            if(objIdx != -1) //if an object have been intersected
            {
                if(!world->Objects->at(objIdx)->isDiffuse()) //Change nr of iterations
                {
                    if(world->Objects->at(objIdx)->isTransparent()) //object is transparent, calculate two rays
                    {
                        glm::vec3 localColor = getLocalColor(objIdx); //local color contribution

                        float refIdx = world->Objects->at(objIdx)->getRefractiveIndex();

                        float RefImp = pow((1 - refIdx)/(1+refIdx), 2);
                        float RefractImp = 1-RefImp;

                        float diffuseFactor = world->Objects->at(objIdx)->getDiffuseIndex(); //how diffuse is the object?
                        float refractedImportance = (importance - diffuseFactor*importance)*RefractImp;
                        float reflectedImportance = (importance - diffuseFactor*importance)*RefImp;

                        //calculate reflected ray direction
                        glm::vec3 reflectedDir = world->Objects->at(objIdx)->calculateReflectedRay(*this);
                        Ray reflectedRay = Ray(world->Objects->at(objIdx)->getLatestIntersection(), reflectedDir, reflectedImportance, world);

                        //calculate refracted ray
                        glm::vec3 refractedDir = world->Objects->at(objIdx)->calculateRefractedRay(*this);
                        Ray refractedRay = Ray(world->Objects->at(objIdx)->getLatestIntersection(), refractedDir, refractedImportance, world);
                        refractedRay.insideObject = true;
                        refractedRay.refractedObject = objIdx;

                        iteration++;

                        return importance*diffuseFactor*localColor + reflectedRay.rayTracedColor(iteration) + refractedRay.rayTracedColor(iteration);
                    }
                    else //the object is reflective only
                    {
                        float diffuseFactor = world->Objects->at(objIdx)->getDiffuseIndex(); //how diffuse is the object?
                        float newImportance = importance - diffuseFactor*importance;

                        //calculate reflected ray direction
                        glm::vec3 reflectedDir = world->Objects->at(objIdx)->calculateReflectedRay(*this);
                        Ray reflectedRay = Ray(world->Objects->at(objIdx)->getLatestIntersection(), reflectedDir, newImportance, world);
                        glm::vec3 localColor = getLocalColor(objIdx);


                        return localColor*diffuseFactor*importance + reflectedRay.rayTracedColor(++iteration); //++ before to send the added number
                    }

                }
                else //The object is diffuse
                {
                    return getLocalColor(objIdx)*importance;
                }


            }
            else //no object intersected = empty space
                return glm::vec3(0,0,0);

        }
    }
    else
        return glm::vec3(0,0,0);
}

int Ray::getIntersectedObject()
{
//check intersection, get color from object
    int nrOfObj = world->Objects->size();
    int objectIdx = -1;
    float minDist = 999999;

    for(int i=0; i<nrOfObj; i++)
    {
        if(world->Objects->at(i)->intersection(*this)) //if the object intersects with this ray
        {
            if(world->Objects->at(i)->getIntersectionDistance() < minDist) //if the distance to the intersection is shorter than previous intersections
            {
                objectIdx = i;
                minDist = world->Objects->at(i)->getIntersectionDistance();
            }
        }
    }
    return objectIdx;

}


glm::vec3 Ray::getLocalColor(int objIdx)
{
    glm::vec3 iPoint = world->Objects->at(objIdx)->getLatestIntersection();
    glm::vec3 n = glm::normalize(world->Objects->at(objIdx)->getIntersectionNormal());
    glm::vec3 objColor = world->Objects->at(objIdx)->getColor();
    int nrOfLights = world->Lights->size();
    int nrOfObj = world->Objects->size();

    glm::vec3 color = glm::vec3(0,0,0);

    for(unsigned i=0; i<nrOfLights; i++)
    {
        glm::vec3 lightVec = world->Lights->at(i)->position - iPoint;

        Ray shadowRay = Ray(iPoint, glm::normalize(lightVec), 1.0, world);
        bool intersected = false;


        for(int k=0; k<nrOfObj; k++)
        {
            if(world->Objects->at(k)->intersection(shadowRay)) //if the object intersects with this ray
            {
                if(glm::length(lightVec) >= world->Objects->at(k)->getIntersectionDistance())
                    intersected = true;
            }
        }


        if(!intersected)
        {
            bool specular = !world->Objects->at(objIdx)->isDiffuse();
            bool transparent = world->Objects->at(objIdx)->isTransparent();

            float d = glm::length(lightVec);

            lightVec = glm::normalize(lightVec);

            float lambertian = 0;

            if(!transparent)
                lambertian = glm::dot(n, lightVec);// / (d/5);


            glm::vec3 H = glm::normalize(lightVec+glm::normalize(-iPoint));
            glm::vec3 specularity = glm::vec3(0,0,0);

            if(specular)
                specularity = (float)pow(glm::dot(n,H), 40)*glm::vec3(1,1,1);//(d/5);*/

            if(lambertian >= 0)
            {
                color += (lambertian * objColor + specularity) * world->Lights->at(i)->radiance / (d/3); //diffuse phong
            }

        }


    }

    return color;
}



