#pragma once
#include <DirectXMath.h>
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Lights.h"
#include "DataStructs.h"
#include "FirstPersonController.h"



class Scene
{
public:
	Scene(FirstPersonController* p_fpc, ID3D11Device* p_device, ID3D11DeviceContext* p_context);
	~Scene();

	/**
	* Render passes scene data to the vertex & pixel shaders as needed, then
	* tells DirectX to draw it
	*
	* @param context   - DirectX context (needed for DrawIndexed())
	* @param p_indices - All indices of materials, lights, etc. in the scene
	* @param p_dlights - List of directional lights in the scene
	* @param p_plights - List of point lights in the scene
	* @param p_slights - List of spot lights in the scene
	*/
	void Render(ID3D11DeviceContext* context,
				std::vector<uint> p_indices,
				std::vector<uint> p_dlights,
				std::vector<uint> p_plights,
				std::vector<uint> p_slights);


	void RenderShadowMaps(ID3D11DeviceContext* context);
	/**
	* CreateObject takes in a mesh and material, creates the appropriate world
	* & collider data, and creates an "object" with them (pushes them to the
	* correct lists).
	*
	* @param p_mesh     - The object's associated mesh
	* @param p_material - The object's associated material
	* @return uint      - The index of the last mesh in the list
	*/
	uint CreateObject(Mesh* p_mesh, Material* p_material);


	//  --  Accessors   --

	/**
	* SetObjectMaterial pushes the provided material onto the material list at
	* the given index. Internally handles reference count adjustment.
	*
	* @param p_index - index to push to in material list
	* @param p_material - material to push
	*/
	void SetObjectMaterial(uint p_index, Material* p_material);

	/**
	* SetObjectMesh pushes the provided mesh onto the mesh list at
	* the given index. Internally handles reference count adjustment.
	*
	* @param p_index    - index to push to in mesh list
	* @param p_mesh     - mesh to push
	*/
	void SetObjectMesh(uint p_index, Mesh* p_mesh);

	/**
	* SetObjectPosition updates the object at the given index with the
	* provided position vector.
	*
	* @param p_index    - index of object world data
	* @param p_position - new object position
	*/
	void SetObjectPosition(uint p_index, DirectX::XMFLOAT3 p_position) { m_worldDatas[p_index].m_position = p_position; }

	/**
	* SetObjectOrientation updates the object at the given index with the
	* provided orientation vector.
	*
	* @param p_index    - index of object world data
	* @param p_mesh     - new object orientation
	*/
	void SetObjectOrientation(uint p_index, DirectX::XMFLOAT3 p_orientation) { m_worldDatas[p_index].m_orientation = p_orientation; }

	/**
	* SetObjectMesh pushes the provided mesh onto the mesh list at
	* the given index. Internally handles reference count adjustment.
	*
	* @param p_index    - index to push to in material list
	* @param p_mesh     - mesh to push
	*/
	void SetObjectScale(uint p_index, float p_scale) { m_worldDatas[p_index].m_scale = p_scale; }

    void SetObjectCollider(uint p_index);

    void SetDoors(std::vector<Door> p_doors) { m_doors = p_doors; }

    void SetName(std::string p_name) { m_name = p_name; }
    std::string GetName() { return m_name; }

    /**
    * Returns whether or not FPC is within certain distance of door
    *
    * @param collisionDistance  - The distance at which FPC and the door are considered to be "colliding"
    * @return int   - index of door FPC is "colliding" with, or -1 if no such
    *  collision exists
    */
    int CollidingWithDoor(float collisionDistance);

	//  --  Getters --
	DirectX::XMFLOAT3 GetObjectPosition(uint p_index)		{ return m_worldDatas[p_index].m_position; }
	DirectX::XMFLOAT3 GetObjectOrientation(uint p_index)	{ return m_worldDatas[p_index].m_orientation; }
	DirectX::XMFLOAT4X4 GetObjectWorld(uint p_index)		{ return m_worldDatas[p_index].GetWorld(); }
	float GetObjectScale(uint p_index)						{ return m_worldDatas[p_index].m_scale; }
    // Terrible naming. . .
    Door GetDoor(uint p_index)                              { return m_doors[p_index]; }
    std::vector<Door> GetDoors()                            { return m_doors; }
    Collider GetObjectCollider(uint p_index)                { return m_colliders[p_index]; }
    std::vector<Collider> GetColliders()                    { return m_colliders; }


	// Movement
	void MoveObject(uint p_index, DirectX::XMFLOAT3 p_moveVector);
	void RotateObject(uint p_index, DirectX::XMFLOAT3 p_axis, float p_rad);
	void Scale(uint p_index, float p_scale);


	// Light functions, this could be re-architectured at a later date to be cleaner
	uint AddDirectionalLight(DirectionalLight p_dlight);
	uint AddSpotLight(SpotLight p_slight);
	uint AddPointLight(PointLight p_plight);

private:
	std::vector<Mesh*> m_meshList;          // Holds meshes
	std::vector<Material*> m_materialList;  // Holds materials
	std::vector<Collider> m_colliders;      // Holds bounding boxes, etc
	std::vector<WorldData> m_worldDatas;    // Holds position, orientation, scale, velocity, etc..
    std::vector<Door> m_doors;

											// Three separate lists for lights.. for now
	std::vector<DirectionalLight> m_dlightList;
	std::vector<SpotLight> m_slightList;
	std::vector<PointLight> m_plightList;

	//shadow stuff
	std::vector<DirectX::XMFLOAT4X4> m_dlightShadowViewList;
	std::vector<DirectX::XMFLOAT4X4> m_dlightShadowProjectionList;
	std::vector<ID3D11ShaderResourceView*> m_dlightSRVList;
	std::vector<ID3D11DepthStencilView*> m_dlightDSVList;
	ID3D11SamplerState* m_shadowSampler;
	ID3D11RasterizerState* m_shadowRasterizer;
	int m_shadowMapSize;
	SimpleVertexShader* m_shadowVS;

    std::string m_name;

	FirstPersonController* m_fpc;

	ID3D11Device* m_device;
};