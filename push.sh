git add .
git add -A
read -p "Enter commit: " answer
git commit -m "$answer"
git push all
git pull