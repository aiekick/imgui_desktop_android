#include <src/frontend/frontend.h>

const ImVec4& Frontend::getClearColor() {
    return m_clearColor;
}

void Frontend::newFrame(const ez::ivec2& vDisplaySize) {
    m_displaySize = vDisplaySize;
}

void Frontend::update() {
    static const auto FLAGS = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_UnsavedDocument;
    const auto& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("MainContent", nullptr, FLAGS);  // Create a window called "Hello, world!" and append into it.

    ImGui::Text("Display Size : %i x %i", m_displaySize.x, m_displaySize.y);

    ImGui::Button("HELLO");

    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

    ImGui::End();
}
