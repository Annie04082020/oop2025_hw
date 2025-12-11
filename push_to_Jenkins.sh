SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

HOMEWORK_DIR="$(dirname "$SCRIPT_DIR")/oop2025f_111310452_hw/"

echo "HOMEWORK_DIR: $HOMEWORK_DIR"
cd "$HOMEWORK_DIR" 
./push.sh