#include "mainframe.h"

CMainFrame::CMainFrame(wxFrame* frame)
    : wxFrame(frame, wxID_ANY, wxT("SymbolConverter"))
{
    const wxString allow[] = { wxT(".") wxT("0"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"),
        wxT("8"), wxT("9") };
    wxArrayString* str = new wxArrayString(sizeof(allow) / sizeof(allow[0]), allow);
    wxTextValidator* validTxt = new wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST);
    validTxt->SetIncludes(*str);

    wxButton* btnConvert = new wxButton(this, NewControlId(), wxT("Convert"));
    wxTextCtrl* txtView =
        new wxTextCtrl(this, NewControlId(), wxT(""), wxDefaultPosition, wxSize(200, 250), wxTE_MULTILINE);
    txtView->SetValidator(*validTxt);

    wxBoxSizer* main_box = new wxBoxSizer(wxVERTICAL);
    main_box->Add(btnConvert);
    main_box->Add(txtView);
    SetSizerAndFit(main_box);

    this->SetSize(500, 350);
}

CMainFrame::~CMainFrame()
{
}
