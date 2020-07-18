
#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {

	Ref<VertexArray> VertexArray::Create()
	{
		Ref<VertexArray> ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = std::make_shared<OpenGLVertexArray>();
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}



}



