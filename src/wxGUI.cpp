///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////
#include <cstring>
#include "../headers/wxGUI.h"

///////////////////////////////////////////////////////////////////////////
DECLARE_APP(cnApp)

IMPLEMENT_APP(cnApp)

bool cnApp::OnInit()
{
    MyFrame2 *frame = new MyFrame2(NULL,wxID_ANY,wxT("ICNWX connector"));
    frame->Show(true);
    return true;
}


MyFrame2::MyFrame2( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	connected=0;
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 3, 3, 0, 0 );
	fgSizer3->AddGrowableCol( 1 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Логин"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT|wxALL, 5 );

	login_text = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	login_text->SetMaxLength( 16 );
	fgSizer3->Add( login_text, 0, wxALL|wxEXPAND, 5 );

	connect_btn = new wxButton( this, wxID_ANY, wxT("Подключиться"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( connect_btn, 0, wxALL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("  Пароль"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	m_staticText4->Wrap( -1 );
	fgSizer3->Add( m_staticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	password_text = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	password_text->SetMaxLength( 10 );
	fgSizer3->Add( password_text, 0, wxALL|wxEXPAND, 5 );

	bmstu_chk = new wxCheckBox( this, wxID_ANY, wxT("Канал МГТУ"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( bmstu_chk, 0, wxALL, 5 );

	this->SetSizer( fgSizer3 );
	this->Layout();
	statusbar = this->CreateStatusBar( 3, wxST_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	connect_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame2::connect_func ), NULL, this );
}

void MyFrame2::connect_func( wxCommandEvent& event )
{
    if (connected==0) //Подключаемся
    {
        usr.command=0;
        connected=1;
        usr.login=login_text->GetValue().mb_str(wxConvUTF8);
        usr.password=password_text->GetValue().mb_str(wxConvUTF8);
        usr.bmstu=bmstu_chk->GetValue();
        connector.connect_serv(usr);
        login_text->Enable(0);
        password_text->Enable(0);
        bmstu_chk->Enable(0);
        connect_btn->SetLabel(wxT("Отключиться"));
    } else
    {
        connected=0;
        connector.disconnect_serv();
        login_text->Enable(1);
        password_text->Enable(1);
        bmstu_chk->Enable(1);
        connect_btn->SetLabel(wxT("Подключиться"));
    }
    event.Skip();
}


MyFrame2::~MyFrame2()
{
	// Disconnect Events
	connect_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame2::connect_func ), NULL, this );
	if (connected==1)
	  connector.disconnect_serv();

}
