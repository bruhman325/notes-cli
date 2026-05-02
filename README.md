A cross platform note taking system
<h1>Usage</h1>

| Command | Arguments | Usage|Flags |
| -------- | -------- | -------- | -------- |
| notes | note_identifier | reads note with identifier from db | --all |
| notes read  | note_identifier | does same thing as above | --all |
|   |  |  |  |
| notes | note_identifier note_content | writes a note to the db |  |
| notes write | note_identifier note_content | does same thing as above |  |
|   |  |  |  |
| notes delete | note_identifier | deletes a note from the db |--all  |

<h1>Install</h1>

linux (works on windows too but idk the commands rn)
```
mkdir build
cd build
cmake -S ../
cmake --build .
sudo cmake --install .
```
