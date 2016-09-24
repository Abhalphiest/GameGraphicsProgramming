#pragma once

#include"../SimpleShader.h"
#include "WICTextureLoader.h" // From DirectX Tool Kit

class Material
{
public:
	

	void GetInstance() { m_references++; }
	void RemoveInstance() { m_references--; if (m_references == 0) delete this; }

	Material(SimpleVertexShader* p_vShader, SimplePixelShader* p_pShader);
	Material(SimpleVertexShader* p_vShader, SimplePixelShader* p_pShader,
		ID3D11ShaderResourceView* p_srv, ID3D11SamplerState* p_s);
	SimpleVertexShader* GetVertexShader() { return m_vertexShader; }
	SimplePixelShader* GetPixelShader() { return m_pixelShader; }
	ID3D11ShaderResourceView* GetSRV() { return m_srv; }
	ID3D11SamplerState* GetSampleState() { return m_sState; }
private:
	//will be changing simple shader to have a reference system when I have time, until then
	//it's more convenient to handle the shader freeing in Game.cpp
	~Material() { //m_vertexShader->RemoveInstance(); m_pixelShader->RemoveInstance();
	}
	SimpleVertexShader* m_vertexShader;
	SimplePixelShader* m_pixelShader;
	int m_references;
	ID3D11ShaderResourceView* m_srv;
	ID3D11SamplerState* m_sState;
	DirectX::XMFLOAT4 m_surfaceColor;
};

