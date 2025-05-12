
SCRIPT_DIR=$(dirname "$(realpath "$0")")
LOG_FILE="$SCRIPT_DIR/cloud_storage/cloud_log.txt"
DOWNLOAD_SCRIPT="download.sh"
LOGIN_CEK=$(tail -n 1 "$LOG_FILE")

if echo "$LOGIN_CEK"| grep -q "LOGIN: INFO"; then
    echo "$(date '+%Y/%m/%d %H:%M:%S') DOWNLOAD: INFO automate user login" >> "$LOG_FILE"
    bash "$DOWNLOAD_SCRIPT"
else
    echo "$(date '+%Y/%m/%d %H:%M:%S') DOWNLOAD: ERROR User not logged in" >> "$LOG_FILE"
fi