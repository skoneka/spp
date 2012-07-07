#ifndef _DB_TYPES_H
#define _DB_TYPES_H
#include "define.h"

typedef struct _st_rekord_lecturer
{
    int id;
    char name[MAX_NAME];
    char degree[MAX_DEGREE];
    char room[MAX_ROOM];
    char topic[MAX_TOPIC];
} st_rekord_lecturer;

typedef struct _st_rekord_topic
{
    int id;
    char name[MAX_NAME];
    char topic_type[MAX_TOPIC_TYPE];
    int hours;
    char date[MAX_DATE];
} st_rekord_topic;

typedef struct _st_rekord_student
{
    int id;
    char name[MAX_NAME];
    int index;
    char topic[MAX_TOPIC];
} st_rekord_student;


#endif
