# Prerequisites
- A C compiler (gcc is assumed).
- gvim (not required for _oldKAF_).
- Windows (Linux is doable, see chapter below).

# Installation
## Using gcc
Run *build.bat*.
## Using another C compiler
Substitute *gcc* in line *1* in *build.bat* for your compiler and run *build.bat*.

# Usage
Executing *build.bat* generates an __HMTL__ parser and two shortcuts: *KAF.lnk* and *oldKAF.lnk*. The latter
is the orignal static version of __KAF__. The former is the newer, dynamic version. I recommend using this
version.

## oldKAF
Executing __oldKAF__ simply opens __notepad__ displaying the information about the flights. To update the
information, close __notepad__ and run __oldKAF__ again. Closing __notepad__ is not required, but is adivised if
you don't want to end up with several windows dedicatated to __notepad__.

## KAF
Executing __KAF__ opens two windwos. One window contains information about the latest updates and the other
window contains the flight information, the *update* window and *flight* window, respectively. The information
in the *flight* window can only be refreshed after there has been an update in the *update* window. These updates
happen, roughly, every thirty seconds but can also be forced by pressing any button while on focused on the
*update* window. The *flight* window will often refresh autimatically but can be forced to refresh by pressing
*F5*. If pressing *F5* does not work, odds are there hasn't been an update on the *update* window.

# Linux
The process that is undergone when running __KAF__ is fairly linear and porting it to __Linux__ should not prove
to difficult. I may do this at some point, though I am making no promises.

# Important notice
The effectiveness of this project is dependent on the syntax of a single webpage. I have no say over the design
of said webpage. It is for those reason I cannot promise to support this project in the future. I will do my
best, though.


