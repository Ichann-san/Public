#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct shm_data {
    char message[256];
    int count;
};

void log2file(const char *entry) {
    FILE *f = fopen("sistem.log", "a");
    if (f) {
        fprintf(f, "%s\n", entry);
        fclose(f);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) exit(1);


    char *token = strtok(argv[1], ";"); char msg[256], log_entry[256];
    strcpy(msg, token);
    key_t key = ftok("shmfile", 100);
    int shmid = shmget(key, sizeof(struct shm_data), 0666 | IPC_CREAT);
    struct shm_data *data = (struct shm_data *)shmat(shmid, NULL, 0);
    token = strtok(NULL, ";");
    int count = atoi(token);

    sprintf(log_entry, "Message from client: %s", msg);
    log2file(log_entry);
    sprintf(log_entry, "Message count: %d", count);
    log2file(log_entry);
    strcpy(data->message, msg);
    data->count = count;
    shmdt(data);
    return 0;
}