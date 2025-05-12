#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>

struct shm_data {
    char message[256];
    int count;
};

struct msgbuf {
    long mtype;
    char mtext[256];
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
    
    key_t shm_key = ftok("shmfile", 100);
    key_t msg_key = ftok("msgfile", 101);
    int jumlah_workers = atoi(argv[1]), shmid = shmget(shm_key, sizeof(struct shm_data), 0666), msgid = msgget(msg_key, 0666 | IPC_CREAT);
    struct shm_data *data = (struct shm_data *)shmat(shmid, NULL, 0);
    struct msgbuf done_banh;

    for (int i = 0; i < data->count; i++) {
        char log_entry[256];
        sprintf(log_entry, "Received at lb: %s (#message %d)", data->message, i+1);
        log2file(log_entry);
        struct msgbuf msg;
        msg.mtype = ((i+1) % jumlah_workers) + 1; // Round-robin gini
        strcpy(msg.mtext, data->message);
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
    }

    for (int i = 0; i < jumlah_workers; i++) {
        done_banh.mtype = i+1;
        strcpy(done_banh.mtext, "DONE");
        msgsnd(msgid, &done_banh, sizeof(done_banh.mtext), 0);
    }

    shmdt(data);
    return 0;
}