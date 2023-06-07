#include "stdafx.h"
#include "Tetrahedron.h"

CTetrahedron::CTetrahedron(CMatrix4d const& transform)
{
	std::vector<Vertex> vertices{
		Vertex({ -1, 0, 1 }),
		Vertex({ +1, 0, 1 }),
		Vertex({ 0, 0, -1 }),
		Vertex({ 0, 2, 0 }),
	};

	std::vector<Face> faces{
		{ 0, 2, 1 },
		{ 3, 0, 1 },
		{ 3, 1, 2 },
		{ 3, 2, 0 },
	};

	auto const pMeshData = std::make_shared<CTriangleMeshData>(vertices, faces);
	m_mesh = CTriangleMesh(pMeshData, transform);
}

bool CTetrahedron::Hit(CRay const& ray, CIntersection& intersection) const
{
	return m_mesh.Hit(ray, intersection);
}
