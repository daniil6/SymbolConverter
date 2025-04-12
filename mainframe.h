#pragma once

#include <wx/frame.h>
#include <wx/textctrl.h>

class CMainFrame : public wxFrame
{
private:
    wxTextCtrl* mTxtA;
    wxTextCtrl* mTxtB;

    void OnConvert(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);

public:
    CMainFrame();
    ~CMainFrame() override;
};