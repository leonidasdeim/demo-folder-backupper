# FolderBackupper

Utility for backing up new or modified files in the folder.  

Application built for Linux on WSL2.  
Requires `cmake` and `gcc` with C++20 support.

### How to build and run:
```
mkdir build
cd build/
cmake ../
cmake --build .  
  
./FolderBackupper hot_folder_path backup_folder_path
./FolderBackupper ../Test/Test-hot/ ../Test/Test-bak/
```
