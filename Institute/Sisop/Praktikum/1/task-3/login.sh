
USER_FILE="cloud_storage/users.txt"
LOG_FILE="cloud_storage/cloud_log.txt"

printf "Username :"
read USERNAME

printf "Password :"
read -s PASSWORD
printf "\n"

if grep -q "^$USERNAME:$PASSWORD$" "$USER_FILE"; then
    if grep -q "LOGIN: INFO" "$LOG_FILE" | grep -v "LOGOUT: INFO"; then
        echo "$(date '+%Y/%m/%d %H:%M:%S') LOGIN: ERROR User $USERNAME already logged in" >> "$LOG_FILE"
        echo "User already logged in."
        exit 1
    else
        echo "$(date '+%Y/%m/%d %H:%M:%S') LOGIN: INFO User $USERNAME logged in successfully" >> "$LOG_FILE"
        echo "User logged in successfully."
    fi
else
    echo "$(date '+%Y/%m/%d %H:%M:%S') LOGIN: ERROR" >> "$LOG_FILE"
    echo "Invalid username or password."
    exit 1
fi