#include <stdio.h>
#include <stdlib.h>

int Open_fail(FILE *fp,char nm,int i,char strok,int sz,char vid) {
	char sim;
    if ((fp = fopen(nm, vid)) == NULL)
    {
        printf("�� ������� ������� ����");
        getchar();
        return 0;
    }
    else
    {
        switch (i)
        {
        case 1:
            //������ ������� �� �����
            fgetc(fp);
            break;
        case 2:
            //������ � ����
            scanf_s("&c", &sim);
            fputc(sim,fp);
            break;
        case 3:
            //������ ������
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