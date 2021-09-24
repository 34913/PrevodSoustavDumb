#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define EXTENDED 1
#define _MAX 1000

uint64_t prevod(char *out, char *cislo, uint64_t pocet, uint32_t soustava_from, uint32_t soustava_to);
uint64_t mocnina(uint64_t cislo, uint64_t pocet);
bool cteni(char *pole, uint32_t max, uint64_t *index);
bool vypis(char *pole, uint64_t delka);
bool chyba(int a);



int main(){
#if EXTENDED
    uint32_t pocet_cisel;
	char cislo[_MAX];
	char out[_MAX];
    uint64_t delka = 0;
    uint32_t soustava_from = 10, soustava_to = 8;

    printf("Zadej pocet cisel na prevedeni: ");
    if(chyba(scanf("%d", &pocet_cisel)))
		return 1;
    while(getchar() != '\n');


    printf("Format: cislo na prevadeni, ze soustavy, do soustavy\n");
    system("pause");

    if(pocet_cisel > 0){
        if(pocet_cisel != 1){
            for(uint32_t i = 0; i < pocet_cisel; i++) {
                delka = 0;

                if(cteni(cislo, _MAX, &delka) == 0){
                    printf("Max znaku je %d\n", _MAX);
                    return 1;
                }
				if (chyba(scanf("%d", &soustava_from)))
					return 1;
				if (chyba(scanf("%d", &soustava_to)))
					return 1;
                while(getchar() != '\n');

                if(soustava_from != 1 && soustava_to != 1 && soustava_from != 0 && soustava_to != 0){
                    if(soustava_from != soustava_to){
                        delka = prevod(out, cislo, delka, soustava_from, soustava_to);
                        vypis(out, delka);
                    }
                    else
                        vypis(cislo, delka);
                }
                else
                    printf("Soustava 1 nebo 0 neni");

            }
        }
        else {
            delka = 0;

            if(cteni(cislo, _MAX, &delka) == 0){
                printf("Max znaku je %d\n", _MAX);
                return 1;
            }

			if (chyba(scanf("%d", &soustava_from)))
				return 1;
			if (chyba(scanf("%d", &soustava_to)))
				return 1;
			while (getchar() != '\n');

            if(soustava_from != 1 && soustava_to != 1){
                if(soustava_from != soustava_to){
                    delka = prevod(out, cislo, delka, soustava_from, soustava_to);
                    vypis(out, delka);
                }
                else
                    vypis(cislo, delka);
            }
            else
                printf("Soustava 1 neni");
        }
    }
    else
        printf("Zkus napsat alespon jedna\n");

#else
    uint32_t pocet_cisel;
    char cislo[_MAX];
    char out[_MAX];
    uint64_t delka = 0;

    scanf("%d", &pocet_cisel);
    while(getchar() != '\n');

    if(pocet_cisel > 0){
        if(pocet_cisel != 1){
            for(uint32_t i = 0; i < pocet_cisel; i++) {
                delka = 0;
                if(cteni(cislo, _MAX, &delka) == 0){
                    printf("Max znaku je %d\n", _MAX);
                    return 1;
                }
                delka = prevod(out, cislo, delka, 10, 8);

                vypis(out, delka);
            }
        }
        else {
            delka = 0;

            if(cteni(cislo, _MAX, &delka) == 0){
                printf("Max znaku je %d\n", _MAX);
                return 1;
            }

            delka = prevod(out, cislo, delka, 10, 8);

            vypis(out, delka);
        }
    }
    else
        printf("Zkus napsat alespon jedna\n");
#endif

    return 0;
}

