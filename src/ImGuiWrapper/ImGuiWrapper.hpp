#ifndef IMGUI_WRAPPER_H
#define IMGUI_WRAPPER_H

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>
#include <GLFW/glfw3.h>
#include <memory>

struct GLFWwindow;

static auto glfw_error_callback(int error, const char *description) -> void {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

class ImGuiWrapper
{
public:
    ImGuiWrapper() {
        m_window = nullptr;
        m_initialized = false;
        m_isDragging = false;
        m_dragOffsetX = 0.0;
        m_dragOffsetY = 0.0;
        m_titleBarHeight = 30.0f;
    }

    bool Init(const std::string& title, const int width, const int height) {
        if (m_initialized)
        {
            fprintf(stderr, "Warning: ImGui already initialized!\n");
            return false;
        }

        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW!\n");
            return false;
        }

        #ifdef __APPLE__
            const char* glsl_version = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #else
            const char* glsl_version = "#version 130";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        #endif

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

        m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (m_window == nullptr)
        {
            fprintf(stderr, "Failed to create window!\n");
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);
        glfwSwapInterval(1); // vsync

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        m_initialized = true;
        return true;
    }

    void Shutdown() {
        if (!m_initialized)
            return;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        if (m_window)
        {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }

        glfwTerminate();
        m_initialized = false;
    }

    bool ShouldClose() { return m_window ? glfwWindowShouldClose(m_window) : true; }

    void BeginFrame()
    {
        if (!m_initialized)
            return;

        glfwPollEvents();

        HandleWindowDragging();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void EndFrame()
    {
        if (!m_initialized)
            return;

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_window);
    }


    void SetTitleBarHeight(float height) { m_titleBarHeight = height; }
    float GetTitleBarHeight() const { return m_titleBarHeight; }

    GLFWwindow* GetWindow() const { return m_window; }

    GLFWwindow* m_window;
    bool m_initialized;

private:
    float m_clearColor[4] = {0.45f, 0.55f, 0.60f, 1.00f};
    bool m_isDragging;
    double m_dragOffsetX;
    double m_dragOffsetY;
    float m_titleBarHeight;

    void HandleWindowDragging() {
        if (!m_window)
            return;

        double mouseX, mouseY;
        glfwGetCursorPos(m_window, &mouseX, &mouseY);

        int mouseButton = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);

        bool inTitleBar = (mouseY >= 0 && mouseY <= m_titleBarHeight);

        if (mouseButton == GLFW_PRESS && inTitleBar && !m_isDragging) {
            m_isDragging = true;
            m_dragOffsetX = mouseX;
            m_dragOffsetY = mouseY;
        }

        if (m_isDragging) {
            if (mouseButton == GLFW_PRESS) {
                int windowX, windowY;
                glfwGetWindowPos(m_window, &windowX, &windowY);

                int newX = windowX + static_cast<int>(mouseX - m_dragOffsetX);
                int newY = windowY + static_cast<int>(mouseY - m_dragOffsetY);

                glfwSetWindowPos(m_window, newX, newY);
            } else {
                m_isDragging = false;
            }
        }
    }
};

extern std::unique_ptr<ImGuiWrapper> wrapper;

#endif