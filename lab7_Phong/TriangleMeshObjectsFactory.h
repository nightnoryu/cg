#pragma once

#include "TriangleMesh.h"

class CTriangleMeshObjectsFactory
{
public:
	CTriangleMesh CreateCube(CMatrix4d const& transform = CMatrix4d());
	CTriangleMesh CreateTetrahedron(CMatrix4d const& transform = CMatrix4d());

private:
	using CTriangleMeshDataPtr = std::shared_ptr<CTriangleMeshData>;

	CTriangleMeshDataPtr CreateCubeMeshData();
	CTriangleMeshDataPtr CreateTetrahedronMeshData();

	CTriangleMeshDataPtr m_cubeMeshData = nullptr;
	CTriangleMeshDataPtr m_tetrahedronMeshData = nullptr;
};