uint64_t prevod(char *out, char *cislo, uint64_t pocet, uint32_t soustava_from, uint32_t soustava_to){
    uint64_t deset = 0;
    char use;
    uint64_t num;
    uint64_t delka = 0;

    if(soustava_from != 10) {
        for(uint64_t i = 0; i < pocet; i++) {
            use = cislo[llabs(i - (pocet - 1))];

            if(use >= '0' && use <= '9') {
                if((use - '0') > soustava_from){
                    printf("Mimo soustavu\n");
                    return delka;
                }
                deset += ((use - '0') * mocnina(soustava_from, i));
            }
            else if(use >= 'A' && use <= 'Z') {
                if(((use - 'A') + ('9' - '0')) > soustava_from){
                    printf("Mimo soustavu\n");
                    return delka;
                }
                deset += (((use - 'A') + ('9' - '0') + 1) * mocnina(soustava_from, i));
            }
            else if(use >= 'a' && use <= 'z') {
                if(((use - 'a') + ('Z' - 'A')) > soustava_from){
                    printf("Mimo soustavu\n");
                    return delka;
                }
                deset += (((use - 'a') + ('Z' - 'A') + ('9' - '0') + 1) * mocnina(soustava_from, i));
            }
            else {
                printf("Nezadavej jine znaky\n");
                return 0;
            }
        }

        if(soustava_to == 10){
            num = deset;
            for(delka = 0; num != 0; delka++){
                num = num / 10;
            }

            uint64_t num2 = deset;
            for(uint64_t i = 0; i < delka; i++){
                num = num2 % 10;
                num2 = num2 / 10;

                if(num >= 0 && num <= ('9' - '0')){
                    use = (num + '0');
                }
                else if(num >= ('9' - '0' + 1) && num <= (('Z' - 'A') + ('9' - '0'))){
                    use = (num - ('9' - '0' + 1) + 'A');
                }
                else if(num >= (('Z' - 'A') + ('9' - '0') + 1) && num <= (('z' - 'a') + ('Z' - 'A') + ('9' - '0'))){
                    use = (num - (('Z' - 'A') + ('9' - '0') + 1) + 'a');
                }
                else{
                    printf("%s radek %d\n", __FILE__, __LINE__);
                    while(1);
                }

                out[llabs(i - (delka - 1))] = use;

            }
        }
    }
    else{
        deset = 0;
        for(uint8_t i = 0; i < pocet; i++){
            deset += (cislo[i] - '0') * (mocnina(10, llabs(i - (pocet - 1))));
        }
    }



    if(soustava_to != 10){
        num = deset;
        for(delka = 0; deset != 0; delka++){
            deset = deset / soustava_to;
        }
        deset = num;

        for(uint64_t i = 0; i < delka; i++){
            num = deset % soustava_to;
            deset = deset / soustava_to;

            if(num >= 0 && num <= ('9' - '0')){
                use = (num + '0');
            }
            else if(num >= ('9' - '0' + 1) && num <= (('Z' - 'A') + ('9' - '0'))){
                use = (num - ('9' - '0' + 1) + 'A');
            }
            else if(num >= (('Z' - 'A') + ('9' - '0') + 1) && num <= (('z' - 'a') + ('Z' - 'A') + ('9' - '0'))){
                use = (num - (('Z' - 'A') + ('9' - '0') + 1) + 'a');
            }
            else{
                printf("%s radek %d\n", __FILE__, __LINE__);
                exit(1);
            }

            out[llabs(i - (delka - 1))] = use;

        }

    }

    return delka;
}

uint64_t mocnina(uint64_t cislo, uint64_t pocet){
    if(pocet == 0)
        return 1;
    if(pocet == 1)
        return cislo;
    return (cislo * mocnina(cislo, pocet - 1));
}

bool cteni(char *pole, uint32_t max, uint64_t *index){
    if(*index == max)
        return 0;
    char ch = getchar();

    if(ch == ' ' || ch == '\n'){
        return 1;
    }

    pole[*index] = ch;
    *index = *index + 1;
    return cteni(pole, max, index);
}

bool vypis(char *pole, uint64_t delka){
    for(uint64_t i = 0; i < delka; i++){
        putc(pole[i], stdout);
    }
    putc('\n', stdout);
    putc('\n', stdout);

    return 1;
}

bool chyba(int a) {
	if (a == NULL || a == EOF) {
		if (a == NULL)
			printf("Spatny input\n");
		else if (a == EOF)
			perror("Chyba: ");
		return 1;
	}
	return 0;

}
