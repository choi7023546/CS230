/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{   // we can devide a whole matrix into small blocks which are 8x8 matrices.
    int i;
    int j;
    int tmp;
    int block_col;
    int block_row;
    int tmp1;
    int tmp2;

    if ( M == 32 ) {
        for ( block_col = 0 ; block_col < M ; block_col+=8) {
            for ( block_row = 0 ; block_row < N ; block_row+=8 ) {
                for ( i = block_row ; i < block_row + 8 ; i++ ) {
                      if (block_col == block_row) {
                           tmp = A[i][i]; 
                        }
                    for ( j = block_col ; j < block_col + 8 ; j++ ) {
                        if ( i != j ) {
                            B[j][i] = A[i][j];
                        }
                    } 
                      if (block_col == block_row) {
                        B[i][i] = tmp;
                     }
                }
            } 
        }   
    } 
    else if ( M == 64) {
        for ( block_col = 0 ; block_col<M ; block_col+=4) {
            for ( block_row = 0 ; block_row < N ; block_row += 4) {
                for ( i = block_row ; i<block_row +4 ; i++) {
                    for ( j = block_col ; j < block_col +4 ; j++) {
                        if ( (i-block_row)==(j-block_col) )  {
                            tmp = A[i][j];
                            tmp1 = i;
                            tmp2 = j;
                        } else {
                            B[j][i] = A[i][j];
                           
                        }
                    }
                    B[tmp2][tmp1] = tmp;
                }
                 
            }
        }
 
    } else {
        for ( block_col = 0 ; block_col<M ; block_col += 8) {
            for ( block_row = 0 ; block_row<N ; block_row += 8 ) {
                for ( i = block_row ; i<block_row+8 ; i++) {
                    if(i>=N) {
                        break;
                    }
                    for ( j = block_col ; j < block_col + 8 ; j++) {
                        if (j>=M){
                            break;
                        }
                        B[j][i] = A[i][j];
                    }
                }
            }
        }
    }

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

