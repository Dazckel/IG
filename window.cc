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

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //MENÚ DE SELECCIÓN DE OBJETOS.
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  QToolBar *objetos = new QToolBar;
  addToolBar(Qt::TopToolBarArea, objetos);

  //Tetrahedron
  QAction *Tetrahedron = new QAction(tr("Tetrahedron"));
  connect(Tetrahedron, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_TETRAHEDRON); });

  //Cube
  QAction *Cube = new QAction(tr("Cube"));
  connect(Cube, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_CUBE); });

  //Cone
  QAction *Cone = new QAction(tr("Cone"));
  connect(Cone, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_CONE); });

  //Cylinder
  QAction *Cylinder = new QAction(tr("Cylinder"));
   connect(Cylinder, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_CYLINDER); });

  QAction *Sphere = new QAction(tr("Sphere"));
  connect(Sphere, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_SPHERE); });

  //Tetrahedron
  QAction *Ply = new QAction(tr("Ply"));
   connect(Ply, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_PLY); });

  //Cube
  QAction *Model = new QAction(tr("Model"));
  connect(Model, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_PERRO); });

  //Cone
  QAction *Map = new QAction(tr("Map"));
  connect(Map, &QAction::triggered, this, [this]
          { Objects(_object::OBJECT_TABLERO); });

  //Cylinder
  QAction *Various = new QAction(tr("Various"));
  connect(Various, &QAction::triggered, this, [this]
          { Objects(_object::MULTIPLE_OBJECTS); });

  QAction *PlyS = new QAction(tr("PlyS"));
  connect(PlyS, &QAction::triggered, this, [this]
          { Objects(_object::PLYS); });

  //Insertamos las opciones en la toolbar
  //objetos->setToolButtonStyle(Qt::ToolButtonTextOnly);

  objetos->addAction(Tetrahedron);
  objetos->addSeparator();
  objetos->addAction(Cube);
  objetos->addSeparator();
  objetos->addAction(Cone);
  objetos->addSeparator();
  objetos->addAction(Cylinder);
  objetos->addSeparator();
  objetos->addAction(Sphere);
  objetos->addSeparator();
  objetos->addAction(PlyS);
  objetos->addSeparator();
  objetos->addAction(Ply);
  objetos->addSeparator();
  objetos->addAction(Model);
  objetos->addSeparator();
  objetos->addAction(Map);
  objetos->addSeparator();
  objetos->addAction(Various);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //FIN MENÚ DE SELECCIÓN DE OBJETOS.
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

  addToolBarBreak();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //MENÚ DE SELECCIÓN DE MODOS DE DIBUJO.
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  QToolBar *modes = new QToolBar;
  addToolBar(Qt::TopToolBarArea, modes);

  //Point
  QAction *Point = new QAction(tr("Point"));
  connect(Point, &QAction::triggered, this, [this]
          { Modes(_draw_modes::POINT); });
  //Fill
  QAction *Fill = new QAction(tr("Fill"));
  connect(Fill, &QAction::triggered, this, [this]
          { Modes(_draw_modes::FILL); });

  //Lines
  QAction *Lines = new QAction(tr("Lines"));
  connect(Lines, &QAction::triggered, this, [this]
          { Modes(_draw_modes::LINES); });
  //Chess
  QAction *Chess = new QAction(tr("Chess"));
  connect(Chess, &QAction::triggered, this, [this]
          { Modes(_draw_modes::CHESS); });

  //Flat
  QAction *Flat = new QAction(tr("Flat"));
  connect(Flat, &QAction::triggered, this, [this]
          { Modes(_draw_modes::FLAT); });
  //Gouraud
  QAction *Gouraud = new QAction(tr("Gouraud"));
  connect(Gouraud, &QAction::triggered, this, [this]
          { Modes(_draw_modes::SMOOTH); });
  //Texture
  QAction *Texture = new QAction(tr("Texture"));
  connect(Texture, &QAction::triggered, this, [this]
          { Modes(_draw_modes::TEXTURE); });
  //TextureFlat
  QAction *TextureFlat = new QAction(tr("TextureFlat"));
  connect(TextureFlat, &QAction::triggered, this, [this]
          { Modes(_draw_modes::TEXTURE_FLAT); });
  //TextureGouraud
  QAction *TextureGouraud = new QAction(tr("TextureGouraud"));
  connect(TextureGouraud, &QAction::triggered, this, [this]
          { Modes(_draw_modes::TEXTURE_SMOOTH); });

  modes->addAction(Point);
  modes->addAction(Lines);
  modes->addAction(Fill);
  modes->addAction(Chess);
  modes->addAction(Flat);
  modes->addAction(Gouraud);
  modes->addAction(Texture);
  modes->addAction(TextureFlat);
  modes->addAction(TextureGouraud);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //FIN MENÚ DE SELECCIÓN DE MODOS DE DIBUJO.
  //////////////////////////////////////////////////////////////////////////////////////////////////////////

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

  resize(1000, 1000);
}

void _window::animacion()
{
  if (!(GL_widget->animacion))
  {
    GL_widget->motion = _gl_widget_ne::_motion::ANIMACION;
    GL_widget->draw_model(_draw_modes_model::DEFAULT);
  }
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

// Funciones de elección de objeto.


void _window::Objects(_object ot)
{
  GL_widget->ObjectType(ot);
}

//Modos de dibujo

void _window::Modes(_draw_modes dm)
{
  GL_widget->Modes(dm);
}