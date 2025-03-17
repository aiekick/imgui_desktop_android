#include <src/backend/backend.h>

// we include the cpp just for embedded fonts
#include <src/res/robotoMedium.cpp>

#ifdef __ANDROID__
#else
#endif

bool Backend::init() {
    return true;
}

void Backend::unit() {
}

void Backend::initImGui(const std::string& vLocalStoragePath, float vFontSize, float vGlobalScale) {
    m_localStoragePath = vLocalStoragePath;
    m_fontSize = vFontSize * vGlobalScale;
    m_globalScale = vGlobalScale;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    UNUSED(io);
    io.ConfigFlags |= ImGuiConfigFlags_IsSRGB;         // Application is SRGB-aware.
#ifdef __ANDROID__
    io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;  // Application is using a touch screen instead of a mouse.
#else

#endif

    ImGui::StyleColorsDark();
}

void Backend::initFonts() {
    ImFontConfig font_cfg;
    font_cfg.SizePixels = m_fontSize;

    ImGuiIO& io = ImGui::GetIO();

    {  // main font
        auto fontPtr = io.Fonts->AddFontFromMemoryCompressedBase85TTF(FONT_ICON_BUFFER_NAME_RM, m_fontSize * m_globalScale);
        if (fontPtr == nullptr) {
            assert(0);  // failed to load font
        } else {
            fontPtr->Scale = 1.0f / m_globalScale;
        }
    }

    ImGui::GetStyle().ScaleAllSizes(m_globalScale);
}

void Backend::newFrame(const ez::ivec2& vDisplaySize) {
    ImGui::CustomStyle::ResetCustomId();
    ImGui::NewFrame();
}

void Backend::update() {}

void Backend::unitImGui() {
    ImGui::DestroyContext();
}
