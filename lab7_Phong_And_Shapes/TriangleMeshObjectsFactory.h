#pragma once

#include "TriangleMesh.h"

class CTriangleMeshObjectsFactory
{
public:
	std::unique_ptr<IGeometryObject> CreateCube(CMatrix4d const& transform = CMatrix4d());
	std::unique_ptr<IGeometryObject> CreateTetrahedron(CMatrix4d const& transform = CMatrix4d());

private:
	using CTriangleMeshDataPtr = std::shared_ptr<CTriangleMeshData>;

	CTriangleMeshDataPtr CreateCubeMeshData();
	CTriangleMeshDataPtr CreateTetrahedronMeshData();

	CTriangleMeshDataPtr m_cubeMeshData = nullptr;
	CTriangleMeshDataPtr m_tetrahedronMeshData = nullptr;
};
