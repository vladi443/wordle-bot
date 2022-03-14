# dictionary

C++ algorithm that scores and attempts to guess the daily word for the popular web game _Wordle_.

## Installation

Windows

1. Download and install a C++ compiler.
2. Download the Dictionary source code and save it as a ```.cpp``` file.
3. Download the two text files called ```words_definitions.txt``` and ```words_dictionary.txt``` and save them at the same location as Dictionary's source code. These two files are used by Dictionary as words databases and are needed for it to work.
4. Navigate to the folder containing the source code of Dictionary and open the ```.cpp``` file with your preferred text editor.
5. Inside the text editor, change ```line 30``` and ```line 31``` to the local location of your ```.txt``` files. Once done save and exit the text editor.
6. Note: If you fail to do step 5 correctly, Dictionary will exit on startup with error message indicating it was not able to load the text files. If this occurs, try to write in the full path to the text files.
7. Open CMD and navigate to the folder containing the source code of Dictionary.
8. Once in the targeted folder, compile the program by typing ```gcc main.cpp -o <preferred-name>.exe``` in the console. (preferred-name ca be anyting, ex. dictionary.exe, main.cpp will be whatever you named the .cpp file upon download).

Linux / MacOS

1. Download the Dictionary source code and save it as a ```.cpp``` file.
2. Download the two text files called ```words_definitions.txt``` and ```words_dictionary.txt``` and save them at the same location as Dictionary's source code. These two files are used by Dictionary as words databases and are needed for it to work.
3. Navigate to the folder of the Source Code of Dictionary (Either via terminal or GUI).
4. Once in the targeted folder, open terminal and open the ```.cpp``` file using a preferred text editor. (ex. nano, vi)
5. From the text editor, change ```line 30``` and ```line 31``` to the local location of your ```.txt``` files. Once done save and exit the text editor.
6. Note: If you fail to do step 5 correctly, Dictionary will exit on startup with error message indicating it was not able to load the text files. If this occurs, try to write in the full path to the text files.
7. Once in the targeted folder, open terminal and compile the program by typing ```g++ -o <preferred-name> main.cpp```. (preferred-name can be anything, ex. primes, main.cpp will be whatever you named the .cpp file upon download).

## Usage

Windows

1. Navigate to the folder where the compiled Primes file is located.
2. Once in the targeted folder, open CMD and type ```<preferred-name>.exe``` or double click the ```<preferred-name>.exe``` file from file explorer.
3. Primes will start either in the CMD window where the command was typed, or will open a new CMD window if opened through file explorer.
4. Follow the instructions displayed upon starting Primes to use it successfully.

Linux / MacOS

1. Navigate to the folder where the compiled Primes file is located.
2. Once in the targeted folder, open terminal and type ```./<preferred-name>```.
3. Primes should start in the same terminal window where the previous command was entered.
4. Follow the instructions displayed upon starting Primes to use it sucessfully.

## Troubleshooting

If you encounter any problems during compiling or using Primes, please open an issue and describe the problem found. Sample data or screenshots will be extremely helpful troubleshooting the problem.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change or add to Primes.

Please make sure to update tests as appropriate and document the changes made.

## Acknowledgements

Special thanks to [MakeaREADME](https://www.makeareadme.com) which template and information I used when developing this README.

Primes was inspired by [Primel](https://converged.yt/primel/) Web Game, which you can play by clicking on its name.

## License
[GNU GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)
