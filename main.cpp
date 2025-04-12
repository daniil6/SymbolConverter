#include "mainframe.h"

#include <wx/app.h>

class CMainApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        return (new CMainFrame())->Show();
    }
};

IMPLEMENT_APP(CMainApp);