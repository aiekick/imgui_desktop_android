#include <src/frontend/frontend.h>

static const auto FLAGS = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_UnsavedDocument;

Frontend::Frontend(Backend& vBackend) : m_backendRef(vBackend) {}

const ImVec4& Frontend::getClearColor() {
    return m_clearColor;
}

bool Frontend::init() {
    if (m_buildThemes()) {
        return true;
    }
    return false;
}

void Frontend::unit() {

}

void Frontend::newFrame(const ez::ivec2& vDisplaySize) {
    m_displaySize = vDisplaySize;
}

void Frontend::update() {
    static bool show_label = false;
    static ImWidgets::InputText input_text;
    const auto& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::Begin("MainContent", nullptr, FLAGS);
    ImGui::BeginVertical("V", io.DisplaySize, 0.5f);
    ImGui::Spring(0.0f);
    ImGui::Text("Dear ImGui %s (Docking/Stack layout)", ImGui::GetVersion());
    ImGui::Spring(0.0f);
    ImGui::Text("%.1f ms/frame (%.1f fps)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::Spring(0.0f);
    ImGui::Text("Screen size : %.0f x %.0f", io.DisplaySize.x, io.DisplaySize.y);
    ImGui::Spring(0.35f);
    if (ImGui::ContrastedButton(show_label ? "Hide me" : "Show me")) {
        show_label = !show_label;
    }
    if (show_label) {
        ImGui::Spring(0.0f);
        input_text.DisplayInputText(io.DisplaySize.x * 0.8f, "", "");
        ImGui::Spring(0.0f);
        ImGui::Text("%s", input_text.GetConstCharPtrText());
    }
    ImGui::Spring(0.5f);
    ImGui::EndVertical();
    ImGui::End();
}
