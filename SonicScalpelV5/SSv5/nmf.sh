#! /bin/bash
# NMF Script to factorise matrix V into W and H

mlpack_nmf -H h.csv -i v.csv -r 128 -W w.csv -u als

