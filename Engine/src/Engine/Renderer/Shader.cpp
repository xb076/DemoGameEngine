

#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Engine {

	Engine::Ref<Shader> Shader::Create(const std::string & filepath)
	{
		Ref<Shader> ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = std::make_shared<OpenGLShader>(filepath);
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}
	
	Ref<Shader> Shader::Create(const std::string& name, const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		Ref<Shader> ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}



	void ShaderLibrary::Add(const std::string& name, const Ref<Shader> shader)
	{
		ENGINE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader> shader)
	{
		Add(shader->GetName(), shader);
	}

	Engine::Ref<Engine::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Engine::Ref<Engine::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Engine::Ref<Engine::Shader> ShaderLibrary::Get(const std::string& name)
	{
		ENGINE_CORE_ASSERT(Exists(name), "Shader already exists!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}










