#include "stdafx.h"
#include "TriangleMeshObjectsFactory.h"

std::unique_ptr<IGeometryObject> CTriangleMeshObjectsFactory::CreateCube(CMatrix4d const& transform)
{
	if (m_cubeMeshData == nullptr)
	{
		m_cubeMeshData = CreateCubeMeshData();
	}

	return std::make_unique<CTriangleMesh>(m_cubeMeshData, transform);
}

std::unique_ptr<IGeometryObject> CTriangleMeshObjectsFactory::CreateTetrahedron(CMatrix4d const& transform)
{
	if (m_tetrahedronMeshData == nullptr)
	{
		m_tetrahedronMeshData = CreateTetrahedronMeshData();
	}

	return std::make_unique<CTriangleMesh>(m_tetrahedronMeshData, transform);
}

CTriangleMeshObjectsFactory::CTriangleMeshDataPtr CTriangleMeshObjectsFactory::CreateCubeMeshData()
{
	std::vector<Vertex> vertices{
		Vertex({ -1, 0, -1 }),
		Vertex({ +1, 0, -1 }),
		Vertex({ +1, +2, -1 }),
		Vertex({ -1, +2, -1 }),
		Vertex({ -1, 0, +1 }),
		Vertex({ +1, 0, +1 }),
		Vertex({ +1, +2, +1 }),
		Vertex({ -1, +2, +1 }),
	};

	std::vector<Face> faces{
		{ 4, 7, 3 },
		{ 4, 3, 0 },
		{ 5, 2, 6 },
		{ 5, 1, 2 },
		{ 4, 0, 1 },
		{ 4, 1, 5 },
		{ 3, 6, 2 },
		{ 3, 7, 6 },
		{ 2, 1, 0 },
		{ 2, 0, 3 },
		{ 5, 6, 7 },
		{ 5, 7, 4 },
	};

	return std::make_shared<CTriangleMeshData>(vertices, faces);
}

CTriangleMeshObjectsFactory::CTriangleMeshDataPtr CTriangleMeshObjectsFactory::CreateTetrahedronMeshData()
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

	return std::make_shared<CTriangleMeshData>(vertices, faces);
}
