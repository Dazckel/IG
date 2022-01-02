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
                { Objects(_object::OBJECT_SPOT); });

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

        QAction *Animacion = new QAction(tr("Animación"));
        connect(Animacion, SIGNAL(triggered()), SLOT(animacion()));

        objetos->addAction(Animacion);
        objetos->addSeparator();

        objetos->addAction(Tetrahedron);
        objetos->addAction(Cube);
        objetos->addAction(Cone);
        objetos->addAction(Cylinder);
        objetos->addAction(Sphere);
        objetos->addAction(Ply);
        objetos->addAction(PlyS);
        objetos->addAction(Model);
        objetos->addAction(Map);
        objetos->addAction(Various);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //FIN MENÚ DE SELECCIÓN DE OBJETOS.
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        addToolBarBreak();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //MENÚ DE SELECCIÓN DE MODOS DE DIBUJO.
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

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

        objetos->addSeparator();
        objetos->addSeparator();
        objetos->addSeparator();

        objetos->addAction(Point);
        objetos->addAction(Lines);
        objetos->addAction(Fill);
        objetos->addAction(Chess);
        objetos->addAction(Flat);
        objetos->addAction(Gouraud);
        objetos->addAction(Texture);
        objetos->addAction(TextureFlat);
        objetos->addAction(TextureGouraud);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //FIN MENÚ DE SELECCIÓN DE MODOS DE DIBUJO.
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //MENÚ MODELO
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        QToolBar *toolbar = new QToolBar;
        addToolBar(Qt::RightToolBarArea, toolbar);

        ////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////
        //NIVEL3
        /////////////////////////////
        QWidget *wid = new QWidget;

        QPushButton *button1 = new QPushButton("Inc1Gr");
        QPushButton *button2 = new QPushButton("Dec1Gr");
        QPushButton *button3 = new QPushButton("Inc2Gr");
        QPushButton *button4 = new QPushButton("Dec2Gr");

        QGridLayout *layout = new QGridLayout(wid);

        QLabel *lv3 = new QLabel("Forearm");

        connect(button1, &QPushButton::pressed, this, [this]
                { Forearm(_opciones::OP1); });
        connect(button2, &QPushButton::pressed, this, [this]
                { Forearm(_opciones::OP2); });
        connect(button3, &QPushButton::pressed, this, [this]
                { Forearm(_opciones::OP3); });
        connect(button4, &QPushButton::pressed, this, [this]
                { Forearm(_opciones::OP4); });

        layout->addWidget(button1, 0, 0);
        layout->addWidget(button2, 0, 1);
        layout->addWidget(button3, 1, 0);
        layout->addWidget(button4, 1, 1);
        /////////////////////////////
        //ArmBody
        /////////////////////////////
        QWidget *wid4 = new QWidget;

        QPushButton *button4_1 = new QPushButton("Inc1GrD");
        QPushButton *button4_2 = new QPushButton("Dec1GrD");
        QPushButton *button4_3 = new QPushButton("Inc2GrD");
        QPushButton *button4_4 = new QPushButton("Dec2GrD");
        QPushButton *button4_5 = new QPushButton("Inc1GrT");
        QPushButton *button4_6 = new QPushButton("Dec2GrT");
        QPushButton *button4_7 = new QPushButton("Inc1GrT");
        QPushButton *button4_8 = new QPushButton("Dec2GrT");

        QGridLayout *layout4 = new QGridLayout(wid4);

        QLabel *lv4 = new QLabel("Arm");

        connect(button4_1, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP1); });
        connect(button4_2, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP2); });
        connect(button4_3, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP3); });
        connect(button4_4, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP4); });
        connect(button4_5, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP5); });
        connect(button4_6, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP6); });
        connect(button4_7, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP7); });
        connect(button4_8, &QPushButton::pressed, this, [this]
                { ArmBody(_opciones::OP8); });

        layout4->addWidget(button4_1, 0, 0);
        layout4->addWidget(button4_2, 0, 1);
        layout4->addWidget(button4_3, 1, 0);
        layout4->addWidget(button4_4, 1, 1);
        layout4->addWidget(button4_5, 2, 0);
        layout4->addWidget(button4_6, 2, 1);
        layout4->addWidget(button4_7, 3, 0);
        layout4->addWidget(button4_8, 3, 1);

        //Fly
        QWidget *wid5 = new QWidget;

        QPushButton *button5_1 = new QPushButton("Inc1Gr");
        QPushButton *button5_2 = new QPushButton("Dec1Gr");
        QPushButton *button5_3 = new QPushButton("Inc2Gr");
        QPushButton *button5_4 = new QPushButton("Dec2Gr");

        QGridLayout *layout5 = new QGridLayout(wid5);

        QLabel *lv5 = new QLabel("Fly");

        connect(button5_1, &QPushButton::pressed, this, [this]
                { Fly(_opciones::OP1); });
        connect(button5_2, &QPushButton::pressed, this, [this]
                { Fly(_opciones::OP2); });
        connect(button5_3, &QPushButton::pressed, this, [this]
                { Fly(_opciones::OP3); });
        connect(button5_4, &QPushButton::pressed, this, [this]
                { Fly(_opciones::OP4); });

        layout5->addWidget(button5_1, 0, 0);
        layout5->addWidget(button5_2, 0, 1);
        layout5->addWidget(button5_3, 1, 0);
        layout5->addWidget(button5_4, 1, 1);

        /////////////////////////////
        //Ratios
        /////////////////////////////
        QWidget *widR = new QWidget;

        QPushButton *buttonR_1 = new QPushButton("Inc1Gr_2");
        QPushButton *buttonR_2 = new QPushButton("Dec1GR_2");
        QPushButton *buttonR_3 = new QPushButton("Inc2Gr_2");
        QPushButton *buttonR_4 = new QPushButton("Dec2Gr_2");
        QPushButton *buttonR_5 = new QPushButton("Inc1Gr_3");
        QPushButton *buttonR_6 = new QPushButton("Dec1Gr_3");
        QPushButton *buttonR_7 = new QPushButton("Inc2Gr_3");
        QPushButton *buttonR_8 = new QPushButton("Dec2Gr_3");
        QPushButton *buttonR_9 = new QPushButton("Inc1Gr_4");
        QPushButton *buttonR_10 = new QPushButton("Dec1Gr_4");
        QPushButton *buttonR_11 = new QPushButton("Inc2Gr_4");
        QPushButton *buttonR_12 = new QPushButton("Dec2Gr_4");

        QGridLayout *layoutR = new QGridLayout(widR);

        QLabel *Rat = new QLabel("Ratios");

        connect(buttonR_1, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP1); });
        connect(buttonR_2, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP2); });
        connect(buttonR_3, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP3); });
        connect(buttonR_4, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP4); });
        connect(buttonR_5, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP5); });
        connect(buttonR_6, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP6); });
        connect(buttonR_7, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP7); });
        connect(buttonR_8, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP8); });
        connect(buttonR_9, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP9); });
        connect(buttonR_10, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP10); });
        connect(buttonR_11, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP11); });
        connect(buttonR_12, &QPushButton::pressed, this, [this]
                { Ratios(_opciones::OP12); });

        layoutR->addWidget(buttonR_1, 0, 0);
        layoutR->addWidget(buttonR_2, 0, 1);
        layoutR->addWidget(buttonR_3, 1, 0);
        layoutR->addWidget(buttonR_4, 1, 1);
        layoutR->addWidget(buttonR_5, 2, 0);
        layoutR->addWidget(buttonR_6, 2, 1);
        layoutR->addWidget(buttonR_7, 3, 0);
        layoutR->addWidget(buttonR_8, 3, 1);
        layoutR->addWidget(buttonR_9, 4, 0);
        layoutR->addWidget(buttonR_10, 4, 1);
        layoutR->addWidget(buttonR_11, 5, 0);
        layoutR->addWidget(buttonR_12, 5, 1);

        /////////////////////////////
        //Luces y Materiales
        /////////////////////////////
        QWidget *widL = new QWidget;

        QPushButton *buttonL_1 = new QPushButton("Luz 1");
        QPushButton *buttonL_2 = new QPushButton("Luz 2");
        QPushButton *buttonL_3 = new QPushButton("Materiales");
        QPushButton *buttonL_4 = new QPushButton("MoveX +");
        QPushButton *buttonL_5 = new QPushButton("MoveY +");
        QPushButton *buttonL_6 = new QPushButton("MoveZ +");
        QPushButton *buttonL_7 = new QPushButton("MoveX -");
        QPushButton *buttonL_8 = new QPushButton("MoveY -");
        QPushButton *buttonL_9 = new QPushButton("MoveZ -");

        QGridLayout *layoutL = new QGridLayout(widL);

        QLabel *Luces = new QLabel("Luces y materiales");

        connect(buttonL_1, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP1); });
        connect(buttonL_2, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP2); });
        connect(buttonL_3, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP3); });
        connect(buttonL_4, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP4); });
        connect(buttonL_5, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP5); });
        connect(buttonL_6, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP6); });
        connect(buttonL_7, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP7); });
        connect(buttonL_8, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP8); });
        connect(buttonL_9, &QPushButton::pressed, this, [this]
                { Luces_Materiales(_opciones::OP9); });

        layoutL->addWidget(buttonL_1, 0, 0);
        layoutL->addWidget(buttonL_2, 0, 1);
        layoutL->addWidget(buttonL_3, 0, 2);
        layoutL->addWidget(buttonL_4, 1, 0);
        layoutL->addWidget(buttonL_5, 1, 1);
        layoutL->addWidget(buttonL_6, 1, 2);
        layoutL->addWidget(buttonL_7, 2, 0);
        layoutL->addWidget(buttonL_8, 2, 1);
        layoutL->addWidget(buttonL_9, 2, 2);

        /////////////////////////////
        //Perspectiva
        /////////////////////////////
        QWidget *widP = new QWidget;

        QPushButton *buttonP_1 = new QPushButton("Projection");
        QPushButton *buttonP_2 = new QPushButton("Orthotonal");
        QGridLayout *layoutP = new QGridLayout(widP);

        QLabel *Persp = new QLabel("Perspectiva");

        layoutP->addWidget(buttonP_1, 0, 0);
        layoutP->addWidget(buttonP_2, 0, 1);

        connect(buttonP_1, &QPushButton::pressed, this, [this]
                { Perspectiva(_opciones::OP1); });
        connect(buttonP_2, &QPushButton::pressed, this, [this]
                { Perspectiva(_opciones::OP2); });

        ////////////////////////////////////////////////////////////////////

        /////////////////////////////
        //Ejes
        /////////////////////////////
        QWidget *wipE = new QWidget;

        QPushButton *buttonE_1 = new QPushButton("Eje X");
        QPushButton *buttonE_2 = new QPushButton("Eje Y");
        QPushButton *buttonE_3 = new QPushButton("Eje Z");
        QGridLayout *layoutE = new QGridLayout(wipE);

        QLabel *Ejs = new QLabel("Eje de la generatriz");

        layoutE->addWidget(buttonE_1, 0, 0);
        layoutE->addWidget(buttonE_2, 0, 1);
        layoutE->addWidget(buttonE_3, 0, 2);

        connect(buttonE_1, &QPushButton::pressed, this, [this]
                { Ejes(_opciones::OP1); });
        connect(buttonE_2, &QPushButton::pressed, this, [this]
                { Ejes(_opciones::OP2); });
        connect(buttonE_3, &QPushButton::pressed, this, [this]
                { Ejes(_opciones::OP3); });

        ////////////////////////////////////////////////////////////////////

        /////////////////////////////
        //Elegir ply
        /////////////////////////////
        QWidget *wipPl = new QWidget;

        QPushButton *buttonPl_1 = new QPushButton("Big dodge");
        QPushButton *buttonPl_2 = new QPushButton("Beethoven");
        QPushButton *buttonPl_3 = new QPushButton("Hormiga");
        QGridLayout *layoutPl = new QGridLayout(wipPl);

        QLabel *Pl = new QLabel("Elegir Ply");

        layoutPl->addWidget(buttonPl_1, 0, 0);
        layoutPl->addWidget(buttonPl_2, 0, 1);
        layoutPl->addWidget(buttonPl_3, 0, 2);

        connect(buttonPl_1, &QPushButton::pressed, this, [this]
                { choose_ply(_opciones::OP1); });
        connect(buttonPl_2, &QPushButton::pressed, this, [this]
                { choose_ply(_opciones::OP2); });
        connect(buttonPl_3, &QPushButton::pressed, this, [this]
                { choose_ply(_opciones::OP3); });

        ////////////////////////////////////////////////////////////////////

        toolbar->addWidget(Pl);
        toolbar->addWidget(wipPl);

        toolbar->addWidget(lv3);
        toolbar->addWidget(wid);

        toolbar->addWidget(lv4);
        toolbar->addWidget(wid4);

        toolbar->addWidget(lv5);
        toolbar->addWidget(wid5);

        toolbar->addWidget(Rat);
        toolbar->addWidget(widR);

        toolbar->addWidget(Luces);
        toolbar->addWidget(widL);

        toolbar->addWidget(Persp);
        toolbar->addWidget(widP);

        toolbar->addWidget(Ejs);
        toolbar->addWidget(wipE);

        toolbar->setAttribute(Qt::WA_AlwaysShowToolTips);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //FIN MENÚ MODELO
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////////////////////////////////
        ////// TEXTURAS
        /////////////////////////////////////
        QToolBar *toolbarT = new QToolBar;
        addToolBar(Qt::LeftToolBarArea, toolbarT);

        QWidget *texturas = new QWidget;
        QPushButton *marte = new QPushButton("Marte");
        connect(marte, &QPushButton::pressed, this, [this]
                { choose_texture(_opciones::OP1); });

        //Tetrahedron
        QPushButton *estrellas = new QPushButton("Estrellas");
        connect(estrellas, &QPushButton::pressed, this, [this]
                { choose_texture(_opciones::OP2); });

        //Cube
        QPushButton *sol = new QPushButton("Sol");
        connect(sol, &QPushButton::pressed, this, [this]
                { choose_texture(_opciones::OP3); });

        //Cone
        QPushButton *venus = new QPushButton("Venus");
        connect(venus, &QPushButton::pressed, this, [this]
                { choose_texture(_opciones::OP4); });

        //Cylinder
        QPushButton *mercurio = new QPushButton("Mercurio");
        connect(mercurio, &QPushButton::pressed, this, [this]
                { choose_texture(_opciones::OP5); });

        QPushButton *t_noche = new QPushButton("Tierra");
        connect(t_noche, &QPushButton::pressed, this, [this]
                { choose_texture(_opciones::OP6); });
        QGridLayout *layout_texturas = new QGridLayout(texturas);

        layout_texturas->addWidget(marte, 0, 0);
        layout_texturas->addWidget(estrellas, 1, 0);
        layout_texturas->addWidget(sol, 2, 0);
        layout_texturas->addWidget(venus, 3, 0);
        layout_texturas->addWidget(mercurio, 4, 0);
        layout_texturas->addWidget(t_noche, 5, 0);
        toolbarT->addWidget(texturas);
        //////////////////////////////////////////

        setWindowTitle(tr("Prácticas IG"));

        resize(1000, 1000);
}

void _window::animacion()
{
        GL_widget->Animacion();
}

void _window::Forearm(_opciones opcion)
{
        GL_widget->Forearm(opcion);
}

void _window::ArmBody(_opciones opcion)
{
        GL_widget->ArmBody(opcion);
}

void _window::Fly(_opciones opcion)
{
        GL_widget->Fly(opcion);
}

void _window::Ratios(_opciones opcion)
{
        GL_widget->Ratios(opcion);
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

void _window::Luces_Materiales(_opciones opcion)
{
        GL_widget->Luces_Materiales(opcion);
}

void _window::Perspectiva(_opciones opcion)
{
        GL_widget->Perspectiva(opcion);
}

void _window::Ejes(_opciones opcion)
{
        GL_widget->Ejes(opcion);
}

///
void _window::choose_ply(_opciones op)
{
        GL_widget->choose_ply(op);
}

void _window::choose_texture(_opciones op)
{
        GL_widget->choose_texture(op);
}