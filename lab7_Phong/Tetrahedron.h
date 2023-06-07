#pragma once

#include "TriangleMesh.h"

class CTetrahedron : public CGeometryObjectImpl
{
public:
	CTetrahedron(CMatrix4d const& transform = CMatrix4d());

	virtual bool Hit(CRay const& ray, CIntersection& intersection) const;

private:
	CTriangleMesh m_mesh{ nullptr };
};
