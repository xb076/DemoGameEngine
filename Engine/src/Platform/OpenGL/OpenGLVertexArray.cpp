#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Engine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		GLenum ret = 0;
		switch (type)
		{
			case Engine::ShaderDataType::Float:			ret = GL_FLOAT; break;
			case Engine::ShaderDataType::Float2:		ret = GL_FLOAT; break;
			case Engine::ShaderDataType::Float3:		ret = GL_FLOAT; break;
			case Engine::ShaderDataType::Float4:		ret = GL_FLOAT; break;
			case Engine::ShaderDataType::Mat3:			ret = GL_FLOAT; break;
			case Engine::ShaderDataType::Mat4:			ret = GL_FLOAT; break;
			case Engine::ShaderDataType::Int2:			ret = GL_INT; break;
			case Engine::ShaderDataType::Int3:			ret = GL_INT; break;
			case Engine::ShaderDataType::Int4:			ret = GL_INT; break;
			case Engine::ShaderDataType::Bool:			ret = GL_INT; break;
			default: ENGINE_CORE_ASSERT(false, "Unknown ShaderDataType!"); break;
		}
		return ret;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		ENGINE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();


		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index
				, element.GetComponentCount()
				, ShaderDataTypeToOpenGLBaseType(element.Type)
				, element.Normalized ? GL_TRUE : GL_FALSE
				, layout.GetStride()
				, (const void*)element.Offset
			);
			++index;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}

