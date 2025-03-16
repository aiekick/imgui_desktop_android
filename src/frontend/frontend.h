#pragma once

#include <imguipack/imguipack.h>
#include <ezlibs/ezTools.hpp>

class Frontend {
private:
	bool m_showDemoWindow{ false };
	ImVec4 m_clearColor{ 0.45f, 0.55f, 0.60f, 1.00f };
    ez::ivec2 m_displaySize;

public:
    const ImVec4& getClearColor();
    void newFrame(const ez::ivec2& vDisplaySize);
    void update();
};
