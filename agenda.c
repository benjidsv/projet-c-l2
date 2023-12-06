#include "agenda.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *ScanString(int bufferSize) {
    char buffer[bufferSize];
    fgets(buffer, bufferSize, stdin);

    int i = 0;
    for (; i < bufferSize; ++i) if (!isalpha(buffer[i])) break;

    // i est la fin de la chaîne
    char *ret = malloc(i); //sizeof char = 1
    strncpy(ret, buffer, i);

    return ret;
}

contact *MakeContact(char *name, char *firstName) {
    contact *new = malloc(sizeof(contact));
    new->name = name;
    new->firstName = firstName;

    return new;
}

t_date *MakeDate(int day, int month, int year) {
    t_date *new = malloc(sizeof(t_date));
    new->day = day;
    new->month = month;
    new->year = year;

    return new;
}

t_time *MakeTime(int hours, int minutes) {
    t_time *new = malloc(sizeof(t_time));
    new->hours = hours;
    new->minutes = minutes;

    return new;
}

rdv *MakeRDV(t_date date, t_time time, t_time duration, char *topic) {
    rdv *new = malloc(sizeof(rdv));
    new->date = date;
    new->time = time;
    new->duration = duration;
    new->topic = topic;

    return new;
}
