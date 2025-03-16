#include <src/backend/backend.h>

void Backend::initImGui(const std::string& vLocalStoragePath, float vFontSize, float vGlobalScale) {
    m_localStoragePath = vLocalStoragePath;
    m_fontSize = vFontSize;
    m_globalScale = vGlobalScale;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    UNUSED(io);
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui::GetStyle().ScaleAllSizes(m_globalScale);
}

void Backend::initFonts() {
    ImFontConfig font_cfg;
    font_cfg.SizePixels = m_fontSize;

    ImGuiIO& io = ImGui::GetIO();

#ifndef PLATFORM_ANDROID
    io.Fonts->AddFontDefault(&font_cfg);
    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and
    // quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which
    // ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != nullptr);
#else
    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and
    // quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which
    // ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Android: The TTF files have to be placed into the assets/ directory (android/app/src/main/assets), we use our GetAssetData() helper to retrieve them.

    // We load the default font with increased size to improve readability on many devices with "high" DPI.
    // FIXME: Put some effort into DPI awareness.
    // Important: when calling AddFontFromMemoryTTF(), ownership of font_data is transferred by Dear ImGui by default (deleted is handled by Dear ImGui), unless we set
    // FontDataOwnedByAtlas=false in ImFontConfig
    io.Fonts->AddFontDefault(&font_cfg);
    // void* font_data;
    // int font_data_size;
    // ImFont* font;
    // font_data_size = GetAssetData("segoeui.ttf", &font_data);
    // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
    // IM_ASSERT(font != nullptr);
    // font_data_size = GetAssetData("DroidSans.ttf", &font_data);
    // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
    // IM_ASSERT(font != nullptr);
    // font_data_size = GetAssetData("Roboto-Medium.ttf", &font_data);
    // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 16.0f);
    // IM_ASSERT(font != nullptr);
    // font_data_size = GetAssetData("Cousine-Regular.ttf", &font_data);
    // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 15.0f);
    // IM_ASSERT(font != nullptr);
    // font_data_size = GetAssetData("ArialUni.ttf", &font_data);
    // font = io.Fonts->AddFontFromMemoryTTF(font_data, font_data_size, 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != nullptr);

#endif
}

void Backend::newFrame(const ez::ivec2& vDisplaySize) {
    ImGui::NewFrame();
}

void Backend::update() {}

void Backend::unitImGui() {
    ImGui::DestroyContext();
}
