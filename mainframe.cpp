#include "mainframe.h"

#include <convert_double_bit.h>
#include <convert_string_double.h>

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include <wx/valtext.h>

#define DEF_RECT wxDefaultPosition, wxDefaultSize

// SymbolConverter

CMainFrame::CMainFrame()
    : wxFrame(nullptr, wxID_ANY, wxT(""), DEF_RECT, wxRESIZE_BORDER | wxCAPTION | wxCLOSE_BOX | wxFRAME_SHAPED)
{
    wxTextValidator* txtValid = new wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST);
    txtValid->SetCharIncludes(wxT("0123456789.-"));

    wxButton* btnSetZero = new wxButton(this, NewControlId(), wxT("0x"));
    wxButton* btnConvert = new wxButton(this, NewControlId(), wxT("Convert"));

    mTxtA = new wxTextCtrl(this, NewControlId(), wxT(""), DEF_RECT, wxTE_MULTILINE);
    mTxtA->SetValidator(*txtValid);

    mTxtB = new wxTextCtrl(this, NewControlId(), wxT(""), DEF_RECT, wxTE_MULTILINE);
    mTxtB->SetValidator(*txtValid);

    {
        wxBoxSizer* mainBox = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* hBox = nullptr;

        {
            hBox = new wxBoxSizer(wxHORIZONTAL);
            hBox->Add(btnConvert);
            hBox->Add(btnSetZero);
            mainBox->Add(hBox);
        }

        {
            mainBox->Add(mTxtA, 1, wxEXPAND);
            mainBox->Add(mTxtB, 1, wxEXPAND);
        }

        this->SetSizerAndFit(mainBox);
    }

    Bind(wxEVT_BUTTON, &CMainFrame::OnConvert, this, btnConvert->GetId());
    mTxtA->Bind(wxEVT_CHAR_HOOK, &CMainFrame::OnKeyDown, this);
    mTxtB->Bind(wxEVT_CHAR_HOOK, &CMainFrame::OnKeyDown, this);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnKeyDown(wxKeyEvent& event)
{
    wxTextCtrl* txt = dynamic_cast<wxTextCtrl*>(this->FindWindow(event.GetId()));

    if(wxGetKeyState(wxKeyCode('.')) == true)
        if(txt->GetValue().Find('.') != -1)
            return;

    if(wxGetKeyState(wxKeyCode('-')) == true)
        if(txt->GetValue().empty() == false)
            return;

    event.Skip();
}

void CMainFrame::OnConvert(wxCommandEvent& event)
{
    std::string strParse;
    std::string strIn = mTxtA->GetValue().ToStdString();
    mTxtB->Clear();

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
        mTxtB->SetValue(str);
    }
}