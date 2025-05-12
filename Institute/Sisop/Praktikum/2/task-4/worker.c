#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

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

    key_t key = ftok("msgfile", 101);
    int worker_id = atoi(argv[1]), msgid = msgget(key, 0666 | IPC_CREAT), msg_count = 0;
    struct msgbuf msg;
    if (msgid == -1) exit(1);//ini handle takut gagal get id

    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), worker_id, 0) == -1) exit(1);
        if (strcmp(msg.mtext, "DONE") == 0) {
            char log_entry[256];
            sprintf(log_entry, "Worker %d: %d messages", worker_id, msg_count);
            log2file(log_entry);
            break;
        }

        char log_entry[256];
        sprintf(log_entry, "Worker%d: message received", worker_id);
        log2file(log_entry);
        msg_count++;
    }

    return 0;
}