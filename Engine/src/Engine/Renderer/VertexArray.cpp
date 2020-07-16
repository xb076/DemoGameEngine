
#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {

	VertexArray* VertexArray::Create()
	{
		VertexArray* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::OpenGL:
			ret = new OpenGLVertexArray();
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}



}



