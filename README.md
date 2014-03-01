DCC888-UFMG
===========

# Code Analysis and Optimization - DCC888 (UFMG)

[Course's Website](http://homepages.dcc.ufmg.br/~fernando/classes/dcc888/)

### Configuring LLVM + Clang environment

To start creating new passes in LLVM, you will have to set up your
environment. Here are some tips that will make your life easier:

Use the stable version of LLVM instead of the latest revision of
LLVM's SVN repository. The latest stable version is the version 3.4
and you can download it as a tar.gz file from llvm.org, or download it
using svn.
$> svn co http://llvm.org/svn/llvm-project/llvm/tags/RELEASE_34/final llvm
$> cd llvm/tools
$> svn co http://llvm.org/svn/llvm-project/cfe/tags/RELEASE_34/final clang

### Graphviz

sudo apt-get install gv
sudo apt-get install graphviz

In your terminal, go to the root of your LLVM and run:
./configure --disable-optimized
This will generate makefiles that enable debugging.

Now, if everything is alright, run:
make

after all add llvm/Debbug+Asserts/bin
and           llvm/Debbug+Asserts/lib

to PATH


