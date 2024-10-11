#include <wx/wx.h>
#include <wx/grid.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
    {
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        
        wxGridSizer* gridSizer = new wxGridSizer(5, 4, 10, 10);
        
        for (int i = 0; i < 20; i++)
        {
            wxTextCtrl* textField = new wxTextCtrl(panel, wxID_ANY, wxString::Format("Text %d", i + 1));
            gridSizer->Add(textField, 0, wxEXPAND);
            
            wxButton* button = new wxButton(panel, wxID_ANY, wxString::Format("Button %d", i + 1));
            gridSizer->Add(button, 0, wxEXPAND);
        }
        
        panel->SetSizer(gridSizer);
    }
};

class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyFrame* frame = new MyFrame("Buttons and Text Fields Example");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);