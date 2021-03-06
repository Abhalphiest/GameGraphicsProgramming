#pragma once

#include"../headers/SimpleShader.h"
#include "WICTextureLoader.h" // From DirectX Tool Kit

class Material
{
public:
	/**
	* GetInstance increases the current reference count for this material
	*/
	void GetInstance() { m_references++; }

	/**
	* RemoveInstance reduces the current referent count for this material
	* and deletes the material if there are no more references.
	*/
	void RemoveInstance() { m_references--; if (m_references == 0) delete this; }

	Material(SimpleVertexShader* p_vShader, SimplePixelShader* p_pShader);
	Material(SimpleVertexShader* p_vShader,
				SimplePixelShader* p_pShader,
				ID3D11ShaderResourceView* p_srv,
				ID3D11ShaderResourceView* p_msrv,
				ID3D11ShaderResourceView* p_specsrv,
				ID3D11ShaderResourceView* p_nsrv,
				ID3D11SamplerState* p_s);

	SimpleVertexShader* GetVertexShader()	{ return m_vertexShader; }
	SimplePixelShader* GetPixelShader()		{ return m_pixelShader; }
	ID3D11ShaderResourceView* GetSRV()		{ return m_srv; }
	ID3D11ShaderResourceView* GetMSRV()		{ return m_multiplysrv; }
	ID3D11ShaderResourceView* GetNSRV()		{ return m_nsrv; }
	ID3D11ShaderResourceView* GetSpecSRV()	{ return m_specsrv; }
	ID3D11SamplerState* GetSampleState()	{ return m_sState; }

	void SetSRV(ID3D11ShaderResourceView* p_srv)			{ m_srv = p_srv; }
	void SetMSRV(ID3D11ShaderResourceView* p_msrv)			{ m_multiplysrv = p_msrv; }
	void SetSpecSRV(ID3D11ShaderResourceView* p_specsrv)	{ m_specsrv = p_specsrv; }
	void SetNSRV(ID3D11ShaderResourceView* p_nsrv)			{ m_nsrv = p_nsrv; }

private:
	~Material() { m_vertexShader->RemoveInstance(); m_pixelShader->RemoveInstance(); }
	SimpleVertexShader* m_vertexShader;
	SimplePixelShader* m_pixelShader;
	int m_references;
	ID3D11ShaderResourceView* m_srv = nullptr,          // Diffuse texture
							*m_multiplysrv = nullptr,   // Multiply texture
							*m_specsrv = nullptr,       // Specular map
							*m_nsrv = nullptr;          // Normal map

	ID3D11SamplerState* m_sState = nullptr;
};

