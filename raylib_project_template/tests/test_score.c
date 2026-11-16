#include "score.h"
#include <stdio.h>

static int Check(int condition, const char *description)
{
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", description);
        return 0;
    }
    printf("PASS: %s\n", description);
    return 1;
}

int main(void)
{
    const char *path = "test_best_score_tmp.txt";
    int ok = 1;
    FILE *file;
    (void)remove(path);

    ok &= Check(LoadBestScore(path) == 0, "missing file is 0");
    ok &= Check(SaveBestScore(path, 7) == 1, "save score");
    ok &= Check(LoadBestScore(path) == 7, "load score");
    ok &= Check(SaveBestScore(path, -1) == 0, "reject negative score");
    ok &= Check(LoadBestScore(path) == 7, "rejected save keeps original value");

    file = fopen(path, "w");
    if (file != NULL) {
        fputs("invalid\n", file);
        fclose(file);
        ok &= Check(LoadBestScore(path) == 0, "invalid file is 0");
    } else {
        ok &= Check(0, "create invalid file");
    }

    (void)remove(path);
    return ok ? 0 : 1;
}
