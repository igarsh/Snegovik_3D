//---------------------------------------------------------------------------
// Borland C++Builder
// Copyright (c) 1987, 1998 Inprise Corporation. All Rights Reserved.
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "draw.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TOpenGL_Form *OpenGL_Form;
//---------------------------------------------------------------------------
__fastcall TOpenGL_Form::TOpenGL_Form(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
////////////////Функция установки Формата Пикселей,////////////////////////////
BOOL bSetupPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                        PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_RGBA;
    ppfd->cColorBits = 32;
    ppfd->cDepthBits = 32;

    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 )
    {
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE)
    {
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;

}
///////////РИСОВАНИЕ СЦЕНЫ ВО ВНЕЭКРАННОМ БУФЕРЕ В ПАМЯТИ////////////////////////////
void	TOpenGL_Form::DrawScene()
{

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    glPushMatrix();

    glColor3d(1,1,1);
    glTranslated(0.0, -0.75, 0.0);
    glCallList(GLOBE1);
    //КООРДИНАТЫ В ЦЕНТРЕ НИЖНЕГО ШАРА
    glColor3d(1,1,1);
    glTranslated(0.0, 0.7, 0.0);
    glCallList(GLOBE2);
    //КООРДИНАТЫ В ЦЕНТРЕ СРЕДНЕГО ШАРА
    //ЛЕВАЯ РУКА
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslated(-0.4, 0.0, 0.0);
    glCallList(HANDS);
    glPopMatrix();
    //КООРДИНАТЫ В ЦЕНТРЕ СРЕДНЕГО ШАРА
    //ПРАВАЯ РУКА
    glPushMatrix();
    glColor3d(1,1,1);
    glTranslated(0.4, 0.0, 0.0);
    glCallList(HANDS);
    glPopMatrix();
    //ГОЛОВА
    //КООРДИНАТЫ В ЦЕНТРЕ СРЕДНЕГО ШАРА
    glColor3d(1,1,1);
    glTranslated(0.0, 0.5, 0.0);
    glCallList(GLOBE3);
    //КООРДИНАТЫ В ЦЕНТРЕ ВЕРХНЕГО ШАРА
    //НОС
    glPushMatrix();
    glColor3d(1,0,0);
    glTranslated(0.0, 0.0, 0.15);
    glCallList(CONE_NOS);
    glPopMatrix();
    //КООРДИНАТЫ В ЦЕНТРЕ ВЕРХНЕГО ШАРА
    //ШЛЯПА
    glPushMatrix();
    glColor3d(0,0,1);
    glTranslated(0.0, 0.09, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glCallList(CONE_CAP);
    glPopMatrix();
    //КООРДИНАТЫ В ЦЕНТРЕ ВЕРХНЕГО ШАРА
    //ПЕРВЫЙ ГЛАЗ
    glPushMatrix();
    glColor3d(0,0,0);
    glTranslated(-0.08, 0.05, 0.18);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glCallList(EYES);
    glPopMatrix();
    //КООРДИНАТЫ В ЦЕНТРЕ ВЕРХНЕГО ШАРА
    //ВТОРОЙ ГЛАЗ
    glPushMatrix();
    glColor3d(0,0,0);
    glTranslated(0.08, 0.05, 0.18);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glCallList(EYES);
    glPopMatrix();


    glPopMatrix();
    //КООРДИНАТЫ ВЕРНУЛИСЬ НА ИСХОДНУЮ ПОЗИЦИЮ В ЦЕНТР ЭКРАНА
    glFlush();
    SwapBuffers(ghDC); //ОБМЕН БУФЕРОВ (ВЫБРОС НА ЭКРАН)
}


////PRAPARE SCENE///////СОЗДАНИЕ ОБЪЕКТОВ В ЛИСТАХ/////////////////////////////////
GLvoid TOpenGL_Form::createObjects()
{
    GLUquadricObj *quadObj;

    glNewList(GLOBE1, GL_COMPILE);
        quadObj = gluNewQuadric ();
        gluQuadricDrawStyle (quadObj, GLU_FILL);
        gluSphere (quadObj, 0.5, 30, 30);
    glEndList();

    glNewList(GLOBE2, GL_COMPILE);
        quadObj = gluNewQuadric ();
        gluQuadricDrawStyle (quadObj, GLU_FILL);
        gluSphere (quadObj, 0.38, 30, 30);
    glEndList();

    glNewList(GLOBE3, GL_COMPILE);
        quadObj = gluNewQuadric ();
        gluQuadricDrawStyle (quadObj, GLU_FILL);
        gluSphere (quadObj, 0.2, 30, 30);
    glEndList();

    glNewList(CONE_NOS, GL_COMPILE);
        quadObj = gluNewQuadric ();
        gluQuadricDrawStyle (quadObj, GLU_FILL);
        gluCylinder (quadObj, 0.05, 0, 0.15, 30, 30);
    glEndList();

    glNewList(CONE_CAP, GL_COMPILE);
        quadObj = gluNewQuadric ();
        gluQuadricDrawStyle (quadObj, GLU_FILL);
        gluCylinder (quadObj, 0.18, 0.1, 0.25, 30, 30);
    glEndList();

     glNewList(EYES, GL_COMPILE);
        quadObj = gluNewQuadric ();
        gluQuadricDrawStyle (quadObj, GLU_FILL);
        gluSphere (quadObj, 0.025, 30, 30);
    glEndList();

    glNewList(HANDS, GL_COMPILE);
        quadObj = gluNewQuadric ();
        gluQuadricDrawStyle (quadObj, GLU_FILL);
        gluSphere (quadObj, 0.14, 30, 30);
    glEndList();



}
////////////////////////////////////////////////////////////////////////////////


//---------------------------------------------------------------------------
void __fastcall TOpenGL_Form::FormCreate(TObject *Sender)
{
        ghDC = GetDC(Handle);
        if (!bSetupPixelFormat(ghDC))
            Close();
        ghRC = wglCreateContext(ghDC);//Create Rendering Context
        wglMakeCurrent(ghDC, ghRC);   //make it current
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f) ;
        glClearDepth( 1.0 );
        glEnable(GL_DEPTH_TEST); //разрешает вычисление буфера глубины
        //который используется для скрытия точек принадлеж невидимым поверхностям
        SetupLighting();
        createObjects(); //Создает объекты в памяти в листах
}
//---------------------------------------------------------------------------
void __fastcall TOpenGL_Form::FormResize(TObject *Sender)
{
////////////ПРИ ИЗМЕНЕНИИ РАЗМЕРОВ ОКНА///SETTING UP THE WORLD
//выполняется как при запуске программы так и при изм разм окна
   GLsizei width=ClientRect.Right;
   GLsizei height=ClientRect.Bottom;

   GLfloat aspect= (GLfloat) width / height;

    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 30.0, aspect, 3.0,   7.0 );
 //                fovy          znear  zfar
 // Z-axis values that are greater than -3 and
 //less than –7 are clipped from the screen. 
   

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslated(0.0, 0.0, -5.0);//!!!без нее ниче не видно
    DrawScene();//обновляет экран при изменении размера,полезная штука
}
//---------Заметаем следы %))------------------------------------
void __fastcall TOpenGL_Form::FormClose(TObject *Sender, TCloseAction &Action)
{
	  
        if (ghRC)
            wglDeleteContext(ghRC);
        if	(ghDC)
        	ReleaseDC(Handle, ghDC);
}
//---------------------------------------------------------------------------
void __fastcall TOpenGL_Form::FormPaint(TObject *Sender)
{
DrawScene();
}
//---------------------------------------------------------------------------

void __fastcall TOpenGL_Form::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{                          
    if(Key == VK_UP)
        glRotatef(-5, 1.0, 0.0, 0.0);
    if(Key == VK_DOWN)
        glRotatef(5, 1.0, 0.0, 0.0);
    if(Key == VK_LEFT)
        glRotatef(-5, 0.0, 1.0, 0.0);
    if(Key == VK_RIGHT)
        glRotatef(5, 0.0, 1.0, 0.0);
}
//---------------------------------------------------------------------------
void __fastcall TOpenGL_Form::SetupLighting()
{
    GLfloat MaterialAmbient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat MaterialDiffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat MaterialSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat MaterialShininess[] = {50.0};
    GLfloat AmbientLightPosition[] = {0.5, 1.0, 1.0, 0.0};
    GLfloat LightAmbient[] = {0.5, 0.5, 0.5, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
    glLightfv(GL_LIGHT0, GL_POSITION, AmbientLightPosition);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
}
void __fastcall TOpenGL_Form::Timer1Timer(TObject *Sender)
{
//glRotatef(5, 0.0, 1.0, 0.0);
DrawScene();        
}
//---------------------------------------------------------------------------

