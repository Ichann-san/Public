
USER_FILE="cloud_storage/users.txt"
LOG_FILE="cloud_storage/cloud_log.txt"


printf "Enter username: "
read USERNAME


if grep -q "^$USERNAME:" "$USER_FILE"; then
  echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: ERROR" >> "$LOG_FILE"
  echo "User already exists."
  exit 1
fi

printf "Enter password: "
read -s PASSWORD

if [[ ${#PASSWORD} -lt 8 ]]; then
  echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: ERROR" >> "$LOG_FILE"
  echo "Password must be at least 8 characters long."
  exit 1
fi

if [[ ! "$PASSWORD" =~ [A-Z] ]]; then
  echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: ERROR" >> "$LOG_FILE"
  echo "Password must contain at least one uppercase letter."
  exit 1
fi

if [[ ! "$PASSWORD" =~ [0-9] ]]; then
  echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: ERROR" >> "$LOG_FILE"
  echo "Password must contain at least one number."
  exit 1
fi

if [[ ! "$PASSWORD" =~ [^a-zA-Z0-9] ]]; then
  echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: ERROR" >> "$LOG_FILE"
  echo "Password must contain at least one special character."
  exit 1
fi

if [[ "$PASSWORD" == "$USERNAME" ]]; then
  echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: ERROR" >> "$LOG_FILE"
  echo "Password must not be the same as the username."
  exit 1
fi

if [[ "$PASSWORD" =~ (cloud|storage) ]]; then
  echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: ERROR" >> "$LOG_FILE"
  echo "Password must not contain the words 'cloud' or 'storage'."
  exit 1
fi

echo "$USERNAME:$PASSWORD" >> "$USER_FILE"
echo "$(date '+%Y/%m/%d %H:%M:%S') REGISTER: INFO" >> "$LOG_FILE"
echo "User registered successfully."
exit 0