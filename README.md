## How to Run the Project

### Step 1: Compile the C Program
Ensure `main.c` and `profiler.h` are in the same folder. Open your terminal or command prompt and run:
`gcc main.c -o profiler_test`

### Step 2: Run the Executable
Execute the compiled program to generate the profile data.
* **Windows:** `.\profiler_test.exe`

*Result:* A file named `path_profile.txt` will be created in the folder.

### Step 3: Generate the Event Log
Run the Python script to visualize the output.
`python analyzer.py`
