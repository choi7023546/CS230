#include "cachelab.h"
#include<getopt.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int hit_count = 0;
int miss_count = 0;
int eviction_count = 0;


typedef struct _Line
{
    int valid;
    int tag;
    int priority;

} Line;

typedef struct _Set
{
    Line* lines;
    int valid_line;

} Set;

typedef struct _Cache
{
    Set* sets;

} Cache;

int initialize_cache ( Cache* cache, int set_index, int lines_per_set)
{
    // Cache -> sets = malloc ( number of sets * sizeof(Set)  ) 
    // Cache -> sets[i].lines =  malloc( lines_per_set * sizeof(Line) ) 
    // Cache -> sets[i].lines[j].valid = 0
    // Cache -> sets[i].lines[j].priority = 0
    int number_of_set = ( 2 << set_index );
    int i,j;
    cache -> sets = (Set*) malloc( (number_of_set) * sizeof(Set) )

    for ( i=0; i<number_of_set ; i++ ) {
        cache -> sets[i].lines = (Line*) malloc( (lines_per_set) * sizeof(Line) );
        cache -> sets[i].valid_line = 0;
        for ( j=0 ; j<lines_per_set ; j++ ) {
            cache -> sets[i].lines[j].valid = 0;
            cache -> sets[i].lines[j].priority = 0;
        }
    }

    return 0;
}

int update ( Cache* cache )
{
    // when store a data to a certain line i, we have to change its priority to 1, and some lines increase.
    // eviction --> find biggest priority and change it to 1, and change tag to new one of i. all other priority increase 1
    // not eviction --> not changing 0 priority. if a priority is smaller than i, increase 1.     
    
    return 0;
}

//int parse ( Cache* cache, char* readline ) 
//{
//    return 0;
//}



int main(int argc, char** argv)
{
    if (argc!=9) {
        exit(0);
    }

    char c;
    int set_index;
    int lines_per_set;
    int block_bit;	
    char* trace_file ;
    while ( ( c = getopt(argc, argv, "s:E:b:t:") ) != -1) {
        switch(c) {
            case 's':
                set_index = atoi(optarg);
                break;

            case 'E':
                lines_per_set = atoi(optarg);
                break;

            case 'b':
                block_bit = atoi(optarg);
                break;

            case 't':
                strcpy(trace_file, optarg);
                break;
        }	     
    }
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
