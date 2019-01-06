#include "pch.h"
#include "Application.h"

#include "Window/Window.h"

#include "Daemon/Events/EventDispatcher.h"
#include "Daemon/Events/KeyboardEvents.h"
#include "Daemon/Events/MouseEvents.h"

namespace dmn
{
	Application::Application()
	{
		WindowCreateInfo windowCreateInfo = { 0 };
		windowCreateInfo.width = 720;
		windowCreateInfo.height = 720;
		windowCreateInfo.title = "Daemon Engine";
		windowCreateInfo.windowMode = EWindowMode::Windowed;
		m_window = Window::create(windowCreateInfo);
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		m_running = true;

		int blueStep = 0;
		constexpr int maxBlueStep = 25;

		double mouseX = 0, mouseY = 0;

		EventDispatcher::getInstance().addListener<WindowCloseEvent>(BIND_EVENT_FN(Application::handleWindowCloseEvent));
		EventDispatcher::getInstance().addListener<WindowResizedEvent>([](WindowResizedEvent& e)
		{
			std::printf("Window was resized: (%d, %d)\n", e.getWidth(), e.getHeight());
		});
		EventDispatcher::getInstance().addListener<KeyPressedEvent>([&blueStep, maxBlueStep](KeyPressedEvent& e)
		{
			/*if (!e.isRepeated())
			{
				if (e.getKey() == GLFW_KEY_0)
					blueStep = 10;
				else if (e.getKey() >= GLFW_KEY_1 && e.getKey() <= GLFW_KEY_9)
					blueStep = e.getKey() - GLFW_KEY_1;
			}*/
			if (e.getKey() == GLFW_KEY_UP && blueStep < maxBlueStep)
				blueStep++;
			else if (e.getKey() == GLFW_KEY_DOWN && blueStep > 0)
				blueStep--;
		});
		EventDispatcher::getInstance().addListener<MouseMovedEvent>([&mouseX, &mouseY](MouseMovedEvent e)
		{
			mouseX = e.getX();
			mouseY = e.getY();
		});
		EventDispatcher::getInstance().addListener<MouseScrolledEvent>([&blueStep, maxBlueStep](MouseScrolledEvent e)
		{
			blueStep += (int)glm::round(e.getYOffset());
			blueStep = glm::clamp(blueStep, 0, maxBlueStep);
		});

		while (m_running)
		{
			float r = (float)(mouseX / m_window->getWidth());
			float g = (float)(mouseY / m_window->getHeight());
			float b = (float)blueStep / maxBlueStep;
			glClearColor(r, g, b, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->update();
		}
	}

	void Application::handleWindowCloseEvent(WindowCloseEvent& e)
	{
		std::printf("Shutting down application\n");
		m_running = false;
	}
}
