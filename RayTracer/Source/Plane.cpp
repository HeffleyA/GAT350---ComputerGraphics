#include "Plane.h"

bool Plane::Hit(const ray_t& ray)
{
        // check dot product of ray direction and plane normal, if result is 0 then ray direction if parallel to plane so it never hits plane
    // the dot product is 0 if the two vectors are perpendicular (90 degrees)
    float denominator = dot(ray.direction, m_normal);
    if (approximately(0, denominator))
    {
        return false; // ray direction and plane parallel, no intersection
    }
 
    // get t (distance) along ray direction to hit point
    float t = dot((m_center - ray.origin), (m_normal / denominator));
    if (t < 0)
    {
        return false; // plane behind ray's origin, no intersection
    }
    return true;
}
