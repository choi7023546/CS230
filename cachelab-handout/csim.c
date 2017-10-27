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
    cache -> sets = (Set*) malloc( (number_of_set) * sizeof(Set) );

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

int get_set ( int address, int set_index, int block_bit )
{
    int set = address >> block_bit;
    int one = ~ ( 0xffffffff << set_index );
    return ( set & one );
}

int get_target ( int address, int set_index, int block_bit )
{
    int target = address >> ( set_index + block_bit );
    int one = ~ ( 0xffffffff << ( 63 - set_index - block_bit ) );
    return ( target & one );
}

int find_index ( Cache* cache, int set, int target, int lines_per_set )
{
    int index=-1;
    int i;
    for ( i = 0 ; i < lines_per_set ; i++ ) {
        if ( ( cache->sets[set].lines[i].valid == 1 ) && ( cache->sets[set].lines[i].tag == target ) ) {
            index = i;
            break;
        }
    }

   return index;

}

// it controls a priority only.
int update ( Cache* cache, int set, int lines_per_set, int line_index,  int _case)
{
    // when store a data to a certain line i, we have to change its priority to 1, and some lines increase.
    // eviction(_case=1) --> find biggest priority and change it to 1, and change tag to new one of i. all other priority increase 1
    // not eviction(_case=2) --> not changing 0 priority. if a priority is smaller than i, increase 1.
    int i;
    int p;
    int index=0;
    // case 1 ; miss eviciton     
    if (_case == 1) {
        //biggest priority == lines_per_set
        for ( i = 0 ; i < lines_per_set ; i++ ) {
            if ( (cache -> sets[set].lines[i].priority) == lines_per_set ) {
                cache -> sets[set].lines[i].priority = 1;
                index = i;
            } else {
                cache -> sets[set].lines[i].priority++;            
            }
        }  
    }
    // case 2 : hit
    else if (_case == 2) {
        i=0;
        p = cache->sets[set].lines[line_index].priority;
        while( (cache->sets[set].lines[i].priority!=0) && (cache->sets[set].lines[i].priority < p) ) {
            cache->sets[set].lines[i].priority++;
            i++;
        }
        cache->sets[set].lines[line_index].priority = 1;
    }
    // case 3 : miss & not eviction
    else {
        i=0;
        while( cache->sets[set].lines[i].priority != 0 ) {
            cache->sets[set].lines[i].priority++;
            i++;
        }
        cache->sets[set].lines[i].priority = 1;
        index = i; 
    }

    return index;
}
// M 1234567, 1
// this has to control valid_line in _set struct. 
int parse ( Cache* cache, char* readline, int set_index, int block_bit, int lines_per_set ) 
{ 
    // case1 : valid_line ==0
    // case2 : valid_line == lines_per_set
    // case3 : some lines are valid 
    char operation = readline[0];
    char* address_p = strtok(&readline[2], ",");
    char* nothing;
    int address = (int)strtol(address_p, &nothing, 16);
    int target = get_target(address, set_index, block_bit);
    int set = get_set(address, set_index, block_bit);
   //  printf("operation is %c\n", operation);
   //  printf("address is %d\n", address);
   //  printf("target is %d\n", target);
   //  printf("set is %d\n", set);
    //case1 : all lines are invalid
    if (cache->sets[set].valid_line == 0) {
     //   printf("all lines are invalid\n");
       // printf("miss\n");
        cache->sets[set].lines[0].valid = 1;
        cache->sets[set].lines[0].tag = target;
        update(cache, set, lines_per_set, 0, 3);
        miss_count++;
        cache->sets[set].valid_line++;
        if (operation == 'M') {
            hit_count++;
        }
    }
    //case2 : all lines are valid
    else if (cache->sets[set].valid_line == lines_per_set) {
       // printf("all lines are valid\n");
        int index = find_index( cache, set, target, lines_per_set );
        // miss eviction
        if ( index == -1 ) {
       //    printf("miss eviction\n");
            int update_index = update( cache, set, lines_per_set, 0, 1);
         //   printf("------------index = %d---------",update_index );
            cache->sets[set].lines[update_index].tag = target;
            miss_count++;
            eviction_count++;
            if (operation == 'M') {
                hit_count++;
            }
        }
        // hit
        else {
           // printf("hit\n");
            update( cache, set, lines_per_set, index,2);
            hit_count++;
            if(operation == 'M') {
                hit_count++;
            }
        }
    }
    //case3 : some lines are valid
    else {
     //   printf("some lines are valid\n");
        int index = find_index( cache, set, target, lines_per_set );
        // miss
        if ( index == -1 ) {
       //     printf("miss\n");
            int update_index = update( cache, set, lines_per_set, 0, 3);
             cache->sets[set].lines[update_index].valid = 1;
             cache->sets[set].lines[update_index].tag = target;
             cache->sets[set].valid_line++;
             miss_count++;
             if (operation == 'M') {
                 hit_count++;
             }
        }
        // hit
        else {
         //   printf("hit\n");
            update( cache, set, lines_per_set, index, 2);
            hit_count++;
            if (operation == 'M') {
                hit_count++;
            }
        }
    } 
 //   printf("operation is %c\n", operation);
 //   printf("address is %d\n", address);
 //   printf("target is %d\n", target);
 //   printf("set is %d\n", set);
    return 0;
}



int main(int argc, char** argv)
{
   // printf("does printf work?\n");
    if (argc!=9) {
        exit(0);
    }
    //printf("reach here?\n");

    char c;
    int set_index;
    int lines_per_set;
    int block_bit;	
    char trace_file[50] ;
    char read_line[50];
    FILE* file;

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
            default:
                exit(0);
                break;
        }	     
    }
    Cache cache;
    initialize_cache( &cache, set_index, lines_per_set ); 
    file =  fopen( trace_file, "r");
 //   printf("right before while\n");
    while( fgets(read_line,50,file) != NULL ) {
 //       printf("while working\n");
        if ( read_line[0] == ' ' ) {
 //           printf("If printed, parse is the probelm!\n");
            parse( &cache, &read_line[1], set_index, block_bit, lines_per_set );    
        }
    
    }

    fclose(file);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
