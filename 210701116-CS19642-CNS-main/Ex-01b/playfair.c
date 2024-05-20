#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SECRET "tdkxubwgf"

char output[100];
char key[5][5];
int bucket[26];
char plain[100];
int idx[2];

void generateKey(char* secret){
    int keyPtr = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            while(bucket[secret[keyPtr] - 'a'] != 0 && keyPtr < strlen(secret)){
                keyPtr++;
            }
            if(keyPtr < strlen(secret)){
                bucket[secret[keyPtr] - 'a'] = 1;
                key[i][j] = secret[keyPtr++];
            } else {
                for(int k = 0; k < 26; k++){
                    if(bucket[k] == 0){
                        key[i][j] = 'a' + k;
                        bucket[k] = 1;
                        break;
                    }
                }
            }
            if(bucket[8] == 1 || bucket[9] == 1){
                bucket[8] = 1;
                bucket[9] = 1;
            }
        }
    }
}

bool digram(){
    for(int i = 0; i < strlen(plain); i+=2){
        if(plain[i] == plain[i + 1]){
            for(int j = strlen(plain); j > i + 1; j--){
                plain[j] = plain[j - 1];
            }
            plain[i + 1] = (plain[i + 1] == 'y') ? 'z' : 'y';
        }
    }
    if(strlen(plain) % 2 == 1){
        plain[strlen(plain)] = (plain[strlen(plain) - 1] == 'y') ? 'z' : 'y';
    }
    return true;
}

void indexOf(char monogram){
    char mutation;
    int i, j;
    if(monogram == 'i' || monogram == 'j'){
        mutation = (monogram == 'i') ? 'j' : 'i';
    } else {
        mutation = monogram;
    }
    for(i = 0; i < 5; i++){
        for(j = 0; j < 5; j++){
            if(key[i][j] == monogram || key[i][j] == mutation){
                idx[0] = i;
                idx[1] = j;
                return;
            }
        }
    }
}

void encrypt(){
    int outIdx = 0, mono1_x, mono1_y, mono2_x, mono2_y;
    if(digram()){
        for(int i = 0; i < strlen(plain); i+=2){
            indexOf(plain[i]);
            mono1_x = idx[0];
            mono1_y = idx[1];
            indexOf(plain[i + 1]);
            mono2_x = idx[0];
            mono2_y = idx[1];
            if(mono1_x == mono2_x){
                output[outIdx++] = key[mono1_x][(mono1_y + 1) % 5];
                output[outIdx++] = key[mono2_x][(mono2_y + 1) % 5];
            } else if(mono1_y == mono2_y){
                output[outIdx++] = key[(mono1_x + 1) % 5][mono1_y];
                output[outIdx++] = key[(mono2_x + 1) % 5][mono2_y];
            } else {
                output[outIdx++] = key[mono1_x][mono2_y];
                output[outIdx++] = key[mono2_x][mono1_y];
            }
        }
    }
}

void decrypt(){
    int outIdx = 0, mono1_x, mono1_y, mono2_x, mono2_y;
    if(digram()){
        for(int i = 0; i < strlen(plain); i+=2){
            indexOf(plain[i]);
            mono1_x = idx[0];
            mono1_y = idx[1];
            indexOf(plain[i + 1]);
            mono2_x = idx[0];
            mono2_y = idx[1];
            if(mono1_x == mono2_x){
                int y1 = (mono1_y == 0) ? 5 : mono1_y;
                int y2 = (mono2_y == 0) ? 5 : mono2_y;
                output[outIdx++] = key[mono1_x][(y1 - 1) % 5];
                output[outIdx++] = key[mono2_x][(y2 - 1) % 5];
            } else if(mono1_y == mono2_y){
                int x1 = (mono1_x == 0) ? 5 : mono1_x;
                int x2 = (mono2_x == 0) ? 5 : mono2_x;
                output[outIdx++] = key[(x1 - 1) % 5][mono1_y];
                output[outIdx++] = key[(x2 - 1) % 5][mono2_y];
            } else {
                output[outIdx++] = key[mono1_x][mono2_y];
                output[outIdx++] = key[mono2_x][mono1_y];
            }
        }
    }
}


int main()
{
    int choice;
    generateKey(SECRET);
    
    printf("PLAYFAIR CIPHER:\n(choose an operation)\n");
    printf("1. Encrypt\n2. Decrypt\nEnter your option : ");
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            printf("Enter plain text : ");
            scanf("%s", plain);
            encrypt();
            break;
        case 2:
            printf("Enter cipher text : ");
            scanf("%s", plain);
            decrypt();
            break;
        default:
            printf("Invalid choice");
            break;
    }

    printf("After Encryption/Decryption : %s", output);

    return 0;
}

