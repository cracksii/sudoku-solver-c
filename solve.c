#include <stdio.h>

char field[9][9];

void load(char*);
void empty(void);
int find(int*, int*);
int solve(void);
int valid(const int*, const int*, const int*);
void print(void);

int main(int argc, char* argv[]) {
    if(argc > 1) {
        load(argv[1]);
    }
    else {
        empty();
    }
    
    if(solve() == 1) {
        printf("Field can't be solved");
    }
    else {
        print();
    }
}

void load(char* path) {
    FILE* file = fopen(path, "r");
    char buffer[100];
    int i = 0;
    while(!feof(file)){
        fgets(buffer, 100, file);
        for(int j = 0; j < 9; j++) {
            field[i][j] = buffer[j];
        }
        i++;
    }

    fclose(file);
}

void empty(void) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++){
            field[i][j] = ' ';
        }
    }
}

int find(int* x, int* y) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(field[i][j] == ' ') {
                *x = j;
                *y = i;
                return 0;
            }
        } 
    }
    return 1;
}

int solve(void) {
    int x, y;
    if(find(&x, &y) == 1) {
        return 0;
    }

    for(int i = 1; i <= 9; i++) {
        if(valid(&x, &y, &i) == 0) {
            field[y][x] = i + '0';

            if(solve() == 0) {
                return 0;
            }
            else {
                field[y][x] = ' ';
            }
        }
    }
    return 1;
}

int valid(const int* x, const int* y, const int* number) {
    // Check for occurencies in same block
    // Start is y or x end is (y / 3 + 1) * 3
    for(int i = *y / 3 * 3; i < (*y / 3 + 1) * 3; i++) {  // Loop over all y fields in current block
        for(int j = *x / 3 * 3; j < (*x / 3 + 1) * 3; j++) {  // Loop over all x fields in current bolck
            if(field[i][j] == *number + '0') {
                return 1;
            }
        }
    }

    // Check for same number occurencies in the same row
    for(int i = 0; i < 9; i++) {
        if(i == *x) {  // Skip if we are checking our newly inserted number
            continue;
        }
        if(field[*y][i] == *number + '0') { // if same number is already in row
            return 1;  // return invalid
        }
    }

    // Check for same number occurencies in the same column
    for(int i = 0; i < 9; i++) {
        if(i == *y) {
            continue;
        }
        if(field[i][*x] == *number + '0') {
            return 1; 
        }
    }
    return 0;  // Number passed all tests, return valid
}

void print(void) {
    for(int i = 0; i < 9; i++) {
        if(i % 3 == 0 && i > 0) {
            printf("-----------------------------\n");
        }
        for(int j = 0; j < 9; j++) {
            if(j % 3 == 0 && j > 0) {
                printf("| ");
            }
            printf("%c  ", field[i][j]);
        }
        printf("\n");
    }
}
