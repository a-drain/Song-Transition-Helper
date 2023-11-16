#include "song.h"

Song::Song() {
    songName = "DEFAULT";
    camelot = "0B";
    BPM = 0;
}

Song::Song(string newName, string newCam, int newBPM) {
    songName = newName;
    camelot = newCam;
    BPM = newBPM;
}

string Song::getSongName() const {
    return songName;
}

string Song::getCamelot() const {
    return camelot;
}

int Song::getBPM() const {
    return BPM;
}

void Song::displayInfo() const {
    cout << "Song: " << songName << endl;
    cout << "BPM: " << BPM << endl;
    cout << "Camelot: " << camelot << endl;
    cout << "------------------------" << endl;
}
