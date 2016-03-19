#ifndef WIDGET_H
#define WIDGET_H

#include "messager.h"

#include <QtGui>
#include <QGLWidget>
#include <QtGui>
#include <QApplication>
#include <QMessageBox>

#include <ctime> // Таймер для подсчета ФПС
#include <iostream> // Печать ФПС в консоль


/* *\brief Widget Класс отображаемого окна
 *  Использует для отображение OpenGl
 *      Так же печатает в консоли запуска получаемое ФПС.
 */
class Widget : public QGLWidget {
    Q_OBJECT

    std::time_t m_lastTime; //!< последнее время замера фпс
    std::int8_t m_frames; //!< подсчет количества фпс
    GLsizei m_height = 720,
            m_width = 576;
public:
    Widget(QWidget *parent = 0);
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int nWidth, int nHeight) override;
    virtual void paintGL() override;
};

#endif
