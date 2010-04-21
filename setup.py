"""
This is the setup script.
This script is automatically run by
easy_install or by pip on the user's machine when
she installs the module from pypi.

Here is some documentation for this process.
http://docs.python.org/extending/building.html

More info:
http://wiki.python.org/moin/Distutils/Tutorial

Register the metadata with pypi as follows:
python setup.py register

Send to pypi as follows:
python setup.py sdist upload --show-response
"""

from distutils.core import setup
from distutils.core import Extension
import os

life_version = '0.1.0'


scripts = [
        'bin/hello-memoryview']

life = Extension(
        name='life',
        sources=['lifemodule.c'])

classifiers = [
        'Development Status :: 4 - Beta',
        'Environment :: Console :: Curses',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Natural Language :: English',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.0',
        'Programming Language :: Python :: 3.1',
        'Programming Language :: C',
        'Topic :: Artistic Software']

download_url = '/'.join([
    'http://pypi.python.org/packages/source',
    'h/hello-memoryview',
    'hello-memoryview-' + life_version + '.tar.gz'])

long_description = open('README.rst').read()

setup(
        name = 'hello-memoryview',
        version = life_version,
        author = 'Alex Griffing',
        author_email = 'argriffi@ncsu.edu',
        maintainer = 'Alex Griffing',
        maintainer_email = 'argriffi@ncsu.edu',
        url = 'http://github.com/argriffing/hello-memoryview',
        download_url = download_url,
        description = 'an example usage of the new style buffer API',
        long_description = long_description,
        classifiers = classifiers,
        platforms = ['Linux'],
        license = 'MIT',
        ext_modules = [life],
        scripts = scripts)
