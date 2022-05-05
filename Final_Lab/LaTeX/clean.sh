#!/bin/bash

# A small script to clean up the mess left by TexShop when building PDFs
rm -Rf $(find * | grep .synctex)
rm -Rf $(find * | grep .aux)
rm -Rf $(find * | grep .log)

# Get rid of python junk
rm -Rf $(find * | grep .pyc)

# Get rid of Mac junk
rm -Rf $(find * | grep .DS_Store)


