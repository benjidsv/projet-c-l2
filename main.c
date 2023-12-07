#include <stdlib.h>
#include <string.h>
#include "agenda.h"
#include "al_list.h"
#include "example_list.h"

#define  MAX_INPUT_LENGTH 32

al_list *list;

// Lis un entier entre minValue et maxValue et retourne la saisie
int ReadIntBetween(const int minValue, const int maxValue) {
    char *end, input[MAX_INPUT_LENGTH];
    long inputAsLong;

    // On entre dans une boucle qui se répète tant que la saisie est invalide (pas un entier / pas entre min et max)
    printf("> ");
    while (fgets(input, MAX_INPUT_LENGTH, stdin)) { // On récupère la saisie
        // On convertit la saisie en entier avec strtol (string to long)
        inputAsLong = strtol(input, &end, 10);
        // Si la fin est égale à l'entrée originale / la fin n'est pas une nouvelle ligne (dernier caractère avec fgets)
        // cela veut dire qu'il y a eu un problème (très probablement que la saisie est invalide)
        // On vérifie aussi que l'entrée est bien entre min et max
        if (end == input || *end != '\n' || inputAsLong < minValue || inputAsLong > maxValue) {
            printf("Saisie invalide - entrez une valeur appropriée\n> ");
        } else break; // Sinon la saisie est valide
    }

    return (int)inputAsLong;
}

void DisplayRDV(al_cell *cell, int showNumbers) {
    r_cell *next = cell->value.rdvs;
    if (next == NULL) {
        printf("Vous n'avez aucun rendez-vous avec cette personne.\n");
        return;
    }
    int i = 1;
    while (next != NULL) {
        if (showNumbers) printf("%d | ", i);
        printf("%s - le %d/%d/%d à %dh%d pendant %dh%d\n", next->r.topic, next->r.date.day, next->r.date.month,
               next->r.date.year, next->r.time.hours, next->r.time.minutes, next->r.duration.hours,
               next->r.duration.minutes);
        next = next->next;
        i++;
    }
}

void AddRDV(al_cell *cell) {
    printf("Saisissez l'objet du rendez-vous : ");
    char *topic = ScanString(MAX_INPUT_LENGTH);
    printf("Saisissez la date du rendez-vous :\nJour ");
    int day = ReadIntBetween(0, 32);
    printf("Mois ");
    int month = ReadIntBetween(0, 13);
    printf("Année ");
    int year = ReadIntBetween(-10000, 10000);
    printf("Saisissez l'heure du rendez-vous ");
    int hour = ReadIntBetween(0, 25);
    printf("Saisissez les minutes de l'heure du rendez-vous ");
    int minutes = ReadIntBetween(-1, 61);
    printf("Saisissez la durée du rendez-vous (heures) ");
    int durationH = ReadIntBetween(-10000, 10000);
    printf("Saisissez la durée du rendez-vous (minutes) ");
    int durationM = ReadIntBetween(-1, 61);
    t_date date = *MakeDate(day, month, year);
    t_time time = *MakeTime(hour,minutes);
    t_time duration = *MakeTime(durationH, durationM);

    rdv new = *MakeRDV(date, time, duration, topic);
    r_cell* newCell = MakeRCell(new);
    if (cell->value.rdvs == NULL) cell->value.rdvs = newCell;
    else {
        r_cell *next = cell->value.rdvs;
        while (next->next != NULL) {
            if (CompareDates(next->next->r.date, newCell->r.date)) break;
            next = next->next;
        }

        newCell->next = next->next;
        next->next = newCell;
    }
}

void DeleteRDV(al_cell *cell) {
    r_cell *next = cell->value.rdvs;
    if (next == NULL) return;
    printf("Saisissez le numéro du rendez-vous à supprimer (-1 pour annuler):\n");
    int choice = ReadIntBetween(-2, 10000);
    if (choice == -1) return;
    if (next->next == NULL) {
        // S'il n'y a qu'un élément dans la liste on le supprime directement
        cell->value.rdvs = NULL;
        return;
    }

    for (int i = 0; i < choice - 2; ++i) {
        if (next->next == NULL) return;
        next = next->next;
    }

    next->next = next->next->next;
}

void ContactMenu(al_cell *cell) {
    printf("Contact : %s %s\n", cell->value.c.firstName, cell->value.c.name);
    while (1) {
        printf("1 - Voir les rendez-vous\n2 - Ajouter un rendez-vous\n3 - Supprimer un rendez-vous\n4 - Retour\n");
        int choice = ReadIntBetween(0, 5);
        switch (choice) {
            case 1:
                DisplayRDV(cell, 0);
                break;
            case 2:
                AddRDV(cell);
                break;
            case 3:
                DisplayRDV(cell, 1);
                DeleteRDV(cell);
                break;
            case 4:
                return;
        }
    }
}

void SearchContact() {
    printf("Saissisez le nom de famille de votre contact: ");
    char *name = ScanString(MAX_INPUT_LENGTH);
    printf("Saissisez le prénom de votre contact: ");
    char *firstName = ScanString(MAX_INPUT_LENGTH);
    char *key = MakeContact(name, firstName)->key;
    al_cell *found = SearchValueLevel0(list, key);
    if (found == NULL) {
        printf("Ce contact n'existe pas.");
        return;
    }
    ContactMenu(found);
}

void CreateContact() {
    printf("Saisissez le prénom du contact: ");
    char *firstName = ScanString(MAX_INPUT_LENGTH);

    printf("Saisissez le nom de famille du contact: ");
    char *name = ScanString(MAX_INPUT_LENGTH);
    contact c = *MakeContact(name, firstName);
    entry e = *MakeEntry(c);
    al_cell *cell = MakeCell(e);
    InsertCell(list, cell, 1);
}

int main() {
    printf("Gestionnaire d'agenda - Benjamin Arbousset, Johan Dao Duy, Wassim Amrani\n");
    list = ExampleList();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

    while (1) {
        printf("1 - Rechercher un contact\n2 - Créer un contact\n3 - Charger un fichier\n4 - Enregistrer le fichier\n5 - Quitter\n");
        int choice = ReadIntBetween(0, 6);

        switch (choice) {
            case 1:
                SearchContact();
                break;
            case 2:
                CreateContact();
                break;
            default:
                exit(0);
        }
    }
#pragma clang diagnostic pop
}
