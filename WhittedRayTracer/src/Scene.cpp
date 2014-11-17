#include "../include/Scene.h"
#include "../include/SceneObject.h"
#include "../include/Light.h"

Scene::Scene()
{
    Objects = new std::vector<SceneObject*>();
    Lights = new std::vector<Light*>();
}

Scene::~Scene()
{
    //dtor
}

void Scene::addObject(SceneObject *so)
{
    Objects->push_back(so);
}

void Scene::addLight(Light *li)
{
    Lights->push_back(li);
}
