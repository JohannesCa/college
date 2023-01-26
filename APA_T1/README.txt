To compile the program do

    $ make all

it will handle all the needed steps.
You can also clean the built program and remove the generated files by doing

    $ make clean

Use: ./apa-t1 <method_name> <input_file_name>

Available sorting methods:
    - selection
    - insertion
    - merge
    - quick
    - heap
    - default (stl default)

Obs.: the input file MUST be in the Resources/ directory.

To run the input files all at once, you can run as well the script run_inputs.sh by doing

    $ ./run_scripts.sh

The generated logs, with information of loading and processing time, will be in the Logs/ directory.

The generated outputs will be in Outputs/ directory.

Using diferent methods on the same input file will NOT generate diferent output files. A method rewrites the output, so it will only be the result of the last sorting method used. So be wise.
