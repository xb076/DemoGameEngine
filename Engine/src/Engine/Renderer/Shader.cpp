

#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Engine {

	Engine::Shader* Shader::Create(const std::string & filepath)
	{
		Shader* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = new OpenGLShader(filepath);
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}
	
	Shader* Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		Shader* ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = new OpenGLShader(vertexSrc, fragmentSrc);
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}


	

}










