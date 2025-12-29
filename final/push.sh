git add .
read -p "Enter commit: " answer
git commit -m "$answer"
git push 
# git config --global credential.helper store
# git config --global --unset credential.helper