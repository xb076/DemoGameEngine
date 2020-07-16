
#include "Engine.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -.9f, .9f), m_CameraPosition(0.f), m_SquarePosition(0.f)
	{

		m_VertexArray.reset(Engine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Engine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

		Engine::BufferLayout layout = {
			{ Engine::ShaderDataType::Float3, "a_Position" },
			{ Engine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Engine::IndexBuffer> indexBuffer;
		indexBuffer.reset(Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Engine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Engine::VertexBuffer> squareVB;
		squareVB.reset(Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Engine::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Engine::IndexBuffer> squareIB;
		squareIB.reset(Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position *0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Engine::Shader(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_BlueShader.reset(new Engine::Shader(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(Engine::TimeStep ts) override
	{
		//LOG_APP_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliSeconds());

		if (Engine::Input::IsKeyPressed(ENGINE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts.GetSeconds();
		else if (Engine::Input::IsKeyPressed(ENGINE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts.GetSeconds();

		if (Engine::Input::IsKeyPressed(ENGINE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts.GetSeconds();
		else if (Engine::Input::IsKeyPressed(ENGINE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts.GetSeconds();

		if (Engine::Input::IsKeyPressed(ENGINE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts.GetSeconds();
		else if (Engine::Input::IsKeyPressed(ENGINE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts.GetSeconds();

		if (Engine::Input::IsKeyPressed(ENGINE_KEY_J))
			m_SquarePosition.x += m_SquareMoveSpeed * ts.GetSeconds();
		else if (Engine::Input::IsKeyPressed(ENGINE_KEY_L))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts.GetSeconds();

		if (Engine::Input::IsKeyPressed(ENGINE_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts.GetSeconds();
		else if (Engine::Input::IsKeyPressed(ENGINE_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts.GetSeconds();

		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Engine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Engine::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				glm::vec3 pos(i * 0.11f, j*0.11f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (i & 0x1)
					m_BlueShader->UploadUniformFloat4("u_Color", blueColor);
				else
					m_BlueShader->UploadUniformFloat4("u_Color", redColor);
				Engine::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}
		
		Engine::Renderer::Submit(m_Shader, m_VertexArray);

		Engine::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Engine::Event& event) override
	{
		
	}

private:
	std::shared_ptr<Engine::Shader> m_Shader;
	std::shared_ptr<Engine::VertexArray> m_VertexArray;

	std::shared_ptr<Engine::Shader> m_BlueShader;
	std::shared_ptr<Engine::VertexArray> m_SquareVA;

	Engine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.f;
	float m_CameraRotation = 0.f;
	float m_CameraRotationSpeed = 90.f;
	
	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;

};


class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{}

};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}


