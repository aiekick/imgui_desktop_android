#pragma once

#include <imguipack/imguipack.h>
#include <ezlibs/ezTools.hpp>
#include <src/backend/backend.h>

class Frontend {
private:
    Backend& m_backendRef;
    float m_navBarHeight{80.0f};
    float m_windowBottomOffset{20.0f};
    bool m_showDemoWindow{false};
    ImVec4 m_clearColor{0.15f, 0.16f, 0.17f, 1.0f};
    ez::ivec2 m_displaySize;

public:
    explicit Frontend(Backend& vBackend);
    Backend& getBackendRef() { return m_backendRef; }
    const ImVec4& getClearColor();
    bool init();
    void unit();
    void newFrame(const ez::ivec2& vDisplaySize);
    void update();

private:
    bool m_buildThemes();
};
