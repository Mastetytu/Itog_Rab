#include <stdio.h>
#include <stdlib.h>

int Open_fail(FILE *fp,char nm,int i,char strok,int sz,char vid) {
	char sim;
    if ((fp = fopen(nm, vid)) == NULL)
    {
        printf("Не удалось открыть файл");
        getchar();
        return 0;
    }
    else
    {
        switch (i)
        {
        case 1:
            //чтение символа из файла
            fgetc(fp);
            break;
        case 2:
            //запись в файл
            scanf_s("&c", &sim);
            fputc(sim,fp);
            break;
        case 3:
            //запись строки
            strung(strok, sz);
            fgetc(&strok, sz, fp);
            break;
        case 4:
            strung(strok, sz);
            fputs(&strok, sz, fp);
            break;
        default:
            break;
        }
        fclose(fp);
        getchar();
        return 0;
    }

}
int strung(char strok,int  sz) {

}