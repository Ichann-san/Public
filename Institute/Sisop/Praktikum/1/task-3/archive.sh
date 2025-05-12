
SCRIPT_DIR=$(dirname "$(realpath "$0")")
LOG_FILE="$SCRIPT_DIR/cloud_storage/cloud_log.txt"
DOWNLOAD_DIR="$SCRIPT_DIR/cloud_storage/download"
ARCHIVE_DIR="$SCRIPT_DIR/cloud_storage/archives"

if [[ ! -d "$DOWNLOAD_DIR" ]]; then
    echo "$(date '+%Y/%m/%d %H:%M:%S') ARCHIVE: ERROR No downloads directory found" >> "$LOG_FILE"
    exit 1
fi

for USER_DIR in "$DOWNLOAD_DIR"/*; do
    USERNAME=$(basename "$USER_DIR")
    USER_ARCHIVE_DIR="$ARCHIVE_DIR/$USERNAME"
    mkdir -p "$USER_ARCHIVE_DIR"
    if [[ -z "$(ls -A "$USER_DIR")" ]]; then
        echo "$(date '+%Y/%m/%d %H:%M:%S') ARCHIVE: INFO No images to archive for user $USERNAME" >> "$LOG_FILE"
        continue
    fi
    TIMESTAMP=$(date '+%H-%d-%m-%Y')
    ARCHIVE_FILE="$USER_ARCHIVE_DIR/archive_$TIMESTAMP.zip"
    zip -j "$ARCHIVE_FILE" "$USER_DIR"/*

    echo "$(date '+%Y/%m/%d %H:%M:%S') ARCHIVE: INFO Archived image $USERNAME to $ARCHIVE_FILE" >> "$LOG_FILE"
    rm -f "$USER_DIR"/*
done