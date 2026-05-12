#!/usr/bin/env bash

clear

frames=(
" "
"  H"
" He"
" Hel"
" Hell"
" Hello"
" Hello, "
" Hello, minishell"
" Hello, minishell!"
)

for frame in "${frames[@]}"; do
  printf "\r%-40s" "$frame"
  sleep 0.10
done

printf "\n"
sleep 0.5

cat <<'EOF'
pwd
echo "Hello from minishell"
export DEMO="LinkedIn"
echo $DEMO
echo "pipe test" | wc -c
echo "first line" > demo.txt
cat demo.txt
echo "second line" >> demo.txt
cat demo.txt
export
unset DEMO
echo $DEMO
echo $?
cat << EOF
This is heredoc
EOF
exit
EOF