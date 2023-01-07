# CSV Combiner

`./combine` is a command line program that takes several CSV files as arguments.
 The comand outputs a new CSV file to `stdout` that contains the
rows from each of the inputs along with an additional column that has the
filename from which the row came.


##  Testing 
* The three given files are int the `fixtures` directory
* Additionaly `fixtures` directory has files "test_one.csv" and "test_two.csv"
that test the case when files have different columns
* The code was writen in C++, to complile the main script use comand `g++ main.cpp -o combine`

## Examples
This comand is able to handle more than two inputs, inputs with different columns, and very large (> 2GB) 
files.

* Example 1
```
$ ./combine ./fixtures/accessories.csv ./fixtures/clothing.csv > combined.csv
```

Given two input files named `clothing.csv` and `accessories.csv`.

|email_hash|category|
|----------|--------|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Shirts|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Pants|
|166ca9b3a59edaf774d107533fba2c70ed309516376ce2693e92c777dd971c4b|Cardigans|

|email_hash|category|
|----------|--------|
|176146e4ae48e70df2e628b45dccfd53405c73f951c003fb8c9c09b3207e7aab|Wallets|
|63d42170fa2d706101ab713de2313ad3f9a05aa0b1c875a56545cfd69f7101fe|Purses|

The output is:

|email_hash|category|filename|
|----------|--------|--------|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Shirts|clothing.csv|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Pants|clothing.csv|
|166ca9b3a59edaf774d107533fba2c70ed309516376ce2693e92c777dd971c4b|Cardigans|clothing.csv|
|176146e4ae48e70df2e628b45dccfd53405c73f951c003fb8c9c09b3207e7aab|Wallets|accessories.csv|
|63d42170fa2d706101ab713de2313ad3f9a05aa0b1c875a56545cfd69f7101fe|Purses|accessories.csv|

* Example 2
```
$ ./combine ./fixtures/test_one.csv ./fixtures/test_two.csv > combined.csv
```

Given two input files named `test_one.csv` and `Test_two.csv`.

|email_hash|category|
|----------|--------|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Shirts|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Pants|
|166ca9b3a59edaf774d107533fba2c70ed309516376ce2693e92c777dd971c4b|Cardigans|

|email_hash|price|
|----------|-----|
|176146e4ae48e70df2e628b45dccfd53405c73f951c003fb8c9c09b3207e7aab|25|
|63d42170fa2d706101ab713de2313ad3f9a05aa0b1c875a56545cfd69f7101fe|24|

The output is:


|email_hash|category|price|filename|
|----------|--------|-----|--------|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Shirts| |test_one.csv|
|21d56b6a011f91f4163fcb13d416aa4e1a2c7d82115b3fd3d831241fd63|Pants| |test_one.csv|
|166ca9b3a59edaf774d107533fba2c70ed309516376ce2693e92c777dd971c4b|Cardigans| |test_one.csv|
|176146e4ae48e70df2e628b45dccfd53405c73f951c003fb8c9c09b3207e7aab| |25|test_two.csv|
|63d42170fa2d706101ab713de2313ad3f9a05aa0b1c875a56545cfd69f7101fe| |24|test_two.csv|

* Edge cases:

    * When provided with no files, the output is `No arguments were provided`
    * When one of the paths is invalid, throws an exeption and outputs `Error. Could not open file {filename}`


## Areas for improvement

    A posibile way to optimize this program is through the usage of multithreading. Since the program writes takes in multiple files its input, each file could be processed using its own thread. 