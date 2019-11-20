#ifndef CMAINFRAME_H
#define CMAINFRAME_H

#include <RBKLib.h>
#include <wx/wx.h>

class CMainFrame : public wxFrame
{
private:
    wxTextCtrl* m_inTextCtrl;
    wxTextCtrl* m_outTextCtrl;

    void OnConvert(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);

public:
    CMainFrame(wxFrame* frame);
    ~CMainFrame();
};

#endif // CMAINFRAME_H
