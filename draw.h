
//--------------------------------------------------------------------------
#ifndef drawH
#define drawH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

//---------------------------------------------------------------------------

#define GLOBE1    1
#define GLOBE2    2
#define GLOBE3    3
#define CONE_NOS  4
#define CONE_CAP  5
#define EYES      6
#define HANDS     7
//---------------------------------------------------------------------------
class TOpenGL_Form : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormPaint(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations




    HGLRC ghRC;
    HDC   ghDC;


    
public:		// User declarations
	__fastcall TOpenGL_Form(TComponent* Owner);
        void __fastcall SetupLighting();
        void DrawScene();
        GLvoid createObjects();
        //void __fastcall SetupTextures();




};
//---------------------------------------------------------------------------
extern TOpenGL_Form *OpenGL_Form;
//---------------------------------------------------------------------------
#endif
