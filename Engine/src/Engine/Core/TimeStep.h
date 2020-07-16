#pragma once


namespace Engine {

	class TimeStep
	{
	public:
		TimeStep(float time = 0.f) :m_Time(time) {}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.f; }
	private:
		float m_Time ;



	};


}

