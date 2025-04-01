#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//Problematic code:Without using single responsibility principle, There would be 2 reason to modify implementation
// one writeFile and other readFile
class FileManager
{
	std::string fileName;
	std::string data;
public:
	FileManager(std::string fileName, std::string data) :fileName(fileName),data(data)
	{

	}
	void writeFile()
	{
		std::ofstream fout;
		fout.open(fileName);
		fout << data;
		fout.close();
	}
	void readFile()
	{
		std::ifstream fin;
		fin.open(fileName);
		std::string line;
		std::vector<std::string> data;
		while (getline(fin, line))
		{
			data.push_back(line);
		}
		fin.close();
	}

};
int main()
{
	std::string data("ABC DEF ");
	FileManager fm("data.txt", data);
	fm.writeFile();
	fm.readFile();
	return 0;
}

Implementaiton using single responsibilty principle:
class FileWriter 
public:
    void saveToFile(string filename, string data) {
        ofstream file(filename);
        file << data;
        file.close();
    }
};

class FileReader {
public:
    vector<string> readFromFile(string filename) {
        vector<string> data;
        string line;
        ifstream file(filename);
        while (getline(file, line)) {
            data.push_back(line);
        }
        file.close();
        return data;
    }
};

class FileManager : public FileReader, public FileWriter {

};

int main() {
    FileManager file_manager;
    file_manager.saveToFile("data.txt", "Hello, World!");

    vector<string> data = file_manager.readFromFile("data.txt");
    for (string line : data) {
        cout << line << endl;
    }

    return 0;
}

