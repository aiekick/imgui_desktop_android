// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define IMGUI_IMPL_API
#include <imguipack/imguipack.h>
#include <3rdparty/imgui_docking/backends/imgui_impl_opengl3.h>
#include <3rdparty/imgui_docking/backends/imgui_impl_glfw.h>

#include <src/backend/backend.h>
#include <src/frontend/frontend.h>

#include <ezlibs/ezApp.hpp>
#include <ezlibs/ezTools.hpp>

#include <stdio.h>
#include <clocale>

// resolution zenfone10
#define BASE_WIDTH 1080
#define BASE_HEIGHT 2286

// scale for desktop app
#define BASE_SCALE 0.4

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int vArgc, char** vArgv) {
    ez::App app(vArgc, vArgv);

    auto loc = std::setlocale(LC_ALL, ".UTF8");
    if (!loc) {
        printf("setlocale fail to apply with this compiler. it seems the unicode will be NOK\n");
    }

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(BASE_WIDTH * BASE_SCALE, BASE_HEIGHT * BASE_SCALE, "StockTrend desktop", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    if (gladLoadGL() == 0) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return false;
    }

    Backend backend;
    if (!backend.init()) {
        return false;
    }

    Frontend frontend(backend);

    backend.initImGui(app.getAppPath(), 20.0f, 1.33f);
    if (!frontend.init()) {
        return false;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    backend.initFonts();

    ez::ivec2 display_size;

    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        glfwGetFramebufferSize(window, &display_size.x, &display_size.y);

        backend.newFrame(display_size);
        frontend.newFrame(display_size);

        backend.update();
        frontend.update();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, display_size.x, display_size.y);
        glClearColor(  //
            frontend.getClearColor().x * frontend.getClearColor().w,
            frontend.getClearColor().y * frontend.getClearColor().w,
            frontend.getClearColor().z * frontend.getClearColor().w,
            frontend.getClearColor().w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    frontend.unit();
    backend.unitImGui();
    backend.unit();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
