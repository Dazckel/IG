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

#include <QMainWindow>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QGuiApplication>

#include <QSignalMapper>
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
  void Nivel3();
  void Nivel4();
  void Nivel5();
  void IncrementarRatio();

  // Funciones de elección de objeto.

  //Draw modes

  void Modes(_draw_modes dm);
  void Objects(_object ot);

private:
  _gl_widget *GL_widget;
};

#endif
