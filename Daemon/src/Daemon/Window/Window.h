#pragma once

#include "Daemon/Core.h"

#include <string>
#include <memory>

namespace dmn
{
	enum class EWindowMode
	{
		Windowed, BorderlessWindowed, FullscreenWindowed, Fullscreen
	};

	struct WindowCreateInfo
	{
		int width;
		int height;
		std::string title;
		EWindowMode windowMode;
	};

	class DMN_API Window
	{
	public:
		virtual ~Window() {};

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;

		virtual void update() const = 0;

		static std::unique_ptr<Window> create(const WindowCreateInfo& windowCreateInfo);
	};
}
