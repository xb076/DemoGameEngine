#pragma once

#include "Engine/Renderer/Buffer.h"

namespace Engine {

	/////////////////////////////////////////////////////////////
	// VertexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

	private:
		uint32_t m_RendererID;
		
	};

	/////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	};

}


