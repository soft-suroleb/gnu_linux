#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DX 3
#define DY 6
#define INNER_DX 1
#define INNER_DY 4
#define INNER_LINES (LINES - 2 * (DX + INNER_DX))

void printColoredString(WINDOW *frame, int x, int y, char *str, int color) {
	int i = 0;
	while (str[i] != '\0') {
		mvwaddch(frame, x, y + i, str[i] | COLOR_PAIR(color));
		i++;
	}
}

void writeNumStr(WINDOW *frame, int x, int y, int num) {
	int i = 0;
	if (num == 0) {
		mvwaddch(frame, x, y, '0' | COLOR_PAIR(1));
	}

	while (num > 0) {
		mvwaddch(frame, x, y - i, (num % 10 + '0') | COLOR_PAIR(1));
		num /= 10;
		i++;
	}
}

int getFileSize(FILE *file) {
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file);
	fseek(file, 0, SEEK_SET);
	return file_size;
}

int getCodeRows(char **code) {
	int size = 0;
	while(code[size++] != NULL);
	return size;
}

char *file2buf(FILE *file) {
	int file_size = getFileSize(file);
	char *buf = (char *)malloc(sizeof(char) * file_size + 1);
	fread(buf, sizeof(char), file_size, file);

	buf[file_size] = '\0';

	return buf;
}

char **fileSplit(char *buf) {
	char **code = (char **)malloc(sizeof(char *) * 300);
	int i = 0;
	int current_row = 0;

	char *tmp = (char *)malloc(sizeof(char) * 300);
	int tmp_i = 0; 
	while (buf[i] != '\0') {
		if (buf[i] == '\t') {
			tmp[tmp_i] = ' ';
			tmp[tmp_i + 1] = ' ';
			tmp[tmp_i + 2] = ' ';
			tmp[tmp_i + 3] = ' ';
			tmp_i += 4;
		} else if (buf[i] != '\n') {
			tmp[tmp_i++] = buf[i];
		} else {
			tmp[tmp_i] = '\0';
			tmp_i = 0;
			code[current_row++] = tmp;
			tmp = (char *)malloc(sizeof(char) * 100);
		}
		i++;
	}

	code[current_row] = NULL;
	return code;
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Usage: ./Show\n");
		return 1;
	}

	char* buf;
	char** code;

	FILE *file = fopen(argv[1], "r");
	if(file == NULL) {
		fprintf(stderr, "Error opening file\n");
		return 1;
	}

	buf = file2buf(file);
	code = fileSplit(buf);

	WINDOW *frame;
	int c = 0;	

	initscr();
	noecho();
	cbreak();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	printw("File: %s; size: %d\n", argv[1], getCodeRows(code));
	refresh();

	frame = newwin(LINES - 2 * DX, COLS - 2 * DY, DX, DY);
	box(frame, 0, 0);
	wrefresh(frame);

	keypad(frame, TRUE);
	scrollok(frame, TRUE);

	int start_row = 0;
	int start_col = 0;

	while(c != 27) {
		wclear(frame);
		box(frame, 0, 0);
		printColoredString(frame, 0, 5, keyname(c), 2);

		for (int i = 0; i < INNER_LINES; i++) {
			int current_row = start_row + i;
			writeNumStr(frame, i + INNER_DX, INNER_DY + 2, current_row);
			mvwaddstr(frame, i + INNER_DX, INNER_DY + 5, code[start_row + i] + start_col);
		}

		c = wgetch(frame);

		switch (c) {
			case KEY_LEFT:
				if (start_col > 0) {
					start_col--;
				}
				break;
			case KEY_RIGHT:
				start_col++;
				break;
			case KEY_DOWN:
				if (start_row < getCodeRows(code) - INNER_LINES) {
					start_row++;
				}
				break;
			case KEY_UP:
				if (start_row > 0) {
					start_row--;
				}
				break;
			case KEY_NPAGE:
				if (start_row < getCodeRows(code) - 2 * INNER_LINES) {
					start_row += INNER_LINES;
				} else {
					start_row = getCodeRows(code) - INNER_LINES;
				}
				break;
			case KEY_PPAGE:
				if (start_row >= INNER_LINES) {
					start_row -= INNER_LINES;
				} else {
					start_row = 0;
				}
				break;
		}
	}

	fclose(file);
	getch();
	delwin(frame);
	endwin();

	free(buf);
	for (int i = 0; i < getCodeRows(code); i++) {
		free(code[i]);
	}
	free(code);

	return 0;
}
