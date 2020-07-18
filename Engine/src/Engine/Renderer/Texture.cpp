#pragma once

#include "pch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Engine {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		Ref<OpenGLTexture2D> ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			//ret.reset(new OpenGLTexture2D(path));
			ret = CreateRef<OpenGLTexture2D>(path);
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		Ref<OpenGLTexture2D> ret = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			break;
		case RendererAPI::API::OpenGL:
			ret = CreateRef<OpenGLTexture2D>(width, height);
			break;
		default:
			ENGINE_CORE_ASSERT(false, "Unkown RenderAPI!");
			break;
		}
		return ret;
	}

}
