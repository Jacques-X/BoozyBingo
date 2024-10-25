#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <random>
#include <algorithm>
#include <cstdlib>

const int songsNum = 282;
const int peopleNum = 35;

class Songs {
private:
    std::array<std::string, songsNum> songTitles;
    std::array<std::array<int, 25>, peopleNum> songSelection;              // [Songs] [People]
    std::array<std::array<std::array<int, 5>, 5>, peopleNum> songSheet;    // [Row] [Column] [Person]

public:
    // Getter for songTitles
    std::string getSongTitle(int index) const {
        return (index >= 0 && index < 282) ? songTitles[index] : "";
    }

    // Setter for songTitles
    void setSongTitle(int index, const std::string& title) {
        if (index >= 0 && index < 282) {
            songTitles[index] = title;
        }
    }

    // Setter for songSelection
    void setSongSelection(const std::array<std::array<int, 25>, 35>& newSelection) {
        songSelection = newSelection;
    }
};

// Function to read song titles from a file
void readSongTitles(Songs& s) {
    std::ifstream file("Songs.txt");
    std::string title;
    int index = 0;

    if (file.is_open()) {
        while (std::getline(file, title) && index < songsNum) {
            s.setSongTitle(index++, title);
        }
        file.close();
        std::cout << "Read " << index << " song titles from file.\n";
    } else {
        std::cerr << "Unable to open Songs.txt file.\nAborting program....";
        exit(0);
    }
}

// Function to choose unique random songs for each person
void chooseSongs(std::array<std::array<int, 25>, peopleNum>& songSelection) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, songsNum - 1);

    for (auto& personSelection : songSelection) {
        std::array<bool, songsNum> usedSongs = {false};  // Increase size to match songsNum
        for (int& song : personSelection) {
            int randomSong;
            do {
                randomSong = dist(gen);
            } while (usedSongs[randomSong]);  // Ensure unique song selection
            usedSongs[randomSong] = true;
            song = randomSong;
        }
    }
}

// Function to randomize the song sheet
void randomizeSheet(std::array<std::array<std::array<int, 5>, 5>, peopleNum>& songSheet, 
                    const std::array<std::array<int, 25>, peopleNum>& songSelection) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 24);

    for (int i = 0; i < peopleNum; ++i) {
        std::array<bool, 25> selected = {false};
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                int randomSong;
                do {
                    randomSong = dist(gen);
                } while (selected[randomSong]);
                selected[randomSong] = true;
                songSheet[i][j][k] = songSelection[i][randomSong];
            }
        }
    }
}

// Function to create a PDF (via HTML file)
void createPDF(const Songs& s, const std::array<std::array<std::array<int, 5>, 5>, peopleNum>& songSheet) {
    std::ofstream htmlFile("bingo_sheets.html");

    if (!htmlFile.is_open()) {
        std::cerr << "Failed to create HTML file." << std::endl;
        return;
    }

    htmlFile << "<html><head><style>"
             << "td { border: 1px solid black; padding: 10px; text-align: center; }"
             << "table { width: 100%; table-layout: auto; }"
             << "h2 {font-family: Montserrat; }"
             << "</style></head><body>";

    for (int person = 0; person < peopleNum; ++person) {
        htmlFile << "<h2>Boozy Bino Sheet No. " << person + 1 << "</h2>";
        htmlFile << "<table>";
        for (int i = 0; i < 5; ++i) {
            htmlFile << "<tr>";
            for (int j = 0; j < 5; ++j) {
                htmlFile << "<td>" << s.getSongTitle(songSheet[person][i][j]) << "</td>";
            }
            htmlFile << "</tr>";
        }
        htmlFile << "</table><br><br><br>";
        if ((person + 1) % 3 == 0 && person < (peopleNum-1)) {
            htmlFile << "<div style='page-break-after: always;'></div>";
        }
    }

    htmlFile << "</body></html>";
    htmlFile.close();

    std::string command = "wkhtmltopdf bingo_sheets.html ~/Downloads/bingo_sheets.pdf";
    if (system(command.c_str()) == 0) {
        std::cout << "PDF created successfully: ~/Downloads/bingo_sheets.pdf" << std::endl;
    } else {
        std::cerr << "Failed to create PDF. Make sure wkhtmltopdf is installed." << std::endl;
    }

    remove("bingo_sheets.html");
}

int main() {
    Songs s;
    srand(time(0));

    readSongTitles(s);

    std::array<std::array<int, 25>, peopleNum> songSelection;
    chooseSongs(songSelection);

    std::array<std::array<std::array<int, 5>, 5>, peopleNum> songSheet;
    randomizeSheet(songSheet, songSelection);

    createPDF(s, songSheet);

    return 0;
}
