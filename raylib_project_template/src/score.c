#include "score.h"
#include <stdio.h>

int LoadBestScore(const char *file_path)
{
    FILE *fp;
    int value = 0;
    if (file_path == NULL) return 0;

    fp = fopen(file_path, "r");
    if (fp == NULL) return 0;
    if (fscanf(fp, "%d", &value) != 1 || value < 0) value = 0;
    fclose(fp);
    return value;
}

int SaveBestScore(const char *file_path, int best_score)
{
    FILE *fp;
    int ok;
    if (file_path == NULL || best_score < 0) return 0;

    fp = fopen(file_path, "w");
    if (fp == NULL) return 0;
    ok = (fprintf(fp, "%d\n", best_score) > 0);
    if (fclose(fp) != 0) ok = 0;
    return ok;
}
