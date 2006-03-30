#!/usr/bin/env python
# This file is part of the xxdiff package.  See xxdiff for license and details.

"""xxdiff-diff-proxy [<options>] <file> <file> [<file>]

Simple wrapper script for xxdiff that presents options that are the same as the
diff or diff3 commands.  This can be used with programs that expect to call
diff/diff3 to present differences to users, and that can be configured with a
different diff program.

This was originally created for integration with Subversion.  This is meant to
be used in a user's configuration file to set diff-cmd and diff3-cmd options, so
that when you run ``svn diff`` it spawns xxdiffs instead of textual diffs (see
also xxdiff-svn-diff).

Add the following lines ``~/.subversion/config``::

  diff-cmd = xxdiff-diff-proxy
  diff3-cmd = xxdiff-diff-proxy

"""

__author__ = "Martin Blais <blais@furius.ca>"
__depends__ = ['xxdiff', 'Python-2.3']


# stdlib imports.
import sys, os
import commands
from tempfile import NamedTemporaryFile

# xxdiff imports.
from xxdiff.scripts import tmpprefix


#-------------------------------------------------------------------------------
#
def parse_options():
    """
    Parse the options.
    """
    import optparse
    parser = optparse.OptionParser(__doc__.strip())

    # For diff-cmd invocation.
    parser.add_option('-u', action='store_true',
                      help="See diff(1). Ignored for xxdiff.")

    parser.add_option('-L', '--label', action='append', default=[],
                      help="See diff(1). Label gets set as file title string "
                      "for xxdiff.")

    # For diff3-cmd invocation.
    parser.add_option('-E', '--show-overlap', action='store_true',
                      help="See diff3(1). Ignored for xxdiff.")

    parser.add_option('-m', '--merge', action='store_true',
                      help="See diff3(1). Passed to xxdiff for automatic "
                      "selection of non-conflictual regions..")

    ## parser.add_option('--reverse', action='store_true',
    ##                   help="Reverse the display order of the files.")
    opts, args = parser.parse_args()

    if len(args) > 3:
        raise parser.error("Cannot invoke wrapper with more than 3 files.")

    return opts, args


#-------------------------------------------------------------------------------
#
def diffproxy_main():
    """
    Main program for cond-replace script.
    """
    opts, args = parse_options()

    # create temporary file to hold merged results.
    tmpf = NamedTemporaryFile('rw', prefix=tmpprefix)

    # run command
    xxdiff_path = 'xxdiff'

    decision = len(args) == 3
    cmd = [xxdiff_path]
    if decision:
        cmd.append('--decision')
    if opts.merge:
        cmd.append('--merge')
    cmd.append('--merged-filename="%s"' % tmpf.name)
    for o1, o2, fn in zip(['--title1', '--title2', '--title3'],
                          ['"%s"' % x for x in opts.label],
                          args):
        if os.path.basename(fn) == 'empty-file':
            o2 = '"(NON-EXISTANT FILE)"'
        cmd.extend([o1, o2])
    cmd.extend(args)
    ##print ' '.join(cmd)

    s, o = commands.getstatusoutput(' '.join(cmd))

    if decision:
        # if the user merged, copy the merged file over the original.

## FIXME: should reject also copy the file?  I think not, no?  Is this a bug?
## Review this.

        if o in ['MERGED', 'ACCEPT', 'REJECT']:
            tmpf.flush()
            tmpf.seek(0)
            text = tmpf.read()
            tmpf.close()
            sys.stdout.write(text)
    
        elif o == 'NODECISION':
            pass # do nothing
        else:
            raise SystemExit(
                    "Error: unexpected answer from xxdiff: %s" % o)


#-------------------------------------------------------------------------------
#
main = diffproxy_main

if __name__ == '__main__':
    main()

