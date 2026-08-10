/*
 * Question 2: Sensor Information System using Union
 *
 * Models an embedded sensor using struct + union.
 * Union stores EITHER an integer OR float reading (not both).
 * Demonstrates pass-by-value vs pass-by-pointer for union.
 *
 * Compile : gcc sensor_union.c -o sensor
 * Run     : ./sensor
 *
 * Concepts: Union, Struct, Function args, Pointer to union,
 *           Pass-by-value vs pass-by-reference, Memory sharing
 */

#include <stdio.h>
#include <string.h>

#define NAME_LEN 32

/* ── Reading type tag ────────────────────────────────────────── */
typedef enum { INT_READING = 1, FLOAT_READING = 2 } ReadingType;

/* ── Union: one memory, two types ───────────────────────────── */
typedef union {
    int   int_val;
    float float_val;
} SensorValue;

/* ── Sensor structure ────────────────────────────────────────── */
typedef struct {
    int         id;
    char        name[NAME_LEN];
    ReadingType type;         /* which union field is valid */
    SensorValue value;
} Sensor;

/* ── Function prototypes ─────────────────────────────────────── */
void readSensor   (Sensor *s);
void displaySensor(Sensor  s);          /* pass by value  */
void updateSensor (Sensor *s);          /* pass by pointer */
void compareSensor(Sensor  a, Sensor b);
void resetSensor  (Sensor *s);

/* ── readSensor(): fill sensor details from user ─────────────── */
void readSensor(Sensor *s)
{
    printf("Enter Sensor ID   : "); scanf("%d", &s->id);
    printf("Enter Sensor Name : "); scanf("%s", s->name);

    printf("Choose Reading Type\n  1. Integer\n  2. Float\nChoice : ");
    int choice; scanf("%d", &choice);

    if (choice == 2) {
        s->type = FLOAT_READING;
        printf("Enter float reading : "); scanf("%f", &s->value.float_val);
    } else {
        s->type = INT_READING;
        printf("Enter int reading   : "); scanf("%d", &s->value.int_val);
    }
}

/* ── displaySensor(): pass by VALUE (copy — changes don't affect original) */
void displaySensor(Sensor s)
{
    printf("\n--- Sensor Details ---\n");
    printf("ID      : %d\n", s.id);
    printf("Name    : %s\n", s.name);
    if (s.type == FLOAT_READING)
        printf("Reading : %.2f (float)\n", s.value.float_val);
    else
        printf("Reading : %d (int)\n", s.value.int_val);
}

/* ── updateSensor(): pass by POINTER (modifies original) ─────── */
void updateSensor(Sensor *s)
{
    printf("\nUpdating Reading...\n");
    if (s->type == FLOAT_READING) {
        printf("Enter new float value : "); scanf("%f", &s->value.float_val);
        printf("Updated Value : %.2f\n", s->value.float_val);
    } else {
        printf("Enter new int value   : "); scanf("%d", &s->value.int_val);
        printf("Updated Value : %d\n", s->value.int_val);
    }
}

/* ── compareSensor(): compare two sensors ─────────────────────── */
void compareSensor(Sensor a, Sensor b)
{
    printf("\n--- Sensor Comparison ---\n");
    printf("Sensor A: %s (ID=%d)\n", a.name, a.id);
    printf("Sensor B: %s (ID=%d)\n", b.name, b.id);

    /* Compare only if both have same reading type */
    if (a.type != b.type) {
        printf("Cannot compare: different reading types\n");
        return;
    }

    if (a.type == FLOAT_READING) {
        float diff = a.value.float_val - b.value.float_val;
        if (diff > 0)
            printf("%s reading is higher by %.2f\n", a.name, diff);
        else if (diff < 0)
            printf("%s reading is higher by %.2f\n", b.name, -diff);
        else
            printf("Both sensors have equal readings\n");
    } else {
        int diff = a.value.int_val - b.value.int_val;
        if (diff > 0)
            printf("%s reading is higher by %d\n", a.name, diff);
        else if (diff < 0)
            printf("%s reading is higher by %d\n", b.name, -diff);
        else
            printf("Both sensors have equal readings\n");
    }
}

/* ── resetSensor(): zero out everything ──────────────────────── */
void resetSensor(Sensor *s)
{
    s->id            = 0;
    s->type          = INT_READING;
    s->value.int_val = 0;
    memset(s->name, 0, NAME_LEN);
    printf("\nSensor reset to default.\n");
}

int main(void)
{
    Sensor s1, s2;

    printf("=== Sensor 1 ===\n");
    readSensor(&s1);
    displaySensor(s1);
    updateSensor(&s1);
    displaySensor(s1);

    printf("\n=== Sensor 2 ===\n");
    readSensor(&s2);
    displaySensor(s2);

    compareSensor(s1, s2);

    resetSensor(&s1);
    displaySensor(s1);

    printf("\nUnion size : %zu bytes\n", sizeof(SensorValue));
    printf("Struct size: %zu bytes\n", sizeof(Sensor));

    return 0;
}
