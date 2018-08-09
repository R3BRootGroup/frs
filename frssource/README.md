# Using ucesb as unpacker stage for R3BROOT
-----------------------------------------

The versatile unpacker generator [ucesb](http://fy.chalmers.se/~f96hajo/ucesb) can be used as unpacking stage for R3BROOT.
This allows the user to write the unpacker using a human-readable specification, rather than in C/C++ code.
Thorough checking of the data format comes for free as well.
For further information about ucesb, see the [write-up](http://fy.chalmers.se/~f96hajo/ucesb/ucesb_doc.pdf).

# Overview
--------

1. Install ucesb (with FAIRROOT version of ROOT)
2. Compile your experiment specific unpacker and test it on data
3. Produce the header file for R3BROOT including the data structure
4. Extract the parts for each detector and level (unpack / raw)
5. Install [R3BROOT](https://www.r3broot.gsi.de) and FRS package
6. Write detector specific readers
7. Write or modify your R3BROOT steering macro
8. Run the macro

# Produce the header file
-----------------------

Run ucesb with the struct_writer header generation option
~~~bash
    ./sNNN --ntuple=<signals>,id=h101_<detector>,ext_h101_<detector>.h
~~~
Example
~~~bash
    ./frs --ntuple=RAW,id=h101_FRS,ext_h101_frs.h
~~~
This will already insert the correct detector names for you, if you like and only extract signals related to the specific detector.


# Extract the parts for each detector
-----------------------------------

At this point this part of the process is still manual:
For this example we will use the RAW level data of FRS.

- Make a copy of ext\_h101.h for each detector (e.g. ext\_h101_frs.h)
- Rename the EXT_STR_h101.h to EXT_STR_h101_frs.h
- Delete all contents of the structure with don't relate to FRS
- Delete all contents of the #define EXT_STR_h101_ITEMS_INFO(...) that don't relate to FRS
- Rename the #define statement to match the structure name.


# Write detector specific reader classes
--------------------------------------

Have a look at r3bsource/R3BUnpackReader.[cxx/h].
Your detector specific reader class should almost be a copy of this, mostly replacing 'unpack' with e.g. 'califa'.
And you will have to make sure that in the Read() function your detector specific data containers are filled with the data from the ucesb structure.


# Questions
---------

[GSI forum](https://forum.gsi.de/index.php?t=thread&frm_id=206&%).
