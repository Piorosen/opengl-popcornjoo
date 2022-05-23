#pragma once
#define GL_SILENCE_DEPRECATION
#define MATH_PI 3.14159265359

#include <string>
#include <memory>
#include <optional>
#include <functional>

#include "size.h"
#include "scene.h"

namespace grc
{
    class application final
    {
    private:
        grc::size size = { 500, 500 };
        std::string title = "OpenGL : Test";

        // 현재 작업중인 VC임
        std::shared_ptr<grc::scene> entryScene = nullptr;

    public:
        static std::unique_ptr<grc::application> shared;

        std::optional<std::function<void()>> closedEvent;

        void keyboard(unsigned char key, int x, int y) const;
        void mouse(int button, int state, int x, int y) const;
        void render() const;

        application();

        void run();
        void close() const;

        // 추후 Scene 설정 기능임
        void setScene(std::shared_ptr<grc::scene>&& scene);

        void initialize(const grc::size size, const std::string title);

        std::string getTitle() const;
        void setTitle(const std::string title);

        grc::size getSize() const;
        void setSize(const grc::size size);

    protected:
    };

    void glKeyboard(unsigned char key, int x, int y);
    void glMouse(int button, int state, int x, int y);
    void glDisplay();
}