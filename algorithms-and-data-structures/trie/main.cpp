#include "Trie.h"
#include <stdio.h>

int main(){
    int commands;
    int min, max;
    int n, k;
    char sign;
    int number;
    scanf("%d", &commands);
    scanf("%d %d", &min, &max);
    scanf("%d %d", &n, &k);
    Trie trie(n, k);

    for(int i = 0; i < commands; i++){
        scanf(" %c", &sign);
        switch (sign)
        {
        case 'I':
            scanf("%d", &number);
            trie.insert(&number);
            break;
        case 'L':
            scanf("%d", &number);
            if(trie.find(&number)){
                printf("%d exist\n", number);
            } else {
                printf("%d not exist\n", number);
            }
            break;
        case 'D':
            scanf("%d", &number);
            trie.remove(&number);
            break;
        case 'P':
            trie.print();
            break;
        default:
            break;
        }
    }

    return 0;
}