///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __wxGUI__
#define __wxGUI__
#include <wx/app.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
///////////////////////////////////////////////////////////////////////////
#define CNGUIMAJORV 0
#define CNGUIMINORV 2
#include "../headers/core.hpp"

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class cnApp
///////////////////////////////////////////////////////////////////////////////
class cnApp : public wxApp
{
     public:
         virtual bool OnInit();
};
///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame2
///////////////////////////////////////////////////////////////////////////////
class MyFrame2 : public wxFrame
{
	private:
		bool connected;
		Core_connector connector;
		usr_data usr;

	protected:
		wxStaticText* m_staticText3;
		wxTextCtrl* login_text;
		wxButton* connect_btn;
		wxStaticText* m_staticText4;
		wxTextCtrl* password_text;
		wxCheckBox* bmstu_chk;
		wxStatusBar* statusbar;

		// Virtual event handlers, overide them in your derived class
		virtual void connect_func( wxCommandEvent& );


	public:

		MyFrame2( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ICNWX Connector"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,100 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );
		~MyFrame2();

};

#endif //__wxGUI__
