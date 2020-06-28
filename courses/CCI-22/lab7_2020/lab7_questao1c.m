format long
n = 10;
a = 0; b = 1;
f=@(x) 2 + 5*x - 3*x.^2 + 6*x.^3 -7*x.^4 -3*x.^5 +x.^6;
I=integral(f,a,b);
h=(b-a)/n;
x=[a:h:b];
y=f(x);
Ia=trapz(x,y);
Et=I-Ia;
fprintf("Regra do trapezio para 10 segmentos\n");
fprintf('Ia = %.8f\n',Ia);
fprintf('Et = %.8f\n',Et);

