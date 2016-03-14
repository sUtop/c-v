#include "widget.h"
#include "view.h" // Общая память для 2-х потоков

Widget::Widget(QWidget *parent)
: QGLWidget(parent)
{
    resize(600, 600);
    connect(ms, SIGNAL(getMessage()), this, SLOT(updateGL()));

}

void Widget::initializeGL()
{
    //    qglClearColor(Qt::black);
    m_lastTime = std::time(NULL);
    m_frames = 0;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


}

void Widget::resizeGL(int nWidth, int nHeight)
{
    //    glViewport(10, 10, nWidth - 10, nHeight - 10);
    //    glMatrixMode(GL_MODELVIEW);
    //    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //   gluPerspective(120.0, (GLdouble)nWidth / (GLdouble)nHeight, 0,1000.0);
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


    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLint x, y;
    GLsizei width = 720, height = 576;
    /* DataType
    #define GL_BYTE                           0x1400
    #define GL_UNSIGNED_BYTE                  0x1401
    #define GL_SHORT                          0x1402
    #define GL_UNSIGNED_SHORT                 0x1403
    #define GL_INT                            0x1404
    #define GL_UNSIGNED_INT                   0x1405
    #define GL_FLOAT                          0x1406
    #define GL_2_BYTES                        0x1407
    #define GL_3_BYTES                        0x1408
    #define GL_4_BYTES                        0x1409
    #define GL_DOUBLE                         0x140A
     */

    glColorMask(true, true, true, false);
    GLenum format = GL_RGBA, type = GL_UNSIGNED_BYTE; //GL_UNSIGNED_SHORT_4_4_4_4;
    //    GLvoid
    //    char * pixels = new char[720 * 576 * 4];


    //    glReadPixels (x, y, width, height, format, type, pixels);
    glDrawPixels(width, height, format, type, pixels);

    glColorMask(true, true, true, true);


}
