#! /usr/local/bin/gnuplot

#set term pdf color round font 'Source Sans Pro Bold'
set term pdf color round font 'Source Sans Pro Bold' size 4,3
#set term pdf color round font 'Dosis' size 4,3

name = "degrees"
filename = name.'.txt'
tablename = name.'.table'

binwidth =100
#set grid

bin(x,width)=width*floor(x/width)

#set xrange [1:100]


set table tablename
plot filename using (bin($2,binwidth)):(2) smooth freq  with boxes
unset table

set logscale xy;
load 'Paired.plt'
set style fill transparent solid 0.1
set samples 10000


lambda = 100000.0 
alpha = 10.0

sigma = sqrt(pi*lambda/2.0)/alpha
mu = 2.0*pi*lambda/alpha/alpha
N = 100000.0

set xtics scale 2
set ytics scale 2
set mytics 10
set mxtics 10

set format y "10^{%T}"
set format x "10^{%T}"
set border lw 3 lc rgb "#555555"

set key spacing 1.5 box lw 3 lc rgb "#555555" opaque textcolor rgb "#555555"

f(x) = a*x+b
g(x) = 10**b*(x**a)

h(x) = sqrt(2*pi)/x
#fit  [0:1.1] f(x) tablename using (log10($1)):(log10($2)) via a,b


set output name.'.pdf'

s = 300*10000

#plot   tablename using 1:($2):(binwidth)  with boxes ls 5  title 'Degree distribution'
plot  []  tablename using ($1):($2):(binwidth)  with points ls 7 pt 7 ps 0.5 lc rgb "#88333333"   lw 0.5  title 'Agent-based model', tablename u ($1):(s*1/$1) with lines lw 5 lc rgb "#88ff4500" title 'Theory';

#    g(x) with lines lt 1 lc rgb "#33ff4500"  lw 6  title 'Fit: '.sprintf("a = %1.2f; b = %1.2f",a,b);
   
#  "#bb306080" 

