#include "Triangle.h"

void Triangle::Update()
{
    m_v1 = m_transform * glm::vec4{ m_local_v1, 1 };
    m_v2 = m_transform * glm::vec4{ m_local_v2, 1 };
    m_v3 = m_transform * glm::vec4{ m_local_v3, 1 };
}

bool Triangle::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    float t;
    if (!Raycast(ray, m_v1, m_v2, m_v3, minDistance, maxDistance, t)) return false;

    raycastHit.distance = t;
    raycastHit.point = ray.at(t);

    glm::vec3 edge1 = m_v2 - m_v1;
    glm::vec3 edge2 = m_v3 - m_v1;

    raycastHit.normal = glm::normalize(Cross(edge1, edge2));
    raycastHit.material = GetMaterial();
}

bool Triangle::Raycast(const ray_t& ray, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, float minDistance, float maxDistance, float& t)
{
    // set edges of the triangle
    glm::vec3 edge1 = v2 - v1;
    glm::vec3 edge2 = v3 - v1;

    // calculate perpendicular vector, determine how aligned the ray is with the triangle plane
    glm::vec3 pvec = glm::cross(ray.direction, edge2); //<generate perpendicular vector with cross product ray direction and edge2>;
    float determinant = glm::dot(pvec, edge1); //<dot product of pvec and edge 1>;

    // if determinant is less than 0 then ray is hitting back of triangle
    // if determinant is 0 then ray is parallel to triangle surface
    if (determinant < 0 || approximately(determinant, 0)) //< determinant is < 0 or approximately 0>
    {
        return false;
    }

    // inverse determinant
    float invDet = 1 / determinant;

    // create direction vector from the triangle first vertex to the ray origin
    glm::vec3 tvec = ray.origin - v1; //<direction vector from m_v1 to ray origin>;
    // Calculate u parameter for barycentric coordinates
    float u = Dot(tvec, pvec) * invDet;
    // Check if u is outside the bounds of the triangle, no intersection
    if (u < 0 || u > 1) //<u is less than 0 or greater than 1>
    {
        return false;
    }

    // Calculate qvec, a vector perpendicular to both tvec and edge1, used to find the v parameter
    glm::vec3 qvec = glm::cross(tvec, edge1); //<how do you create a vector perpendicular to two vectors ? tvec x edge1>
    // Calculate v parameter for barycentric coordinates
    float v = Dot(qvec, ray.direction) * invDet;
    // Check if v is outside the bounds or if u + v exceeds 1, no intersection
    if (v < 0 || u + v > 1) //< v is less than 0 or u + v is greater than 1 >
    {
        return false;
    }

    // Calculate intersection distance and check range
    t = Dot(edge2, qvec) * invDet;
    if (t >= minDistance && t <= maxDistance)
    {
        return true;
    }

    return false;
}
