#include <stdio.h>
#include <ctype.h>
#include <string.h>

void removeVowels(char *str) {
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if (!isalpha(ch) || !strchr("AEIOUaeiou", ch)) {
            str[j] = ch;
            j++;
        }
    }
    str[j] = '\0';
}

int main() {
    char str[100];

    printf("Digite uma string: ");
    fgets(str, sizeof(str), stdin);

    // Remove as vogais da string
    removeVowels(str);

    printf("String sem vogais: %s\n", str);

    return 0;
}
