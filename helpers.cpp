#include "helpers.h"

void displaySongsInArray(Song songArray[], int numSongs) {
    for (int i = 0; i < numSongs; i += 1) {
        songArray[i].displayInfo();
    }
}

int homePageInput() {
    cout << "What would you like to do today?" << endl;
    cout << "0. Exit program." << endl;
    cout << "1. Find the next song." << endl;
    cout << "2. Remove/Add a Song." << endl;
    cout << "Enter your choice here: ";
    string input;
    getline(cin, input);
    int option = stoi(input);
    return option;
}

string songNameInput() {
    string input;
    cout << "Enter the name of the song here (watch out for spacing and capitalization!): ";
    getline(cin, input);
    return input;
}

int getAddRemoveInput() {
    int choice;
    cout << "Would you like to remove a song or add one back in? (0 to exit, 1 for remove, 2 for add): ";
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}


void findNextSongs(Song original, Song songArray[], int numSongs) {
    Song potentialSongs[100];
    string camelotArray[24] = {"1A", "1B", "2A", "2B", "3A", "3B", "4A", "4B", "5A", "5B", "6A", "6B", "7A", "7B", "8A", "9A", "9B", "10A", "10B", "11A", "11B", "12A", "12B"};

    cout << "Original Song: " << endl;
    cout << "------------------------" << endl;
    original.displayInfo();
    cout << endl;
    cout << "Suggested Next Song(s): " << endl;
    cout << "------------------------" << endl;

    int numPotential = 0;

    int ogBPM = original.getBPM();
    double maxPosBPM = ogBPM * (4.0 / 3.0);
    double minPosBPM = ogBPM * (3.0 / 4.0);

    string pos1, pos2, pos3, pos4, pos5, pos6;
    string ogCamelot = original.getCamelot();

    // Trim leading and trailing whitespaces from ogCamelot
    ogCamelot.erase(std::remove_if(ogCamelot.begin(), ogCamelot.end(), ::isspace), ogCamelot.end());

    for (int i = 0; i < 24; i += 1) {
        // Trim leading and trailing whitespaces from camelotArray[i]
        string trimmedCamelot = camelotArray[i];
        trimmedCamelot.erase(std::remove_if(trimmedCamelot.begin(), trimmedCamelot.end(), ::isspace), trimmedCamelot.end());

        if (ogCamelot == trimmedCamelot) {
            pos1 = trimmedCamelot;
            if (trimmedCamelot == "1A" || trimmedCamelot == "1B") {
                if (trimmedCamelot == "1A") {
                    pos2 = "12B";
                    pos3 = "12A";
                }
                if (trimmedCamelot == "1B") {
                    pos2 = "12B";
                    pos3 = "1A";
                }
                pos4 = camelotArray[i + 1];
                pos5 = camelotArray[i + 2];
                pos6 = camelotArray[i + 3];
            }
            else if (trimmedCamelot == "12A" || trimmedCamelot == "12B") {
                if (trimmedCamelot == "12A") {
                    pos2 = camelotArray[23];
                    pos3 = camelotArray[0];
                }
                if (trimmedCamelot == "12B") {
                    pos2 = camelotArray[0];
                    pos3 = camelotArray[1];
                }
                pos5 = camelotArray[i - 1];
                pos6 = camelotArray[i - 2];
                pos6 = camelotArray[i - 3];
            }
            else {
                pos2 = camelotArray[i + 1];
                pos3 = camelotArray[i + 2];
                pos4 = camelotArray[i - 1];
                pos5 = camelotArray[i - 2];
                pos6 = camelotArray[i + 3];
            }
        }
    }

    for (int i = 0; i < numSongs; i += 1) {
        int bpmOfSong = songArray[i].getBPM();
        string camelotOfSong = songArray[i].getCamelot();

        camelotOfSong.erase(std::remove_if(camelotOfSong.begin(), camelotOfSong.end(), ::isspace), camelotOfSong.end());

        if (bpmOfSong <= maxPosBPM && bpmOfSong >= minPosBPM) {
            if (camelotOfSong == pos1 || camelotOfSong == pos2 || camelotOfSong == pos3 || camelotOfSong == pos4 || camelotOfSong == pos5) {
                if (songArray[i].getSongName() != original.getSongName()) {
                    potentialSongs[numPotential] = songArray[i];
                    numPotential += 1;
                }
            }
        }
    }

    if (numPotential == 0) { // output section
        cout << "NO SONGS FOUND :(" << endl;
    } else {
        for (int i = 0; i < numPotential; i += 1) {
            potentialSongs[i].displayInfo();
        }
    }
    cout << endl;
}

void removeAddSong(string title, Song songArray1[], Song songArray2[], int& numSongs1, int& numSongs2) {
    for (int i = 0; i < numSongs1; i += 1) {
        if (songArray1[i].getSongName() == title) {
            songArray2[numSongs2] = songArray1[i];
            for (int j = i; j < numSongs1 - 1; j += 1) {
                songArray1[j] = songArray1[j + 1];
            }
        numSongs1 -= 1;
        numSongs2 += 1;
        }
    }
}