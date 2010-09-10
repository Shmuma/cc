#!/bin/sh

prog='
BEGIN {
    rating = 0;
};


/show_authorstats/ {
    rating++;
};


/userid=2100/ {
    print rating;
    exit;
};
';

wget -O - -q 'http://icpcres.ecs.baylor.edu/onlinejudge/index.php?option=com_onlinejudge&Itemid=20&page=show_authorsrank&limit=1500&limitstart=0' | \
awk "$prog"