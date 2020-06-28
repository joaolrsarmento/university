format long
n = 5;
a = 0; b = 1;
f=@(x) 2 +5*x -3*x.^2 +6*x.^3 -7*x.^4 -3*x.^5 +x.^6;
h=(b-a)/n;
Ia1=Simpson13_mod(f,a,2*h,h);
Ia2=Simpson38_mod(f,2*h,b,h);
I=integral(f,a,b);
Ia=Ia1+Ia2;
Et=I-Ia;
fprintf("Regra de 1/3 de Simpson para 2 segmentos com \na regra de 3/8 de Simpson para 3 segmentos\n");
fprintf('Ia = %.8f\n',Ia);
fprintf('Et = %.8f\n',Et);
function Ia=Simpson13_mod(f,a,b,h)
    x=[a:h:b];
    y=f(x);
    Ia=(b-a)*(y(1)+4*y(2)+y(3))/6;
end
function Ia=Simpson38_mod(f,a,b,h)
    x=[a:h:b];
    y=f(x);
    Ia=(b-a)*(y(1)+3*(y(2)+y(3))+y(4))/8;
end

