#include <iostream>
#include <fstream>
#include <algorithm>
#include "math.h"
#include "song.h"
using namespace std;

/*
https://www.reddit.com/r/Beatmatch/comments/uyl5po/ways_to_transition_between_different_tempos_and/
https://www.reddit.com/r/DJs/comments/c98oeq/camelot_keywheel_rules_transitions_demonstration/
*/

string songInput() {
    cout << "Enter the song name or enter 0 to quit: ";
    string input;
    getline(cin, input);
    return input;
}

void findNextSongs(Song original, Song songArray[], int numSongs) {
    Song potentialSongs[100];
    string camelotArray[24] = {"1A", "1B", "2A", "2B", "3A", "3B", "4A", "4B", "5A", "5B", "6A", "6B", "7A", "7B", "8A", "9A", "9B", "10A", "10B", "11A", "11B", "12A", "12B"};

    cout << "------------------------" << endl;
    cout << "Original Song: " << endl;
    original.displayInfo();
    cout << endl;
    cout << "------------------------" << endl;
    cout << "Suggested Next Songs: " << endl;

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


int main() {
    system("clear");
    int numSongs = 0;
    Song songArray[100];
    string camelotArray[24] = {"1A", "1B", "2A", "2B", "3A", "3B", "4A", "4B", "5A", "5B", "6A", "6B", "7A", "7B", "8A", "9A", "9B", "10A", "10B", "11A", "11B", "12A", "12B"};
    string selection;

    ifstream file("file.csv");
    if (!file.is_open()) {
        cerr << "File couldn't be opened!" << endl;
        return 1;
    }

    string header;
    getline(file, header);

    string first, songName, bpmTemp, camelot;
    while (getline(file, first, ',')) {
        getline(file, songName, ',');
        getline(file, bpmTemp, ',');
        getline(file, camelot, '\n');

        int bpm = stoi(bpmTemp); 

        songArray[numSongs] = Song(songName, camelot, bpm);
        numSongs += 1;
    }

    while (true) {
        string input = songInput();

        if (input == "0") {
            system("clear");
            break;
        }
        else {
            for (int i = 0; i < numSongs; i += 1) {
                if (songArray[i].getSongName() == input) {
                    Song first = songArray[i];
                    findNextSongs(first, songArray, numSongs);
                }
            }
        }
    }
    file.close();
    return 0;
}

