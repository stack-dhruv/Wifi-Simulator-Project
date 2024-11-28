#!/bin/bash

# Colors for terminal output
GREEN="\033[1;32m"
CYAN="\033[1;36m"
RESET="\033[0m"
BOLD="\033[1m"

# Directories and files
DIRS=("bin" "docs" "include" "src")
FILES=("docs/OOPD____Project.pdf" "makefile" "readme.md")

# ASCII Art
ASCII_ART="
        +-----------------------------------+
        |      ___       __   __         ___|
        ||  | |__  |    /    /  \  |\/| |__ |
        ||/\| |___ |___ \__  \__/  |  | |___|
        +-----------------------------------+
+--------------------------------------------------+
|                   :Authored By:                  |
| __        __                                  __ |
||  \ |__| |__) |  | \  / |__/ |  |  |\/|  /\  |__)|
||__/ |  | |  \ \__/  \/  |  \ \__/  |  | /~~\ |  \|
|                                                  |
|                __       ___  ___                 |
|               |__)  /\   |  |__  |               |
|               |    /~~\  |  |___ |___            |
+--------------------------------------------------+
"

# Function to create directories and files
create_structure() {
  echo -e "${CYAN}Setting up project structure...${RESET}"

  for dir in "${DIRS[@]}"; do
    if [ ! -d "$dir" ]; then
      mkdir "$dir"
      echo -e "${GREEN}Created directory: $dir${RESET}"
    else
      echo -e "${CYAN}Directory already exists: $dir${RESET}"
    fi
  done

  for file in "${FILES[@]}"; do
    if [ ! -f "$file" ]; then
      touch "$file"
      echo -e "${GREEN}Created file: $file${RESET}"
    else
      echo -e "${CYAN}File already exists: $file${RESET}"
    fi
  done
}

# Execute the function
create_structure

# Display ASCII Art and final message
echo -e "\n${BOLD}${GREEN}${ASCII_ART}${RESET}"
echo -e "${BOLD}${GREEN}Setup Successful!${RESET}"
