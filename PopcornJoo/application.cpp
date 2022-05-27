#include "application.h"

#if defined(_WIN32)
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <spdlog/spdlog.h>
#include <chrono>

std::unique_ptr<grc::application> grc::application::shared = std::make_unique<grc::application>();

long long prevEscTime;
long long prevRenderTime;
void grc::application::keyboard(unsigned char key, int x, int y) const
{
    this->entryScene->keyboardEvent(key, x, y);

    //ESC 키가 눌러졌다면 프로그램 종료

    if (key == 27)
    {
        auto time = std::chrono::system_clock::now();
        auto mill = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();

        if (mill - prevEscTime < 300)
        {
            close();
        }
        prevEscTime = mill;
    }
}

void grc::application::mouse(int button, int state, int x, int y) const
{
    if (this->entryScene == nullptr)
    {
        spdlog::critical("Entry Controller Not Found");
        return;
    }
    else
    {
        this->entryScene->mouseEvent(button, state, x, y);
    }
}

void grc::application::mousePassive(int x, int y) const
{
    spdlog::info("[{}, {}]", x, y);
}

void grc::application::render() const
{
    if (this->entryScene == nullptr)
    {
        spdlog::critical("Entry Controller Not Found");
        return;
    }
    else
    {
        auto time = std::chrono::system_clock::now();
        auto mill = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
        this->entryScene->render(mill - prevRenderTime);
        prevRenderTime = mill;
    }
}

grc::application::application()
{
    spdlog::info("OpenGL Initialize : [{}, {}], {}", size.width, size.height, title);
    int myArgc = 0;
    glutInit(&myArgc, nullptr); //GLUT 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
}

std::string grc::application::getTitle() const
{
    return this->title;
}

void grc::application::setTitle(const std::string title)
{
    this->title = title;
    glutSetWindowTitle(title.c_str());
}

void grc::application::run()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glutReshapeFunc(reshape);
    //glutSpecialFunc(grc::glKeyboard);

    glutKeyboardFunc(grc::glKeyboard);
    glutMouseFunc(grc::glMouse);
    glutDisplayFunc(grc::glDisplay);
    glutIdleFunc(grc::glDisplay);
    glutPassiveMotionFunc(grc::glMousePassive);
    glutTimerFunc(50, grc::glTimer, 0);

    glutMainLoop();
}

void grc::application::close() const
{
    glutDestroyWindow(glutGetWindow());

    if (this->closedEvent.has_value())
    {
        this->closedEvent.value()();
    }

    exit(0);
}

void grc::application::initialize(const grc::size size, const std::string title)
{
    this->size = size;
    this->title = title;
    glutInitWindowSize(500, 500);
    spdlog::info("OpenGL : run, [{}, {}, \"{}\"]", size.width, size.height, title);
    glutInitWindowSize(size.width, size.height); //윈도우의 width와 height
    glutCreateWindow(title.c_str());             //윈도우 생성
}

void grc::application::setSize(const grc::size size)
{
    this->size = size;
    glViewport(0, 0, size.width, size.height);
}

grc::size grc::application::getSize() const
{
    return this->size;
}
void grc::application::setScene(std::shared_ptr<grc::scene>&& scene) {
    this->entryScene = scene;
    glutPostRedisplay();
}


void grc::glDisplay()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //glClear에서 컬러 버퍼 지운 후 윈도우를 채울 색을 지정, 검은색
    glClear(GL_COLOR_BUFFER_BIT);         //컬러 버퍼를 지운다.
    glLoadIdentity();

    grc::application::shared->render();

    glutSwapBuffers();
}

void grc::glKeyboard(unsigned char key, int x, int y)
{
    grc::application::shared->keyboard(key, x, y);
}
void grc::glMouse(int button, int state, int x, int y)
{
    grc::application::shared->mouse(button, state, x, y);
}

void grc::glMousePassive(int x, int y)
{
    grc::application::shared->mousePassive(x, y);
}

void grc::glTimer(int value) {
    //grc::application::shared->timer(value);
    glutPostRedisplay();
    glutTimerFunc(50, grc::glTimer, value);
}