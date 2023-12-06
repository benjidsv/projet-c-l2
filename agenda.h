#ifndef PROJET_C_L2_AGENDA_H
#define PROJET_C_L2_AGENDA_H

char *ScanString(int bufferSize);

typedef struct contact {
    char *name;
    char *firstName;
    char *key;
} contact;

contact *MakeContact(char *name, char *firstName);

typedef struct t_date {
    int day;
    int month;
    int year;
} t_date;

t_date *MakeDate(int day, int month, int year);

typedef struct t_time {
    int hours;
    int minutes;
} t_time;

t_time *MakeTime(int hours, int minutes);

typedef struct rdv {
    t_date date;
    t_time time;
    t_time duration;
    char *topic;
} rdv;

rdv *MakeRDV(t_date date, t_time time, t_time duration, char *topic);

typedef struct r_cell {
    rdv r;
    struct r_cell *next;
} r_cell;

r_cell *MakeRCell(rdv r);

typedef struct entry {
    contact c;
    r_cell *rdvs;
} entry;

entry *MakeEntry(contact c);

#endif //PROJET_C_L2_AGENDA_H
