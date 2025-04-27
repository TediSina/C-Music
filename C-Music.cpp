#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

/**
 * @brief Represents a Song object.
 *
 * This class defines a song with title, artist, and file path, along with methods for displaying and playing the song.
 */
class Song {
public:
    std::string title;
    std::string artist;
    std::string path;

    /**
     * @brief Constructor for Song.
     *
     * Initializes a song with a title, artist, and file path.
     *
     * @param t The title of the song.
     * @param a The artist of the song.
     * @param p The file path of the song.
     */
    Song(std::string t, std::string a, std::string p)
        : title(t), artist(a), path(p) {
    }

    /**
     * @brief Destructor for Song.
     *
     * Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~Song() {}

    /**
     * @brief Displays the song information.
     *
     * Prints the title and artist of the song to the console.
     */
    virtual void display() const {
        std::cout << "Title: " << title << " | Artist: " << artist;
    }

    /**
     * @brief Plays the song.
     *
     * Plays the song using the system's default media player by calling the system's play command.
     */
    void play() const {
        std::string command = "start \"\" \"" + path + "\"";
        system(command.c_str());
    }

    /**
     * @brief Abstract method to get the genre of the song.
     *
     * @return The genre of the song as a string.
     */
    virtual std::string getGenre() const = 0;
};

/**
 * @brief Represents a Rock Song.
 *
 * This class extends the Song class and defines a rock genre song.
 */
class RockSong : public Song {
public:
    /**
     * @brief Constructor for RockSong.
     *
     * Initializes a rock song with a title, artist, and file path.
     *
     * @param t The title of the rock song.
     * @param a The artist of the rock song.
     * @param p The file path of the rock song.
     */
    RockSong(std::string t, std::string a, std::string p)
        : Song(t, a, p) {
    }

    /**
     * @brief Displays the rock song information.
     *
     * Prints the title, artist, and genre (Rock) to the console.
     */
    void display() const override {
        Song::display();
        std::cout << " | Genre: Rock\n";
    }

    /**
     * @brief Gets the genre of the rock song.
     *
     * @return The genre of the rock song as "Rock".
     */
    std::string getGenre() const override {
        return "Rock";
    }
};

/**
 * @brief Represents a Pop Song.
 *
 * This class extends the Song class and defines a pop genre song.
 */
class PopSong : public Song {
public:
    /**
     * @brief Constructor for PopSong.
     *
     * Initializes a pop song with a title, artist, and file path.
     *
     * @param t The title of the pop song.
     * @param a The artist of the pop song.
     * @param p The file path of the pop song.
     */
    PopSong(std::string t, std::string a, std::string p)
        : Song(t, a, p) {
    }

    /**
     * @brief Displays the pop song information.
     *
     * Prints the title, artist, and genre (Pop) to the console.
     */
    void display() const override {
        Song::display();
        std::cout << " | Genre: Pop\n";
    }

    /**
     * @brief Gets the genre of the pop song.
     *
     * @return The genre of the pop song as "Pop".
     */
    std::string getGenre() const override {
        return "Pop";
    }
};

/**
 * @brief Represents a Hip-Hop Song.
 *
 * This class extends the Song class and defines a hip-hop genre song.
 */
class HipHopSong : public Song {
public:
    /**
     * @brief Constructor for HipHopSong.
     *
     * Initializes a hip-hop song with a title, artist, and file path.
     *
     * @param t The title of the hip-hop song.
     * @param a The artist of the hip-hop song.
     * @param p The file path of the hip-hop song.
     */
    HipHopSong(std::string t, std::string a, std::string p)
        : Song(t, a, p) {
    }

    /**
     * @brief Displays the hip-hop song information.
     *
     * Prints the title, artist, and genre (Hip-Hop) to the console.
     */
    void display() const override {
        Song::display();
        std::cout << " | Genre: Hip-Hop\n";
    }

    /**
     * @brief Gets the genre of the hip-hop song.
     *
     * @return The genre of the hip-hop song as "HipHop".
     */
    std::string getGenre() const override {
        return "HipHop";
    }
};

/**
 * @brief Manages a collection of songs.
 *
 * This class manages the library of songs, allowing users to add, list, play, and delete songs, as well as save and load songs to/from a file.
 */
class MusicLibrary {
private:
    std::vector<Song*> songs;
    const std::string filename = "songs.txt";

    /**
     * @brief Saves the current song list to a file.
     *
     * Writes the song details (title, artist, path, genre) to a file named "songs.txt".
     */
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

    /**
     * @brief Loads songs from a file.
     *
     * Reads the song details from a file named "songs.txt" and populates the song library.
     */
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

public:
    /**
     * @brief Constructor for MusicLibrary.
     *
     * Initializes the music library by loading songs from a file and initializing random number generation.
     */
    MusicLibrary() {
        loadSongs();
        std::srand(std::time(0));
    }

    /**
     * @brief Destructor for MusicLibrary.
     *
     * Cleans up the dynamically allocated songs in the library.
     */
    ~MusicLibrary() {
        for (auto song : songs) {
            delete song;
        }
    }

    /**
     * @brief Adds a song to the library.
     *
     * Prompts the user for song details (title, artist, path, genre) and adds the song to the library.
     */
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

    /**
     * @brief Lists all songs in the library.
     *
     * Displays all songs in the library, printing their details (title, artist, genre).
     */
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

    /**
     * @brief Lists songs by genre.
     *
     * Allows the user to filter songs by genre (Rock, Pop, or Hip-Hop) and displays the matching songs.
     */
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

    /**
     * @brief Plays a song from the library.
     *
     * Prompts the user to select a song and plays the selected song.
     */
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

    /**
     * @brief Plays a random song from the library.
     *
     * Selects a random song from the library and plays it.
     */
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

    /**
     * @brief Deletes a song from the library.
     *
     * Prompts the user to select a song to delete and removes the selected song from the library.
     */
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
};

/**
 * @brief Main function.
 *
 * The entry point of the program. Displays a menu and prompts the user for actions related to the music library (add, list, play, etc.).
 *
 * @return int Exit status code.
 */
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
