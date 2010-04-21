About hello-memoryview
======================

This is an example usage of the new-style buffer API
available in Python 2.6.


Requirements
============

Python 2.6+ and the numpy package.


Usage
=====

To run the demo using the slow python code::

    $ hello-memoryview

To run the demo using the faster C extension::

    $ hello-memoryview --fast

To advance the state by one step press 'n'.
To advance the state by multiple steps press '<k>n'
where <k> is some number, possibly with multiple digits.
For example, typing '99n' will advance the state by 99 steps.
To quit, press any key that is not 'n' and is not a digit.
