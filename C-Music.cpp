#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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
        std::cout << "2. List Songs\n";
        std::cout << "3. Play Song\n";
        std::cout << "4. Delete Song\n";
        std::cout << "5. Exit\n";
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
            library.playSong();
            break;
        case 4:
            library.deleteSong();
            break;
        case 5:
            std::cout << "\nGoodbye!\n";
            break;
        default:
            std::cout << "\nInvalid option.\n";
        }
    } while (choice != 5);

    return 0;
}
