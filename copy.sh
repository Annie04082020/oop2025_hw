SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
# echo $SCRIPT_DIR
DATA_DIR="$SCRIPT_DIR/assignment7"
echo $DATA_DIR
TARGET_DIR="$SCRIPT_DIR/../oop2025f_111310452_hw"
echo $TARGET_DIR

cp -r CMakeLists.txt README.md src tests "$TARGET_DIR"

