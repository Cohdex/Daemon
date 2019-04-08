#pragma once

#include "Daemon/Window/Window.h"

#include <GLFW/glfw3.h>

#include <string>

namespace dmn
{
	class GlfwWindowImpl : public Window
	{
	private:
		GLFWwindow* m_glfwWindow;
		int m_width;
		int m_height;
		std::string m_title;

		static void windowCloseCallback(GLFWwindow* glfwWindow);
		static void windowResizeCallback(GLFWwindow* glfwWindow, int width, int height);
		static void keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
		static void mousePosCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
		static void mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
		static void mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset);

	public:
		GlfwWindowImpl(const WindowCreateInfo& windowCreateInfo);
		virtual ~GlfwWindowImpl();

		virtual inline int getWidth() const override { return m_width; }
		virtual inline int getHeight() const override { return m_height; }

		virtual void update() const override;
	};
}
