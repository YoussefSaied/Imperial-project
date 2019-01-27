%% Function
function h=hf(x)
r=480e3;
h1=9000;
h2=20;
g=9.81;
if (x < -1*r)
    h=-1*h1;
end
if x > r
    h=-1*h2;
end
if (x <= r) && (x >= -1*r)
   h=-1* .5 * (h1+h2 + (h2-h1)*sin(.5*pi*x/r)) ;
end
end