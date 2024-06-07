#!/usr/bin/env python3

import argparse
import json
import sys
import re

p = argparse.ArgumentParser()
p.add_argument( "launch_name" )
args = p.parse_args()

TYPE_TO_ADAPTER = {
  'cppdbg': 'vscode-cpptools'
}

configurations = {}
with open( args.launch_name ) as launch_file:
  vsconfigurations = json.loads( re.sub( r"(\/\*([\s\S]*?)\*\/)|(\/\/(.*)$)", "", launch_file.read(), flags=re.MULTILINE ) ).get( "configurations", [] )
  if not vsconfigurations:
    exit( f"No launch.json configurations found in {args.launch_name}" )

  for vsconfig in vsconfigurations:
    name = vsconfig.pop( "name" )
    configurations[ name ] = {
      "adapter": TYPE_TO_ADAPTER[ vsconfig.pop( "type" ) ],
      "configuration": vsconfig,
    }

vimspector = {
  "$schema": "https://puremourning.github.io/vimspector/schema/vimspector.schema.json",
  "configurations": configurations
}

json.dump( vimspector, sys.stdout, indent=2 )
