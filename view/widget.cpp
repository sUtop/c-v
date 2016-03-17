#include "widget.h"
#include "view.h" // Общая память для 2-х потоков

Widget::Widget(QWidget *parent)
: QGLWidget(parent)
{
    resize(m_width, m_height);
    connect(ms, SIGNAL(pixelsFull()), this, SLOT(updateGL()));

}

void Widget::initializeGL()
{
    m_lastTime = std::time(NULL);
    m_frames = 0;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint) nWidth, (GLint) nHeight);
}

void Widget::paintGL() // рисование
{
    // Рассчет фпс
    std::time_t result = std::time(NULL);
    if(result - m_lastTime > 1) {
        std::cout << "Paint Gl " << (int) m_frames << " FPS \n";
        m_frames = 0;
        m_lastTime = result;
    }
    else ++m_frames;

    // Отображение
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColorMask(true, true, true, false);
    GLenum format = GL_RGBA,
            type = GL_UNSIGNED_BYTE;

    glDrawPixels(m_width, m_height, format, type, pixels);
    glColorMask(true, true, true, true);

}
