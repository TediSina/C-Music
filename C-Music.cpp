#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Song {
public:
    std::string title;
    std::string artist;
    std::string path;

    Song(std::string t, std::string a, std::string p)
        : title(t), artist(a), path(p) {
    }

    virtual ~Song() {}

    virtual void display() const {
        std::cout << "Title: " << title << " | Artist: " << artist;
    }

    void play() const {
        std::string command = "start \"\" \"" + path + "\"";
        system(command.c_str());
    }

    virtual std::string getGenre() const = 0;
};

class RockSong : public Song {
public:
    RockSong(std::string t, std::string a, std::string p)
        : Song(t, a, p) {
    }

    void display() const override {
        Song::display();
        std::cout << " | Genre: Rock\n";
    }

    std::string getGenre() const override {
        return "Rock";
    }
};

class PopSong : public Song {
public:
    PopSong(std::string t, std::string a, std::string p)
        : Song(t, a, p) {
    }

    void display() const override {
        Song::display();
        std::cout << " | Genre: Pop\n";
    }

    std::string getGenre() const override {
        return "Pop";
    }
};

class HipHopSong : public Song {
public:
    HipHopSong(std::string t, std::string a, std::string p)
        : Song(t, a, p) {
    }

    void display() const override {
        Song::display();
        std::cout << " | Genre: Hip-Hop\n";
    }

    std::string getGenre() const override {
        return "HipHop";
    }
};

class MusicLibrary {
private:
    std::vector<Song*> songs;
    const std::string filename = "songs.txt";

public:
    MusicLibrary() {
        loadSongs();
        std::srand(std::time(0));
    }

    ~MusicLibrary() {
        for (auto song : songs) {
            delete song;
        }
    }

    void addSong() {
        int genreChoice;
        std::string title, artist, path;
        std::cin.ignore();
        std::cout << "Enter song title: ";
        std::getline(std::cin, title);
        std::cout << "Enter artist name: ";
        std::getline(std::cin, artist);
        std::cout << "Enter file path: ";
        std::getline(std::cin, path);

        path.erase(std::remove(path.begin(), path.end(), '\"'), path.end());
        path.erase(std::remove(path.begin(), path.end(), '\''), path.end());

        std::cout << "Select Genre:\n";
        std::cout << "1. Rock\n";
        std::cout << "2. Pop\n";
        std::cout << "3. Hip-Hop\n";
        std::cout << "Choice: ";
        std::cin >> genreChoice;

        Song* newSong = nullptr;
        switch (genreChoice) {
        case 1:
            newSong = new RockSong(title, artist, path);
            break;
        case 2:
            newSong = new PopSong(title, artist, path);
            break;
        case 3:
            newSong = new HipHopSong(title, artist, path);
            break;
        default:
            std::cout << "\nInvalid genre. Song not added.\n";
            return;
        }

        songs.push_back(newSong);
        saveSongs();
    }

    void listSongs() const {
        if (songs.empty()) {
            std::cout << "\nNo songs in the library.\n";
            return;
        }
        std::cout << std::endl;
        for (size_t i = 0; i < songs.size(); ++i) {
            std::cout << i + 1 << ". ";
            songs[i]->display();
        }
    }

    void listSongsByGenre() const {
        if (songs.empty()) {
            std::cout << "\nNo songs in the library.\n";
            return;
        }
        int genreChoice;
        std::cout << "\nFilter by Genre:\n";
        std::cout << "1. Rock\n";
        std::cout << "2. Pop\n";
        std::cout << "3. Hip-Hop\n";
        std::cout << "Choice: ";
        std::cin >> genreChoice;
        std::cout << std::endl;

        bool found = false;
        int index = 1;
        for (const auto& song : songs) {
            if ((genreChoice == 1 && song->getGenre() == "Rock") ||
                (genreChoice == 2 && song->getGenre() == "Pop") ||
                (genreChoice == 3 && song->getGenre() == "HipHop")) {
				std::cout << index << ". ";
                song->display();
                found = true;
            }
            index++;
        }

        if (!found) {
            std::cout << "\nNo songs found for the selected genre.\n";
        }
    }

    void playSong() const {
        if (songs.empty()) {
            std::cout << "\nNo songs to play.\n";
            return;
        }
        int choice;
        std::cout << "\nEnter the song number to play: ";
        std::cin >> choice;
        if (choice < 1 || choice > songs.size()) {
            std::cout << "\nInvalid choice.\n";
            return;
        }
        songs[choice - 1]->play();
    }

    void playRandomSong() const {
        if (songs.empty()) {
            std::cout << "\nNo songs in the library.\n";
            return;
        }
        int randomIndex = std::rand() % songs.size();
        std::cout << "\nPlaying random song:\n";
        std::cout << randomIndex << ". ";
        songs[randomIndex]->display();
        std::cout << std::endl;
        songs[randomIndex]->play();
    }

    void deleteSong() {
        if (songs.empty()) {
            std::cout << "\nNo songs to delete.\n";
            return;
        }
        listSongs();
        int choice;
        std::cout << "\nEnter the song number to delete: ";
        std::cin >> choice;
        if (choice < 1 || choice > songs.size()) {
            std::cout << "\nInvalid choice.\n";
            return;
        }
        delete songs[choice - 1];
        songs.erase(songs.begin() + (choice - 1));
        saveSongs();
        std::cout << "\nSong deleted successfully.\n";
    }

private:
    void saveSongs() const {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cout << "\nError saving songs.\n";
            return;
        }
        for (const auto& song : songs) {
            outFile << song->title << "|" << song->artist << "|" << song->path << "|" << song->getGenre() << "\n";
        }
    }

    void loadSongs() {
        std::ifstream inFile(filename);
        if (!inFile) {
            return;
        }
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string title, artist, path, genre;

            std::getline(ss, title, '|');
            std::getline(ss, artist, '|');
            std::getline(ss, path, '|');
            std::getline(ss, genre);

            Song* newSong = nullptr;
            if (genre == "Rock") {
                newSong = new RockSong(title, artist, path);
            }
            else if (genre == "Pop") {
                newSong = new PopSong(title, artist, path);
            }
            else if (genre == "HipHop") {
                newSong = new HipHopSong(title, artist, path);
            }

            if (newSong != nullptr) {
                songs.push_back(newSong);
            }
        }
    }
};

int main() {
    MusicLibrary library;
    int choice;

    do {
        std::cout << "\n--- C-Music ---\n";
        std::cout << "-----------------\n";
        std::cout << "Made by: Alons Fejzo, Riseld Logu & Tedi Sina\n";
        std::cout << "-----------------\n";
        std::cout << "Select an option:\n";
        std::cout << "1. Add Song\n";
        std::cout << "2. List All Songs\n";
        std::cout << "3. List Songs by Genre\n";
        std::cout << "4. Play Song\n";
        std::cout << "5. Play Random Song\n";
        std::cout << "6. Delete Song\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            library.addSong();
            break;
        case 2:
            library.listSongs();
            break;
        case 3:
            library.listSongsByGenre();
            break;
        case 4:
            library.playSong();
            break;
        case 5:
            library.playRandomSong();
            break;
        case 6:
            library.deleteSong();
            break;
        case 7:
            std::cout << "\nGoodbye!\n";
            break;
        default:
            std::cout << "\nInvalid option.\n";
        }
    } while (choice != 7);

    return 0;
}
