#!/usr/bin/python
# 
import  csv,sys, os, subprocess
from subprocess import check_output
from subprocess import call

def file_len(fname):
    i = 0
    with open(fname) as f:
        for i, l in enumerate(f):
            pass
    return i + 1


extensions = "--extensions=c,h" 
verbose = "--verbose=5"
filters="--filter=-runtime/threadsafe_fn,-runtime/printf,+whitespace,+readability,-readability/casting,-legal/copyright"
counting="--counting=detailed"
locCount = 0
fileName = raw_input("Which file should I check?")
outfile = open(fileName +".styleOuput.txt",'w')
locCount = locCount + file_len(fileName)
try:
  proc = subprocess.Popen(["python", "cpplint.py",extensions,filters,verbose, counting, fileName] ,stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  #result = result + check_output(["python", "cpplint.py",extensions,filters, counting,callDir ], stderr=subprocess.stdout)
  out,err = proc.communicate()
  print err
  outfile.write(err)
  outfile.write ("LOC: "+ str(locCount))

except subprocess.CalledProcessError as e:
  print "error state"
  print(e.returncode)
  outfile.close()
  