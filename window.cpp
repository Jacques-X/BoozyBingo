#include <wx/wx.h>
#include <wx/scrolwin.h>
#include <wx/grid.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>  // For std::ceil

class ColorToggleButton : public wxButton {
private:
    bool isSelected;
    wxBrush defaultBrush;
    wxBrush selectedBrush;

public:
    ColorToggleButton(wxWindow* parent, wxWindowID id, const wxString& label)
        : wxButton(parent, id, label), isSelected(false) {
        defaultBrush = wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
        selectedBrush = wxColour(0, 200, 0);  // A slightly darker green
        Bind(wxEVT_PAINT, &ColorToggleButton::OnPaint, this);
    }

    void Toggle() {
        isSelected = !isSelected;
        Refresh();
    }

private:
    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);
        wxSize size = GetSize();

        dc.SetBrush(isSelected ? selectedBrush : defaultBrush);
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(wxRect(size));

        // Draw the label
        dc.SetTextForeground(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
        dc.SetFont(GetFont());
        wxString label = GetLabel();
        wxSize textSize = dc.GetTextExtent(label);
        dc.DrawText(label, (size.GetWidth() - textSize.GetWidth()) / 2,
                        (size.GetHeight() - textSize.GetHeight()) / 2);
    }
};

class MyFrame : public wxFrame {
private:
    std::vector<ColorToggleButton*> buttons;
    std::vector<wxString> buttonNames;
    wxScrolledWindow* scrolledWindow;
    wxGridSizer* gridSizer;

public:
    MyFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)) {
        scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
        scrolledWindow->SetScrollRate(0, 10);  // Vertical scroll only

        // Read and sort button names
        ReadButtonNames("Songs.txt");

        // Fixed number of columns (e.g., 5), but rows will be dynamically set
        size_t numCols = 5;
        gridSizer = new wxGridSizer(0, numCols, 10, 10);  // Rows will be set dynamically
        
        // Add buttons
        for (const wxString& name : buttonNames) {
            ColorToggleButton* button = new ColorToggleButton(scrolledWindow, wxID_ANY, name);
            button->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
            gridSizer->Add(button, 0, wxEXPAND);
            buttons.push_back(button);
        }

        // Set the sizer and fit to content
        scrolledWindow->SetSizer(gridSizer);
        scrolledWindow->FitInside();  // Ensure scrolling area fits content

        // Update the number of rows based on the window size
        Bind(wxEVT_SIZE, &MyFrame::OnResize, this);
    }

private:
    void ReadButtonNames(const wxString& filename) {
        std::ifstream file(filename.ToStdString());
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                buttonNames.push_back(wxString(line));
            }
        }
        std::sort(buttonNames.begin(), buttonNames.end());
    }

    void OnButtonClick(wxCommandEvent& event) {
        ColorToggleButton* clickedButton = dynamic_cast<ColorToggleButton*>(event.GetEventObject());
        if (clickedButton) {
            clickedButton->Toggle();
        }
    }

    void OnResize(wxSizeEvent& event) {
        // Calculate number of rows based on window height
        wxSize size = GetClientSize();
        int windowHeight = size.GetHeight();

        // Get the approximate height of one button (assuming all buttons have similar height)
        if (!buttons.empty()) {
            int buttonHeight = buttons[0]->GetSize().GetHeight();
            if (buttonHeight > 0) {
                int numRows = windowHeight / buttonHeight;
                gridSizer->SetRows(numRows);  // Set the number of rows dynamically
            }
        }

        scrolledWindow->FitInside();  // Ensure the scroll area updates
        event.Skip();  // Continue with default resize handling
    }
};

// Move MyApp out of MyFrame
class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame("Boozy Bingo Song List");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
