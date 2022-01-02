/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef DRAWMODES
#include "draw_modes.h"
#endif

#ifndef OBJECT_T
#include "object_types.h"
#endif

#ifndef MODEL_PARAM
#include "model_param.h"
#endif

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGuiApplication>
#include <QLabel>
#include <QSignalMapper>
#include <QPushButton>
class _gl_widget;

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

class _window : public QMainWindow
{
  Q_OBJECT

public:
  _window();

public slots:
  void animacion();
  void Forearm(_opciones opcion);
  void ArmBody(_opciones opcion);
  void Fly(_opciones opcion);
  void Ratios(_opciones opcion);
  // Funciones de elección de objeto.

  //Draw modes

  void Modes(_draw_modes dm);
  void Objects(_object ot);
  void Luces_Materiales(_opciones opcion);
  void Perspectiva(_opciones opcion);
  void Ejes(_opciones opcion);
  void choose_ply(_opciones op);
  void choose_texture(_opciones op);

  private:
    _gl_widget *GL_widget;
  };

#endif
