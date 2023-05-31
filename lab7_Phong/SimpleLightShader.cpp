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
		// Получаем источник света
		ILightSource const& light = scene.GetLight(i);

		// Вычисляем вектор направления на источник света из текущей точке
		CVector3d lightDirection = light.GetDirectionFromPoint(shadeContext.GetSurfacePoint());

		// Вычисляем интенсивность света в направлении от источника к текущей точке
		double lightIntensity = light.GetIntensityInDirection(-lightDirection);

		// Получаем нормаль к поверхности в обрабатываемой точке
		CVector3d const& n = shadeContext.GetSurfaceNormal();

		// Вычисляем скалярное произведение нормали и орт-вектора направления на источник света
		double nDotL = Max(Dot(n, Normalize(lightDirection)), 0.0);

		CMatrix4d modelView;
		modelView.LoadLookAtRH(
			0, 3, 7,
			0, 0, 0,
			0, 1, 0);
		CVector3d reflectDirection = Reflect(-lightDirection, n);
		CVector3d viewDirection = -(modelView * CVector4d(shadeContext.GetSurfacePoint(), 1));
		double spec = std::pow(Max(Dot(viewDirection, reflectDirection), 0.0), 32);

		CVector4f ambientColor = light.GetAmbientIntensity() * m_material.GetAmbientColor() * 0.1;
		CVector4f diffuseColor = static_cast<float>(nDotL * lightIntensity) * light.GetDiffuseIntensity() * m_material.GetDiffuseColor();
		CVector4f specularColor = CVector4f(0.3f, 0.3f, 0.3f, 0.5f) * spec * 0.3f;

		shadedColor = ambientColor + diffuseColor + specularColor;
	}

	// Возвращаем результирующий цвет точки
	return shadedColor;
}