#include "stdafx.h"
#include "SimpleLightShader.h"
#include "ILightSource.h"
#include "Scene.h"
#include "ShadeContext.h"
#include "Vector4.h"
#include "VectorMath.h"

CSimpleLightShader::CSimpleLightShader(CSimpleMaterial const& material)
	: m_material(material)
{
}

/*
Запоминаем параметры материала, связанного с шейдером
*/
void CSimpleLightShader::SetMaterial(CSimpleMaterial const& material)
{
	m_material = material;
}

CVector4f CSimpleLightShader::Shade(CShadeContext const& shadeContext) const
{
	/*
	Получаем сцену из контекста закрашивания для того, чтобы вычислить вклад
	каждого из источников света в освещенность обрабатываемой точки
	*/
	CScene const& scene = shadeContext.GetScene();

	// Результирующий цвет
	CVector4f shadedColor;

	const size_t numLights = scene.GetLightsCount();

	// Пробегаемся по всем источникам света в сцене
	for (size_t i = 0; i < numLights; ++i)
	{
		ILightSource const& light = scene.GetLight(i);
		CVector3d lightDirection = light.GetDirectionFromPoint(shadeContext.GetSurfacePoint());
		CVector3d const& n = shadeContext.GetSurfaceNormal();

		double lightIntensity = light.GetIntensityInDirection(-lightDirection);

		// Вычисляем скалярное произведение нормали и орт-вектора направления на источник света
		double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);

		// Модель освещения Фонга: https://habr.com/ru/articles/441862/

		CVector3d reflectDirection = Reflect(-lightDirection, n);
		CVector3d viewDirection = Normalize(-(scene.GetModelViewMatrix() * CVector4d(scene.GetCameraPosition(), 1)));
		double spec = std::pow(Max(Dot(viewDirection, reflectDirection), 0.0), 256);

		CVector4f ambientColor = light.GetAmbientIntensity() * m_material.GetAmbientColor() * 0.1;
		CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();
		CVector4f specularColor = light.GetSpecularIntensity() * m_material.GetSpecularColor() * spec * 1;

		shadedColor = ambientColor + diffuseColor + specularColor;
	}

	// Возвращаем результирующий цвет точки
	return shadedColor;
}