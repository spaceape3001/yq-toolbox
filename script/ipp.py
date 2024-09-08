#!/usr/bin/python

import io,sys,os,os.path,subprocess

DIR = sys.argv[1]
IPP = []

def exclude(name):
    for ch in name:
        if ch == '.':
            break;
        if ch.islower():
            return False;
    return True

for f in os.listdir(DIR):
    if f.endswith('.ipp'):
        IPP.append(f)
        continue
    if not f.endswith('.cpp'):
        continue
    #if exclude(f):
    #    continue
    rt  = f.removesuffix('.cpp')
    if rt == DIR:
        continue
    ipp = rt + '.ipp'
    IPP.append(ipp)
    subprocess.run(["git", "mv", "%s/%s" % (DIR, f), "%s/%s" % (DIR, ipp)])
    print("%s -> %s" % (f, ipp))

IPP.sort()

with open("%s/%s.cpp" % (DIR, DIR), 'w') as f:
    f.write("""////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

// Auto-generated file

""")

    for i in IPP:
        f.write("""#include "%s"
""" % i)

