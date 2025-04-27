echo "[1;36mUse Ctrl+J to run a prettier command.[0m"

add_raiinbow() {
  BUFFER="$BUFFER | ~/.rainbow/rainbow"
  zle .accept-line
}
zle -N add_raiinbow
bindkey 'e' add_raiinbow