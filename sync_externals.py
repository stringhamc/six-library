#!/usr/bin/env python

import pdb
import subprocess
import os
from os.path import join, split, exists

# Get all the git remotes
def getRemotes():
    return filter(None, subprocess.check_output('git remote'.split()).split('\n'))

# Add a git remote
def addRemote(name, location):
    cmd = 'git remote add -f ' + name + ' ' + location
    subprocess.check_call(cmd.split())

# Send remotes in as key/value pairs in dictionary
def addRemotesIfNeeded(remotes):
    existingRemotes = getRemotes()
    for name, location in remotes.iteritems():
        if not name in existingRemotes:
            addRemote(name, location)

def addSubtree(remoteName, prefix, branch = 'master'):
    cmd = 'git subtree add --prefix ' + prefix + ' ' + remoteName + ' ' + \
        branch + ' --squash'
    subprocess.check_call(cmd.split())

def gitMove(srcPathname, destPathname):
    destDir = split(destPathname)[0]
    if not exists(destDir):
        os.makedirs(destDir)

    cmd = 'git mv ' + srcPathname + ' ' + destPathname
    subprocess.check_call(cmd.split())

# SIX-specific
def addSIXRemotes():
    addRemotesIfNeeded({'coda-oss_remote' : 'https://github.com/mdaus/coda-oss.git',
                        'nitro_remote': 'https://github.com/mdaus/nitro.git'})

def addSIXRepos():
    addSubtree('coda-oss_remote', join('temp_externals', 'coda-oss'))
    addSubtree('nitro_remote', join('temp_externals', 'nitro'))

def moveSIXDirs():
    # CODA-OSS
    cppModules = 'cli except include io logging math math.linear math.poly ' \
                 'mem mt numpyutils sio.lite str sys tiff types xml.lite wscript'
    cppModules = [join('modules', 'c++', dir) for dir in cppModules.split()]

    drivers = 'numpy xml wscript'
    drivers = [join('modules', 'drivers', dir) for dir in drivers.split()]

    codaOssDirs = ['build', \
                   join('modules', 'wscript'), \
                   join('modules', 'python')] + \
                   cppModules + \
                   drivers
    codaOssDirs = [join('temp_externals', 'coda-oss', dir) for dir in codaOssDirs]

    # NITRO
    cModules = 'nitf nrt wscript'
    cModules = [join('c', dir) for dir in cModules.split()]

    nitroDirs = ['c++', 'wscript'] + cModules
    nitroDirs = [join('temp_externals', 'nitro', 'modules', dir) for dir in nitroDirs]
    
    dirs = [codaOssDirs, nitroDirs]
    
    # TODO: 1. Do 'git mv' to move these into place
    #       2. Move some of this into a common file in coda-oss
    #       3. There needs to be some repeated code in here for first adding these repos?

    #gitMove(join('temp_externals', 'coda-oss', 'build'),
    #        join('final_externals', 'coda-oss', 'build'))
    
    #gitMove(join('temp_externals', 'coda-oss', 'modules'),
    #        join('final_externals', 'coda-oss', 'modules'))

if __name__ == '__main__':
    #addSIXRemotes()
    #addSIXRepos()
    moveSIXDirs()