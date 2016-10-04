#pragma once
#include <DirectXMath.h>
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Entity.h"
#include "Lights.h"
#include "DataStructs.h"
#include "FirstPersonController.h"


class Scene
{
public:
	Scene(FirstPersonController* p_fpc);
	~Scene();
	void Render(ID3D11DeviceContext* context, std::vector<uint> p_indices,
		std::vector<uint> p_dlights, std::vector<uint> p_plights, std::vector<uint> p_slights);


	//object "constructor"
	uint CreateObject(Mesh* p_mesh, Material* p_material);

	//accessors
	void SetObjectMaterial(uint p_index, Material* p_material);
	void SetObjectMesh(uint p_index, Mesh* p_mesh);
	void SetObjectPosition(uint p_index, DirectX::XMFLOAT3 p_position) { m_worldDatas[p_index].m_position = p_position; }
	void SetObjectOrientation(uint p_index, DirectX::XMFLOAT3 p_orientation) { m_worldDatas[p_index].m_orientation = p_orientation; }
	void SetObjectScale(uint p_index, float p_scale) { m_worldDatas[p_index].m_scale = p_scale; }
	//need getters


	//Light functions, this could be rearchitectured at a later date to be
	//cleaner
	uint AddDirectionalLight(DirectionalLight* p_dlight);
	uint AddSpotLight(SpotLight* p_slight);
	uint AddPointLight(PointLight* p_plight);

	//need getters and setters for lights still

	
private:
	std::vector<Mesh*> m_meshList;  //holds meshes
	std::vector<Material*> m_materialList; //holds materials
	std::vector<Collider> m_colliders;  //hold bounding boxes, etc
	std::vector<WorldData> m_worldDatas; //to hold position, orientation, scale, velocity, etc..

	std::vector<DirectionalLight*> m_dlightList; //three separate lists for lights.. for now
	std::vector<SpotLight*> m_slightList;
	std::vector<PointLight*> m_plightList;

	FirstPersonController* m_fpc;


};
