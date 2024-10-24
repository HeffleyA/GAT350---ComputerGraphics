#pragma once
#include "Material.h"
#include "Ray.h"
#include <memory>

class SceneObject
{
public:
	SceneObject() = default;
	SceneObject(std::shared_ptr<Material> material) : m_material{ material }{}

	virtual bool Hit(const ray_t& ray) = 0;

	std::weak_ptr<Material> GetMaterial() { return m_material; }

protected:
	std::shared_ptr<Material> m_material;

};