#pragma once

#include "ILightSource.h"
#include "Matrix4.h"
#include "Vector4.h"

class CLightSourceImpl : public ILightSource
{
public:
	CMatrix4d const& GetTransform() const
	{
		return m_transform;
	}

	void SetTransform(CMatrix4d const& transform)
	{
		m_transform = transform;
	}

	virtual void SetAmbientIntensity(CVector4f const& ambientIntensity)
	{
		m_ambientIntensity = ambientIntensity;
	}

	virtual CVector4f const& GetAmbientIntensity() const
	{
		return m_ambientIntensity;
	}

	virtual void SetDiffuseIntensity(CVector4f const& diffuseIntensity)
	{
		m_diffuseIntensity = diffuseIntensity;
	}

	virtual CVector4f const& GetDiffuseIntensity() const
	{
		return m_diffuseIntensity;
	}

	virtual void SetSpecularIntensity(CVector4f const& specularIntensity)
	{
		m_specularIntensity = specularIntensity;
	}

	virtual CVector4f const& GetSpecularIntensity() const
	{
		return m_specularIntensity;
	}

protected:
	CLightSourceImpl(CMatrix4d const& transform = CMatrix4d())
		: m_transform(transform)
	{
	}

private:
	CVector4f m_ambientIntensity;
	CVector4f m_diffuseIntensity;
	CVector4f m_specularIntensity;
	CMatrix4d m_transform;
};
