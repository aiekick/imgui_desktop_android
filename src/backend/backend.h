#pragma once
#include <imguipack/imguipack.h>
#include <ezlibs/ezTools.hpp>
#include <string>

class Backend {
private:
    std::string m_localStoragePath;  // path of where to load/save files
    float m_fontSize{22.0f};
    float m_globalScale{1.0f};

public:
    void initImGui(const std::string& vLocalStoragePath, float vFontSize, float vGlobalScale);
	void initFonts();
    void newFrame(const ez::ivec2& vDisplaySize);
    void update();
    void unitImGui();
};
