# Trabalho_Pratico_PDS2

This project was made for a college discipline about software development.

## Run and compile commands

### Build

Run `make` on the root folder to compile all the library and source files. 
In case lib folder isnt empty run `make clean`

### Run

To run the already compiled code run `make run`
To use the make file, put the output files in the data folder, you can change the file names on line 32 of the makefile or stick with the original file names 'users.csv' and 'events.csv'

### Check memory leaks

To run the code and check any possible memory leaks run `make mem`

## File Structure

The code is divided in two folders, lib and src. Lib contains header files with the declaration of all classes and src contains class functions. The code also has a data folder that contains the csv inputs. 
