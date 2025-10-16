set grid
set datafile separator ','
f(x) = a*x+b
fit f(x) ARG1 using 3:4 via a,b
plot ARG1 using 3:4 with points, f(x) with lines
