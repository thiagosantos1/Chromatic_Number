
#define BOY  0
#define GIRL 1

typedef struct lightswitch {
  int counter;
  sem_t mut;
} LIGHTSWITCH;

LIGHTSWITCH *init_lightswitch();
void lock(LIGHTSWITCH *ptr, sem_t *semptr);
void unlock(LIGHTSWITCH *ptr, sem_t *semptr);

