 #include <stdio.h>
#include<string.h>

char output[100];

void encrypt(char* plain, int length, int key){
    for(int i = 0; i < length; i++){
        output[i] = (char)(plain[i] + key) % 128;
    }
}

void decrypt(char* plain, int length, int key){
    for(int i = 0; i < length; i++){
        output[i] = (char)(((plain[i] >= key) ? plain[i] : key) - ((plain[i] <= key) ? plain[i] : key));
    }
}

int main()
{
    int choice;
    char input[100] = { '\0' };
    
    printf("CAESAR CIPHER:\n(choose an operation)\n");
    printf("1. Encrypt\n2. Decrypt\nEnter your option : ");
    
    scanf("%d", &choice);
    
    switch(choice){
        case 1:
            printf("Enter Plain Text : ");
            scanf("%s", input);
            encrypt(input, strlen(input), 3);
            printf("The cipher text : %s", output);
            break;
        case 2:
            printf("Enter Cipher Text : ");
            scanf("%s", input);
            decrypt(input, strlen(input), 3);
            printf("The plain text : %s", output);
            break;
        default:
            printf("Invalid choice");
            break;
    }

    return 0;
}

