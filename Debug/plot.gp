#! /usr/local/bin/gnuplot

set term pdf color round font 'Source Sans Pro Bold'

name = "degrees"
filename = name.'.txt'
tablename = name.'.table'

binwidth =100
set grid

bin(x,width)=width*floor(x/width)

#set xrange [1:100]


set table tablename
plot filename using (bin($2,binwidth)):(2) smooth freq  with boxes
unset table

#set logscale xy;
load 'Paired.plt'
set style fill transparent solid 0.1
set samples 10000


lambda = 100000.0 
alpha = 10.0

sigma = sqrt(pi*lambda/2.0)/alpha
mu = 2.0*pi*lambda/alpha/alpha
N = 100000.0





f(x) = a*x+b
g(x) = 10**b*(x**a)

h(x) = sqrt(2*pi)/x
#fit  [0:1.1] f(x) tablename using (log10($1)):(log10($2)) via a,b


set output name.'.pdf'

#plot   tablename using 1:($2):(binwidth)  with boxes ls 5  title 'Degree distribution'
plot  []  tablename using ($1-100):($2):(binwidth)  with points ls 2 pt 2 lc rgb "#44306080" ps 0.5 lw 3  title 'Degree distribution';

#    g(x) with lines lt 1 lc rgb "#33ff4500"  lw 6  title 'Fit: '.sprintf("a = %1.2f; b = %1.2f",a,b);
    

