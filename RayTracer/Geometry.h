#pragma once
#include "Types.h"
#include "Ray.h"

class Material;

class Geometry
{
public:
    Geometry() = default;
    virtual ~Geometry() = default;
    Geometry(std::shared_ptr<Material> material) : material{ material } {}

    std::shared_ptr<Material> material;

    virtual bool Hit(const ray_t& ray, float tMin, float tMax, raycastHit_t& hit) = 0;
};