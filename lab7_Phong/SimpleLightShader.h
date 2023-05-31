#pragma once

#include "IShader.h"
#include "SimpleMaterial.h"

class CSimpleLightShader : public IShader
{
public:
	CSimpleLightShader(CSimpleMaterial const& material = CSimpleMaterial());

	void SetMaterial(CSimpleMaterial const& material);

	virtual CVector4f Shade(CShadeContext const& shadeContext) const;

private:
	CSimpleMaterial m_material;
};
