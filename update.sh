# copy to homwork directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
# echo $SCRIPT_DIR
DATA_DIR="$SCRIPT_DIR/assignment8"
echo $DATA_DIR
TARGET_DIR="$SCRIPT_DIR/../oop2025f_111310452_hw"
echo $TARGET_DIR

cp -r CMakeLists.txt README.md src tests "$TARGET_DIR"

# push (homwerk copy)

git add .
git add -A
read -p "Enter commit: " answer
git commit -m "$answer"
git push all
git pull

# saving login info locally
# git config --global credential.helper store
# git config --global --unset credential.helper

# push (Jenkins, handin)
HOMEWORK_DIR="$(dirname "$SCRIPT_DIR")/oop2025f_111310452_hw/"
echo "HOMEWORK_DIR: $HOMEWORK_DIR"
cd "$HOMEWORK_DIR" 
git add .
git add -A
git commit -m "$answer"
git push 

git pull