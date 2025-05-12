
SCRIPT_DIR=$(dirname "$(realpath "$0")")
LOG_FILE="$SCRIPT_DIR/cloud_storage/cloud_log.txt"
DOWNLOAD_DIR="$SCRIPT_DIR/cloud_storage/downloads"
USERNAME=$(grep "LOGIN: INFO" "$LOG_FILE" | tail -n 1 | cut -d ' ' -f 6)
USER_DOWNLOAD_DIR="$DOWNLOAD_DIR/$USERNAME"

if [[ -z "$USERNAME" ]]; then
    echo "$(date '+%Y/%m/%d %H:%M:%S') DOWNLOAD: ERROR User not logged in" >> "$LOG_FILE"
    exit 1
fi

mkdir -p "$USER_DOWNLOAD_DIR"
# ini udah dikasih seed nature, tapi ternyata ga random, jadi seed nya dihapus aja
# kalo mau nanti tinggal dikasih seed aja, atau pake api lain
wget -q "https://picsum.photos/1920/1080?random=$RANDOM" -O "$USER_DOWNLOAD_DIR/image_$i.jpg"

TIMESTAMP=$(date '+%Y-%m-%d %H-%M_%d-%m-%Y')
ZIP_FILE="$USER_DOWNLOAD_DIR/$TIMESTAMP.zip"
zip -j "$ZIP_FILE" "$USER_DOWNLOAD_DIR"/*.jpg

echo "$(date '+%Y/%m/%d %H:%M:%S') DOWNLOAD: INFO Images done $USERNAME" >> "$LOG_FILE"