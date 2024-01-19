// プログラミング言語:C
// コンパイル方法:gcc 22_12485-05-05.c
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#define WIDTH   (16)

const void *dump(const void *addr, size_t bytes)
{
    const unsigned char *p = addr;
    char text[WIDTH+1];
    unsigned i = 0;

    while (i < bytes) {
        if ((i % WIDTH) == 0) {
            printf("%6d: ", i);

            memset(text, '\0', sizeof(text));
        }


        printf("%02x ", *p);

        text[i % WIDTH] = isprint(*p) ? *p : '.';

        p++; i++;


        if ((i % WIDTH) == 0) {
            printf(": %s\n", text);
        }
    }

    if ((i % WIDTH) != 0) {
        printf("%*s: %s\n", (WIDTH - (i % WIDTH)) * 3, " ", text);
    }

    return addr;
}

const void *wt_dump(const void *addr, size_t bytes, FILE *fp)
{
    const unsigned char *p = addr;
    char text[WIDTH+1];
    unsigned i = 0;

    while (i < bytes) {
        if ((i % WIDTH) == 0) {
            fprintf(fp, "%6d: ", i);

            memset(text, '\0', sizeof(text));
        }


        fprintf(fp, "%02x ", *p);

        text[i % WIDTH] = isprint(*p) ? *p : '.';

        p++; i++;


        if ((i % WIDTH) == 0) {
            fprintf(fp, ": %s\n", text);
        }
    }

    if ((i % WIDTH) != 0) {
        fprintf(fp, "%*s: %s\n", (WIDTH - (i % WIDTH)) * 3, " ", text);
    }

    return addr;
}

int getFSZ(FILE *fp){
	int size = 0;
	fseek( fp, 0, SEEK_END );
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET );
	
	return size;
}

int main(void){
    FILE*fp1;
	FILE*fp2;
    FILE*fp3;
    FILE*fp4;
    FILE*fo;
    FILE*fo2;
    unsigned char input_binary1[200000]; //平文をブロック暗号化したもの
    unsigned char input_binary2[200000]; //平文を1文字変えたものをブロック暗号化したもの
    unsigned char input_binary3[200000]; //平文を換字暗号化したもの
    unsigned char input_binary4[200000]; //平文を1文字変えたものを換字暗号化したもの
    unsigned char err[200000]; // 誤差(ブロック暗号)
    unsigned char err2[200000]; // 誤差(換字暗号)

    int fsize = 0;
    int fsize_ = 0;

    /* 入力ファイルオープン */
	if((fp1 = fopen("crypted", "rb")) == NULL)
	{
        
		puts("file not open");
		exit(0);
	}
	if((fp2 = fopen("crypted_", "rb")) == NULL)
	{
		puts("file not open");
		exit(0);
	}
    if((fp3 = fopen("cipher.txt", "rb")) == NULL)
	{
		puts("file not open");
		exit(0);
	}
    if((fp4 = fopen("cipher_.txt", "rb")) == NULL)
	{
		puts("file not open");
		exit(0);
	}
    if((fo = fopen("block_error.txt", "w")) == NULL)
	{
		puts("er");
		exit(0);
	}
    if((fo2 = fopen("substitution_error.txt", "w")) == NULL)
	{
		puts("er");
		exit(0);
	}

    fsize = getFSZ(fp1);
    fsize_ = getFSZ(fp3);

    fread(input_binary1, sizeof(unsigned char), fsize, fp1);
    fread(input_binary2, sizeof(unsigned char), fsize, fp2);
    fread(input_binary3, sizeof(unsigned char), fsize_, fp3);
    fread(input_binary4, sizeof(unsigned char), fsize_, fp4);

    /*XOR計算*/
    for(int i=0;i<fsize;i++){
        err[i] = input_binary1[i]^input_binary2[i];
    }
    for(int i=0;i<fsize_;i++){
        err2[i] = input_binary3[i]^input_binary4[i];
    }
    
    /*結果のdump*/
    printf("\n\n");
	printf("******************************************************\n");
	printf("************        Block cipher XOR      ************\n");
	printf("******************************************************\n\n\n");
    dump(err, fsize);
    printf("\n\n");
	printf("********************************************************\n");
	printf("**********        Substitution cipher XOR     **********\n");
	printf("********************************************************\n\n\n");
    dump(err2, fsize_);

    wt_dump(err, fsize, fo);
    wt_dump(err2, fsize_, fo2);

    printf("\n\n");

    /*終了処理*/
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fo);
    fclose(fo2);

    return 0;
}