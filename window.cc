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


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/





_window::_window()
{

  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QWidget *Central_widget = new QWidget(this);

  QFrame *Framed_widget= new QFrame(Central_widget);
  Framed_widget->setSizePolicy(Q);
  Framed_widget->setFrameStyle(QFrame::Panel);
  Framed_widget->setLineWidth(3);


  GL_widget = new _gl_widget(this);
  GL_widget->setSizePolicy(Q);

  QHBoxLayout *Horizontal_frame = new QHBoxLayout();
  Horizontal_frame->setContentsMargins(1,1,1,1);

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
  const QIcon openIcon = QIcon::fromTheme("Animacion", QIcon("./icons/ANIMACION.png"));
  QAction *openAct = new QAction(openIcon, tr("Animacion"), this);
  connect(openAct, SIGNAL(triggered()), this, SLOT(animacion()));

  //MOVIMIENTO
  QAction *movimiento = new QAction(openIcon, tr("Movimiento"), this);
  connect(movimiento, SIGNAL(triggered()), this, SLOT(Movimiento()));

  //parametros
  QAction *parametros = new QAction(openIcon, tr("Parametros"), this);
  connect(parametros, SIGNAL(triggered()), this, SLOT(Parametros()));

  //Posicion
  QAction *Posicion = new QAction(openIcon, tr("Posicion"), this);
  connect(Posicion, SIGNAL(triggered()), this, SLOT(Posicion()));


  
  
  //MENU DE LAS ACCIONES DEL MODELO
  QMenu *Motion_menu=menuBar()->addMenu(tr("&Motion"));
  Motion_menu->addAction(openAct);
  Motion_menu->addAction(movimiento);
  Motion_menu->addAction(parametros);
  Motion_menu->addAction(Posicion);
  //

  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Exit);


  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

  setWindowTitle(tr("Práctica 1"));

  resize(800,800);
}

void _window::animacion()
{
  GL_widget->Draw_model = true;
  GL_widget->opcion =_gl_widget_ne::_opciones::ANIMACION;
  GL_widget->draw_objects();
}

void _window::Movimiento()
{
  GL_widget->Draw_model = true;
  GL_widget->opcion = _gl_widget_ne::_opciones::MOVIMIENTO;
}


void _window::Parametros()
{
  GL_widget->Draw_model = true;
  GL_widget->opcion = _gl_widget_ne::_opciones::PARAMETROS;
}

void _window::Posicion()
{
  GL_widget->Draw_model = true;
  GL_widget->opcion = _gl_widget_ne::_opciones::POSICION;
}