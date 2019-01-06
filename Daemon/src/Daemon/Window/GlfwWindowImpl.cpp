#include "pch.h"
#include "GlfwWindowImpl.h"

#include "Daemon/Events/EventDispatcher.h"
#include "Daemon/Events/WindowEvents.h"
#include "Daemon/Events/KeyboardEvents.h"
#include "Daemon/Events/MouseEvents.h"

#include <GLFW/glfw3.h>

namespace dmn
{
	std::unique_ptr<Window> Window::create(const WindowCreateInfo& windowCreateInfo)
	{
		return std::make_unique<GlfwWindowImpl>(windowCreateInfo);
	}

	static void glfw_error_callback(int error, const char* description)
	{
		std::printf("GLFW error (%d): %s\n", error, description);
	}

	static void glad_pre_callback(const char* name, void* funcptr, int len_args, ...)
	{
		while (glad_glGetError() != GL_NO_ERROR);
	}

	static void glad_post_callback(const char* name, void* funcptr, int len_args, ...)
	{
		GLenum error = glad_glGetError();
		if (error != GL_NO_ERROR)
		{
			std::printf("An error occurred when calling %s: ", name);
			do
			{
				std::printf("%d ", error);
			}
			while ((error = glad_glGetError()) != GL_NO_ERROR);

			std::printf("\n");
		}
	}

	GlfwWindowImpl::GlfwWindowImpl(const WindowCreateInfo& windowCreateInfo)
		: m_title(windowCreateInfo.title)
	{
		glfwSetErrorCallback(glfw_error_callback);

		std::printf("Creating window '%s' (%d, %d)\n", windowCreateInfo.title.c_str(), windowCreateInfo.width, windowCreateInfo.height);
		if (!glfwInit())
		{
			std::printf("Could not initialize GLFW!\n");
			throw 1;
		}

		m_glfwWindow = glfwCreateWindow(windowCreateInfo.width, windowCreateInfo.height, windowCreateInfo.title.c_str(), nullptr, nullptr);
		if (m_glfwWindow == nullptr)
		{
			std::printf("Could not create window!\n");
			throw 1;
		}
		glfwGetWindowSize(m_glfwWindow, &m_width, &m_height);

		glfwMakeContextCurrent(m_glfwWindow);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::printf("Could not initialize Glad!\n");
			throw 1;
		}
#ifdef GLAD_DEBUG
		glad_set_pre_callback(glad_pre_callback);
		glad_set_post_callback(glad_post_callback);
#endif

		glfwSetWindowUserPointer(m_glfwWindow, this);
		glfwSetWindowCloseCallback(m_glfwWindow, GlfwWindowImpl::windowCloseCallback);
		glfwSetWindowSizeCallback(m_glfwWindow, GlfwWindowImpl::windowResizeCallback);
		glfwSetKeyCallback(m_glfwWindow, GlfwWindowImpl::keyCallback);
		glfwSetCursorPosCallback(m_glfwWindow, GlfwWindowImpl::mousePosCallback);
		glfwSetMouseButtonCallback(m_glfwWindow, GlfwWindowImpl::mouseButtonCallback);
		glfwSetScrollCallback(m_glfwWindow, GlfwWindowImpl::mouseScrollCallback);
	}

	GlfwWindowImpl::~GlfwWindowImpl()
	{
		glfwDestroyWindow(m_glfwWindow);
	}

	void GlfwWindowImpl::update() const
	{
		glfwPollEvents();
		glfwSwapBuffers(m_glfwWindow);
	}

	void GlfwWindowImpl::windowCloseCallback(GLFWwindow* glfwWindow)
	{
		EventDispatcher::getInstance().dispatch(WindowCloseEvent());
	}

	void GlfwWindowImpl::windowResizeCallback(GLFWwindow* glfwWindow, int width, int height)
	{
		GlfwWindowImpl& myWindow = *(GlfwWindowImpl*)glfwGetWindowUserPointer(glfwWindow);
		myWindow.m_width = width;
		myWindow.m_height = height;
		glViewport(0, 0, width, height);
		EventDispatcher::getInstance().dispatch(WindowResizedEvent(width, height));
	}

	void GlfwWindowImpl::keyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			EventDispatcher::getInstance().dispatch(KeyPressedEvent(key, mods, action == GLFW_REPEAT));
		}
		else if (action == GLFW_RELEASE)
		{
			EventDispatcher::getInstance().dispatch(KeyReleasedEvent(key, mods));
		}
	}

	void GlfwWindowImpl::mousePosCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
	{
		EventDispatcher::getInstance().dispatch(MouseMovedEvent(xpos, ypos));
	}

	void GlfwWindowImpl::mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			EventDispatcher::getInstance().dispatch(MouseButtonPressedEvent(button, mods));
		}
		else if (action == GLFW_RELEASE)
		{
			EventDispatcher::getInstance().dispatch(MouseButtonReleasedEvent(button, mods));
		}
	}

	void GlfwWindowImpl::mouseScrollCallback(GLFWwindow* glfwWindow, double xoffset, double yoffset)
	{
		EventDispatcher::getInstance().dispatch(MouseScrolledEvent(xoffset, yoffset));
	}
}
