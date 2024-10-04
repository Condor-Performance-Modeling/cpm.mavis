# Mavis

Mavis is a framework that allows decoding of the RISC-V ISA into
custom instruction class types as well as custom extensions to those
class types.

## Run regression

Mavis is a header-only library. Regression needs to build a tester.

* Build library for tester, output will be `libmavis.a`
```
cmake .
make -j8
```
* Build tester, output will be `Mavis`
```
cd test
mkdir build
cd build
cmake ..
```
* Execute the tester and compare golden `out`
```
./Mavis > test.out
diff -s test.out ../golden.out
```

## Notes on adding additional instructions

These files were changed to add AndeStar addigp 

```
impl/forms/ExtractorForms.h          include the astar forms header
impl/forms/AndeStarForms.h           form interface classes
impl/forms/AndeStarForms.cpp         initialize the form const containers
impl/forms/AndeStarExtractorForms.h  the dark arts begin here
impl/FormRegistry.cpp                add the Ande* headers and name to map
json/isa_andestar.json               instr definitions

```
