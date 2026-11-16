#ifndef COURSE_SCORE_H
#define COURSE_SCORE_H

/* Reads a non-negative integer. Returns 0 if file missing or invalid. */
int LoadBestScore(const char *file_path);

/* Returns 1 on successful save; returns 0 on an error. */
int SaveBestScore(const char *file_path, int best_score);

#endif
