#pragma once

#include "ILightSource_fwd.h"
#include "Matrix4.h"
#include "Matrix_fwd.h"
#include "SceneObject_fwd.h"
#include "Vector4.h"

class CRay;
class CIntersection;

/************************************************************************/
/* Класс "Сцена" - хранит объекты, предоставляет методы для нахождения  */
/* пересечений луча с объектами сцены                                   */
/************************************************************************/
class CScene
{
public:
	explicit CScene(CMatrix4d const& modelViewMatrix, CVector3d const& cameraPosition);

	// Задать цвет заднего фона сцены
	void SetBackdropColor(CVector4f const& backdropColor);

	/*
	Добавляем объект в сцену
	*/
	void AddObject(CSceneObjectPtr pSceneObject);

	/*
	Добавляем источник света в сцену
	*/
	void AddLightSource(ILightSourcePtr pLightSource);

	/*
	Возвращает количество источников света в сцене
	*/
	size_t GetLightsCount() const;

	/*
	Доступ к источнику света с указанным индексом
	*/
	ILightSource const& GetLight(size_t index) const;

	/*
	Возвращает цвет луча, столкнувшегося с объектами сцены
	*/
	CVector4f Shade(CRay const& ray) const;

	/*
	Трассирует луч вглубь сцены и возвращает информацию о первом столкновении луча с объектам сцены
	*/
	bool GetFirstHit(CRay const& ray, CIntersection& bestIntersection, CSceneObject const** ppIntersectionObject) const;

	CMatrix4d const& GetModelViewMatrix() const;

	CVector3d const& GetCameraPosition() const;

private:
	CMatrix4d const& m_modelViewMatrix;
	CVector3d m_cameraPosition;

	// Коллекция объектов сцены
	typedef std::vector<CSceneObjectPtr> SceneObjects;
	SceneObjects m_objects;

	typedef std::vector<ILightSourcePtr> LightSources;
	LightSources m_lightSources;

	// Цвет заднего фона сцены
	CVector4f m_backdropColor;
};
