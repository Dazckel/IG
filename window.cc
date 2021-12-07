/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include <QApplication>
#include <QAction>
#include <QMenuBar>
#include <QFrame>

#include "window.h"
#include "glwidget.h"

#include <QToolBar>
#include <QString>

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

_window::_window()
{

  QSizePolicy Q(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QWidget *Central_widget = new QWidget(this);

  QFrame *Framed_widget = new QFrame(Central_widget);
  Framed_widget->setSizePolicy(Q);
  Framed_widget->setFrameStyle(QFrame::Panel);
  Framed_widget->setLineWidth(3);

  GL_widget = new _gl_widget(this);
  GL_widget->setSizePolicy(Q);

  QHBoxLayout *Horizontal_frame = new QHBoxLayout();
  Horizontal_frame->setContentsMargins(1, 1, 1, 1);

  Horizontal_frame->addWidget(GL_widget);
  Framed_widget->setLayout(Horizontal_frame);

  QHBoxLayout *Horizontal_main = new QHBoxLayout(Central_widget);

  Horizontal_main->addWidget(Framed_widget);

  Central_widget->setLayout(Horizontal_main);
  setCentralWidget(Central_widget);

  // actions for file menu
  //SALIR
  QAction *Exit = new QAction(QIcon("./icons/exit.png"), tr("&Exit..."), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

  //AANIMACIO Y MOVIMIENTOS DEL MODELO
  //ANIMACION

  QAction *Animacion = new QAction(tr("Animación"));
  connect(Animacion, SIGNAL(triggered()), SLOT(animacion()));

  //NIVEL3
  QAction *Nivel3 = new QAction(tr("Nivel3"));
  connect(Nivel3, SIGNAL(triggered()), SLOT(Nivel3()));

  //Nivel4
  QAction *Nivel4 = new QAction(tr("Nivel4"));
  connect(Nivel4, SIGNAL(triggered()), SLOT(Nivel4()));

  //Nivel5
  QAction *Nivel5 = new QAction(tr("Nivel5"));
  connect(Nivel5, SIGNAL(triggered()), SLOT(Nivel5()));

  //Ratios
  QAction *Ratios = new QAction(tr("Ratios"));
  connect(Ratios, SIGNAL(triggered()), SLOT(IncrementarRatio()));

  //TOOLBAR para modificar parámetros del modelo.
  ///////////////////////////

  QToolBar *toolbar = new QToolBar;
  addToolBar(Qt::RightToolBarArea, toolbar);
  toolbar->setToolButtonStyle(Qt::ToolButtonTextOnly);
  toolbar->addAction(Animacion);
  toolbar->addSeparator();
  toolbar->addAction(Nivel3);
  toolbar->addSeparator();
  toolbar->addAction(Nivel4);
  toolbar->addSeparator();
  toolbar->addAction(Nivel5);
  toolbar->addSeparator();
  toolbar->addAction(Ratios);

  toolbar->setAttribute(Qt::WA_AlwaysShowToolTips);


  // menus
  QMenu *File_menu = menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Exit);

  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

  setWindowTitle(tr("Prácticas IG"));

  resize(800, 800);
}

void _window::animacion()
{
  if (!(GL_widget->animacion))
    GL_widget->motion = _gl_widget_ne::_motion::ANIMACION;
  else
    GL_widget->motion = _gl_widget_ne::_motion::PARAR_ANIMACION;

}

void _window::Nivel3()
{
  GL_widget->motion = _gl_widget_ne::_motion::LEVEL_3;
}

void _window::Nivel4()
{

  GL_widget->motion = _gl_widget_ne::_motion::LEVEL_4;
}

void _window::Nivel5()
{
  GL_widget->motion = _gl_widget_ne::_motion::LEVEL_5;
}

void _window::IncrementarRatio()
{
  GL_widget->motion = _gl_widget_ne::_motion::GRADOS;
}
