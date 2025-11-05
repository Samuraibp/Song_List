#include <iostream>
using namespace std;

const int MAX_SONGS = 200;
const int UNKNOWN_YEAR = -1;

const int MAX_TITLE = 100;
const int MAX_AUTHOR = 100;
const int MAX_LYRICS = 5000;

struct Song {
	char title[MAX_TITLE];
	char author[MAX_AUTHOR];
	int year;
	char lyrics[MAX_LYRICS];
};

Song songs[MAX_SONGS];
int song_count = 0;

void safe_input(char* buf, int size)
{
	cin.getline(buf, size);
}

int find_song_index(const char* title, const char* author)
{
	for (int i = 0; i < song_count; i++)
		if (strcmp(songs[i].title, title) == 0 && strcmp(songs[i].author, author) == 0)
			return i;
	return -1;
}

void read_lyrics(char* buffer)
{
	cout << "Enter song text. End with a single '.' on a line" << endl;
	buffer[0] = '\0';
	char line[300];
	while (true)
	{
		safe_input(line, 300);
		if (strcmp(line, ".") == 0) break;
		if (strlen(buffer) + strlen(line) + 2 < MAX_LYRICS)
		{
			strcat(buffer, line);
			strcat(buffer, "\n");
		}
	}
}



int main()
{

}