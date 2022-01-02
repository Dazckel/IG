HEADERS += \
  aux.h \
  aux2.h \
  aux3.h \
  colors.h \
  basic_object3d.h \
  cone.h \
  cylinder.h \
  dog.h \
  dogocopter.h \
  draw_types.h \
  femur.h \
  file_ply_stl.h \
  forearm.h \
  gorrocoptero.h \
  helice.h \
  leg.h \
  object3d.h \
  axis.h \
  object_ply.h \
  object_rev.h \
  pata.h \
  perro.h \
  perro_volador.h \
  sphere.h \
  tablero.h \
  tetrahedron.h \
  cube.h \
  glwidget.h \
  tibia.h \
  window.h

SOURCES += \
  aux.cpp \
  aux2.cc \
  aux3.cc \
  basic_object3d.cc \
  cone.cc \
  cylinder.cc \
  dog.cc \
  dogocopter.cc \
  femur.cc \
  file_ply_stl.cc \
  forearm.cc \
  gorrocoptero.cc \
  helice.cc \
  leg.cc \
  object3d.cc \
  axis.cc \
  object_ply.cc \
  object_rev.cc \
  pata.cc \
  perro.cc \
  perro_volador.cc \
  sphere.cc \
  tablero.cc \
  tetrahedron.cc \
  cube.cc \
  main.cc \
  glwidget.cc \
  tibia.cc \
  window.cc


LIBS += -L/usr/X11R6/lib64 -lGL


CONFIG += c++11
QT += widgets


DISTFILES += \
    window.o

linux {
TARGET= skeleton
INCLUDEPATH += /home/dazckel/Facultad/IG/glew/include
LIBS += -L/home/dazckel/Facultad/IG/glew/lib -lGLEW \
-L/usr/X11R6/lib64 -lGL
}
