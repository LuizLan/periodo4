#include <stdio.h>

int main (){

    short i, criticos;
    short hora, minuto, critico, n;

    while (scanf("%hd", &n) != EOF){   

        criticos = 0;
        short tempo_total = 420;

        for (i = 0; i < n; ++i){

            scanf("%hd %hd %hd", &hora, &minuto, &critico);

            while (tempo_total < (hora * 60) + minuto)
                tempo_total += 30;
            
            if (tempo_total - ((hora * 60) + minuto) > critico)
                ++criticos;

            tempo_total += 30;
        }

         printf("%hd\n", criticos);   
    }

    return 0;
}