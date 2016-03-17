#include "widget.h"
#include "view.h" // Общая память для 2-х потоков

Widget::Widget(QWidget *parent)
: QGLWidget(parent)
{
    resize(m_width, m_height);
    connect(ms, SIGNAL(getMessage()), this, SLOT(updateGL()));

}

void Widget::initializeGL()
{
    m_lastTime = std::time(NULL);
    m_frames = 0;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(0.0f,0.0f,1.0f);
//glEnable(GL_LIGHTING);
}

void Widget::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_MODELVIEW);
//    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint) nWidth, (GLint) nHeight);
}

GLint nNumPoints = 3;
GLfloat ctrlPoints[3][3][3] = {{{ -4.0f, 0.0f, 4.0f},
                                { -2.0f, 4.0f, 4.0f},
                                {  4.0f, 0.0f, 4.0f}},
                               {{ -4.0f, 0.0f, 0.0f},
                                { -2.0f, 4.0f, 0.0f},
                                {  4.0f, 0.0f, 0.0f}},
                               {{ -4.0f, 0.0f, -4.0f},
                                { -2.0f, 4.0f, -4.0f},
                                {  4.0f, 0.0f, -4.0f}}};
                                        
                                        
                                        
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

//    gluLookAt(2.0f, 2.0f,2.0f,
//              0.5f, 1.0f,0.5f, // Нормаль повернута в обратную сторону
//              0.0f, 1.0f,0.0f);
//    gluPerspective(90.f,1.0,0.1,40.f);

    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
//    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f,0.0f,-1.0f);

//GLAPI void GLAPIENTRY gluLookAt 
//    (GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, 
//    GLdouble centerX, GLdouble centerY, GLdouble centerZ, 
//    GLdouble upX, GLdouble upY, GLdouble upZ);
    
//GLAPI void GLAPIENTRY glMap2f( GLenum target,
//		     GLfloat u1, GLfloat u2, GLint ustride, GLint uorder,
//		     GLfloat v1, GLfloat v2, GLint vstride, GLint vorder,
//		     const GLfloat *points );

    GLUquadric * quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_FLAT);

    gluQuadricDrawStyle(quad,GLU_FILL);

    glPushMatrix();
    
    glColor3f(0.0f,1.0f,1.0f);
    gluSphere (quad, 0.1f, 4, 2);
    glColor3f(0.0f,1.0f,1.0f);

    glPopMatrix();
    
    glTranslatef(0.0f,-0.2f,0.0f);

    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    gluSphere (quad, 0.1f, 4, 2);
    glColor3f(1.0f,1.0f,0.0f);
    glPopMatrix();
    
//    GLfloat light_position[]={2.0,1.0,2.0,0.0};
//    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
//    glEnable(GL_LIGHT0);

    gluDeleteQuadric(quad);

    
//    glMap2f(GL_MAP2_VERTEX_3,
//            -5.0f,
//            10.0f,
//            3,
//            3,
//            -5.0f,
//            10.0f,
//            9,
//            3,
//            &(ctrlPoints[0][0][0]));
////    
//    glEnable(GL_MAP2_VERTEX_3);
////    
//    glMapGrid2f(10,0.0f,10.0f,10,0.0f,10.0f);
////    glEvalMesh2(GL_LINE,0,10,0,10);
//    glEvalMesh2(GL_FILL,0,10,0,10);
//    glEnable(GL_AUTO_NORMAL);
////    
////    // Drawpoints
    int i,j;
    glPointSize(5.0f);
//
    glBegin(GL_POINTS);
    for(i = 0; i < nNumPoints; ++i)
        for(j = 0; j < 3; ++j)
            glVertex3fv(ctrlPoints[i][j]);
    glEnd();


    
    // Отображение

    

    
//    glutSwapBuffers();
    
    

    

//#define GL_BYTE					0x1400
//#define GL_UNSIGNED_BYTE			0x1401
//#define GL_SHORT				0x1402
//#define GL_UNSIGNED_SHORT			0x1403
//#define GL_INT					0x1404
//#define GL_UNSIGNED_INT				0x1405
//#define GL_FLOAT				0x1406
//#define GL_2_BYTES				0x1407
//#define GL_3_BYTES				0x1408
//#define GL_4_BYTES				0x1409
//#define GL_DOUBLE				0x140A
    
    
    glColorMask(true, true, true, false);
    GLenum format = GL_RGBA, 
            type = GL_UNSIGNED_BYTE;
//            type = GL_BYTE;
//            type = GL_SHORT;

    glDrawPixels(m_width, m_height, format, type, pixels);
    glColorMask(true, true, true, true);

    
    glPopMatrix();
    
}
