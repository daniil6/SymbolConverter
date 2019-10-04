#include "mainframe.h"

CMainFrame::CMainFrame(wxFrame* frame)
    : wxFrame(frame, wxID_ANY, wxT("SymbolConverter"))
{

    wxButton* btnConvert = new wxButton(this, NewControlId(), wxT("Convert"));
    wxTextCtrl* txtView = new wxTextCtrl(this, NewControlId(), wxT("\n\n\n\n"));

    wxBoxSizer* main_box = new wxBoxSizer(wxVERTICAL);
    main_box->Add(btnConvert);
    main_box->Add(txtView);
    SetSizerAndFit(main_box);

    this->SetSize(500, 500);
}

CMainFrame::~CMainFrame()
{
}
