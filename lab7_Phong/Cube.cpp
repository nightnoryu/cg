#include "stdafx.h"
#include "Cube.h"

CCube::CCube(CMatrix4d const& transform)
	: m_mesh(nullptr)
{
	std::vector<Vertex> vertices{
		Vertex({ -1, 0, -1 }), // 0
		Vertex({ +1, 0, -1 }), // 1
		Vertex({ +1, +2, -1 }), // 2
		Vertex({ -1, +2, -1 }), // 3
		Vertex({ -1, 0, +1 }), // 4
		Vertex({ +1, 0, +1 }), // 5
		Vertex({ +1, +2, +1 }), // 6
		Vertex({ -1, +2, +1 }), // 7
	};

	std::vector<Face> faces{
		{ 4, 7, 3 }, // x<0
		{ 4, 3, 0 }, // x<0
		{ 5, 2, 6 }, // x>0
		{ 5, 1, 2 }, // x>0
		{ 4, 0, 1 }, // y<0
		{ 4, 1, 5 }, // y<0
		{ 3, 6, 2 }, // y>0
		{ 3, 7, 6 }, // y>0
		{ 2, 1, 0 }, // z<0
		{ 2, 0, 3 }, // z<0
		{ 5, 6, 7 }, // z>0
		{ 5, 7, 4 }, // z>0
	};

	auto const pMeshData = std::make_shared<CTriangleMeshData>(vertices, faces);
	m_mesh = CTriangleMesh(pMeshData, transform);
}

bool CCube::Hit(CRay const& ray, CIntersection& intersection) const
{
	return m_mesh.Hit(ray, intersection);
}
