#include "mainframe.h"

CMainFrame::CMainFrame(wxFrame* frame)
    : wxFrame(frame, wxID_ANY, wxT("SymbolConverter"))
{
    const wxString allow[] = { wxT("0"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"),
        wxT("9"), wxT("."), wxT("-") };
    wxArrayString* str = new wxArrayString(sizeof(allow) / sizeof(allow[0]), allow);
    wxTextValidator* validTxt = new wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST);
    validTxt->SetIncludes(*str);

    wxButton* convertButton = new wxButton(this, NewControlId(), wxT("Convert"));
    m_inTextCtrl = new wxTextCtrl(this, NewControlId(), wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    m_outTextCtrl = new wxTextCtrl(this, NewControlId(), wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    m_inTextCtrl->SetValidator(*validTxt);
    m_outTextCtrl->SetValidator(*validTxt);

    wxBoxSizer* main_box = new wxBoxSizer(wxVERTICAL);
    main_box->Add(convertButton);

    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_inTextCtrl, 0, wxEXPAND);
    h_box->Add(m_outTextCtrl, 1, wxEXPAND);
    main_box->Add(h_box, 1, wxEXPAND);

    SetSizerAndFit(main_box);

    Bind(wxEVT_BUTTON, &CMainFrame::OnConvert, this, convertButton->GetId());
    m_inTextCtrl->Bind(wxEVT_CHAR_HOOK, &CMainFrame::OnKeyDown, this);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnKeyDown(wxKeyEvent& event)
{
    if(wxGetKeyState(wxKeyCode('.')) == true)
        if(m_inTextCtrl->GetValue().Find('.') != -1)
            return;

    if(wxGetKeyState(wxKeyCode('-')) == true)
        if(m_inTextCtrl->GetValue().empty() == false)
            return;

    event.Skip();
}

void CMainFrame::OnConvert(wxCommandEvent& event)
{
    std::string strParse;
    std::string strIn = m_inTextCtrl->GetValue().ToStdString();
    m_outTextCtrl->Clear();

    std::vector<double> out;
    for(auto itr = strIn.begin(); itr != strIn.end() + 1; ++itr) {
        if(*itr == '\n' || *itr == '\0') {
            out.push_back(ConvertStringToDouble(strParse));
            strParse.clear();
        } else
            strParse.push_back(*itr);
    }

    for(auto& p : out) {
        wxString str(ConvertDoubleToBit(p));
        m_outTextCtrl->SetValue(str);
    }

    this->SetSizerAndFit(this->GetSizer());
}
