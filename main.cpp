#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <vector>   
#include <random>    

class songs {
private:
    std::string songTitles[100];
    int songSelection[40][25]; //[People][Songs]
    int songSheet[40][5][5];   //[People][Sheet Hight][Sheet Width]

public:
    //Getter for songTitles
    std::string getSongTitle(int index) const {
        if (index >= 0 && index < 100) {
            return songTitles[index];
        }
        return "";
    }

    //Setter for songTitles
    void setSongTitle(int index, const std::string &title) {
        if (index >= 0 && index < 100) {
            songTitles[index] = title;
        }
    }

    //Setter for entire songSelection array
    void setSongSelection(const int newSongSelection[40][25]) {
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < 25; ++j) {
                songSelection[i][j] = newSongSelection[i][j];
            }
        }
    }
};

// Function to read song titles from a file
void readSongTitles(songs &s) {
    std::ifstream file("Songs.txt");
    std::string line, title;
    int index = 0;

    if (file.is_open()) {
        while (std::getline(file, title) && index < 100) {
            s.setSongTitle(index, title); // Set the title in the songs array
            index++;
        }
        file.close();
        std::cout << "Read " << index << " song titles from file.\n";
    } else {
        std::cerr << "Unable to open Songs.txt file.\n";
    }
}

// Function to choose random songs for each person
void chooseSongs(int songSelection[40][25]) {
    // Seed for random number generator
    srand(time(0));

    // For each person
    for (int i = 0; i < 40; ++i) {
        // Boolean array to track used songs (false = not used, true = used)
        bool usedSongs[25] = {false};

        for (int j = 0; j < 25; ++j) {
            int randomSong;

            // Keep picking a random song until an unused one is found
            do {
                randomSong = rand() % 25; // Random number between 0 and 24
            } while (usedSongs[randomSong]); // Repeat if the song was already used

            // Mark this song as used and add it to the person's selection
            usedSongs[randomSong] = true;
            songSelection[i][j] = randomSong;
        }
    }
}

// Function to randomize the song sheet
void randomiseSheet(int songSheet[40][5][5], const int songSelection[40][25]) {
    // Array to track which songs have been selected
    bool selected[25];

    for (int i = 0; i < 40; ++i) {
        // Reset selected array for each songSheet
        for (int s = 0; s < 25; ++s) {
            selected[s] = false;
        }

        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                int randomSong;

                // Find a unique random song
                do {
                    randomSong = rand() % 25; // Pick a random song
                } while (selected[randomSong]); // Keep picking until we find an unselected song

                // Mark the song as selected
                selected[randomSong] = true;

                // Assign the unique song to the songSheet
                songSheet[i][j][k] = songSelection[i][randomSong];
            }
        }
    }
}

void createPDF(const songs &s, const int songSheet[40][5][5]) {
    // Create an HTML file
    std::ofstream htmlFile("bingo_sheets.html");
    
    if (!htmlFile.is_open()) {
        std::cerr << "Failed to create HTML file." << std::endl;
        return;
    }

    // Write HTML header
    htmlFile << "<html><head><style>"
             << "td { border: 1px solid black; padding: 10px; text-align: center; }"
             << "table { width: 100%; table-layout: auto; }"
             << "h2 {font-family: Montserrat; }"
             << "</style></head><body>";

    // Create a table for each person
    for (int person = 0; person < 40; ++person) {
        htmlFile << "<h2>Boozy Bino Sheet No. " << person + 1 << "</h2>";
        htmlFile << "<table>";
        for (int i = 0; i < 5; ++i) {
            htmlFile << "<tr>";
            for (int j = 0; j < 5; ++j) {
                std::string songTitle = s.getSongTitle(songSheet[person][i][j]);
                htmlFile << "<td>" << songTitle << "</td>";
            }
            htmlFile << "</tr>";
        }
        htmlFile << "</table>";

        // Add page break after every 4 people
        if ((person + 1) % 4 == 0 && person < 39) {
            htmlFile << "<div style='page-break-after: always;'></div>";
        }
    }

    // Close HTML file
    htmlFile << "</body></html>";
    htmlFile.close();

    // Convert HTML to PDF using wkhtmltopdf
    std::string command = "wkhtmltopdf bingo_sheets.html ~/Downloads/bingo_sheets.pdf";
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "PDF created successfully: ~/Downloads/bingo_sheets.pdf" << std::endl;
    } else {
        std::cerr << "Failed to create PDF. Make sure wkhtmltopdf is installed." << std::endl;
    }

    // Remove the temporary HTML file
    remove("bingo_sheets.html");
}

int main() {
    songs s;

    // Seed the random number generator once
    srand(time(0));

    // Read song titles from file
    readSongTitles(s);

    // Choosing songs for each person
    int songSelection[40][25];
    chooseSongs(songSelection);

    // Create sheet for each person
    int songSheet[40][5][5];
    randomiseSheet(songSheet, songSelection);

    // Output the songSheet array for each person
    for (int person = 0; person < 40; ++person) {
        std::cout << "Song Sheet for Person " << person + 1 << ":\n";
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                // Get the song title using the song index
                std::string songTitle = s.getSongTitle(songSheet[person][i][j]);
                std::cout << songTitle << "\t\t\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    createPDF(s, songSheet);

    return 0;
}
