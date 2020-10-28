#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGS 2
#define FILENAME "todolist.txt"

/** Megvizsgáljuk, hogy a szám a megadott értéken belül van-e. Balról zárt, jobbról nyílt. */
int inRange(int num, int low, int high) {
	return (low <= num) && (num < high);
}

/** Időformátum vizsgálata */
int isValidTime(char *time) {
	int hour;
	int minute;
	
	/* Feldaraboljuk a sztinget */
	hour = atoi(strtok(time, ":"));
	minute = atoi(strtok(NULL, ":"));
	
	/* Majd visszaállítjuk eredeti állapotába, ezzel beállítva a 2 számjegyes formátumot */
	snprintf(time, sizeof(time), "%.2d:%.2d", hour, minute);
	
	return inRange(hour, 0, 24) && inRange(minute, 0, 60);
}

/** Feladatformátum vizsgálata */
int isValidTodo(char *task) {
	int i;
	
	/* Végigfut a sztringen, ha egy karakter nem karakter, jelezzük hogy hibás bemenet */
	for(i=0;i<strlen(task);i++) {
		if(!isalpha(task[i])) return 0;
	}
	
	/* Egyéb esetben rendben van */
	return 1;
}

/** Sor fájlba írása */
void writeToFile(FILE *file, char *time, char *task) {
	fprintf(file, "%s - %s\n", time, task);
}

/** Belépő metódus, argumentumok átvétele */
int main(int argc, char *argv[]) {
	/* Argumentumok száma, itt figyeljünk rá, hogy az első elem a futtatott program neve */
	int args = argc - 1;
	
	/* Minimum bemenet vizsgálata, hibás bemenet esetén a program leáll */
	if(args < MIN_ARGS) {
		printf("Hibás bemenet!\n");
		exit(1);
	}
	
	/* Ciklusváltozó */
	int i;
	/* Időre mutató pointer */
	char *time;
	/* Feladatra mutató pointer */
	char *task;
	/* File pointer */
	FILE *file;
	
	/* Ha van egy extra bemenetünk, azaz páratlan számú paraméterünk, akkor figyelmen kívül hagyjuk */
	if(argc % 2 == 0) argc--;
	
	/* File megnyitása */
	file = fopen(FILENAME, "w");
	
	/* Bejárjuk a kapott argumentumokat páronként, első elemtől kezdjük, mivel a 0. a futtatott fájl */
	for(i=1;i<argc;i++) {
		time = argv[i++]; //Itt nő i értéke egyel, így tudunk párosával lépni
		task = argv[i];
		
		if(isValidTime(time) == 1 && isValidTodo(task) == 1) {
			writeToFile(file, time, task);
		}else printf("Hibás bemenet!\n");
	}
	
	/* File bezárása */
	fclose(file);
	
	/* Jelezzük a rendszer felé, hogy minden rendben ment */
	return 0;
}
