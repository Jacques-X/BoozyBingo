#include <wx/wx.h>
#include <wx/grid.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
        wxPanel* panel = new wxPanel(this, wxID_ANY);
        
        // Create a 5x5 grid sizer
        wxGridSizer* gridSizer = new wxGridSizer(5, 5, 10, 10);
        
        for (int i = 0; i < 25; i++) { // 25 cells for a 5x5 grid
            wxButton* button = new wxButton(panel, wxID_ANY, wxString::Format("Button %d", i/2 + 1));
                gridSizer->Add(button, 0, wxEXPAND);
        }
        
        panel->SetSizer(gridSizer);
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame("Boozy Bingo Song List");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);