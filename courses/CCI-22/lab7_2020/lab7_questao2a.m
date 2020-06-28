format long
a = 0; b = 1;
f=@(x) 2 +5*x -3*x.^2 +6*x.^3 -7*x.^4 -3*x.^5 +x.^6;
I=integral(f,a,b);
Ia=Simpson13(f,a,b);
fprintf("Regra de 1/3 de Simpson para 1 segmento\n");
fprintf('Ia = %.8f\n',Ia);
fprintf('Et = %.8f\n',Et);
function Ia=Simpson13(f,a,b)
h=(b-a)/2;
x=[a:h:b];
y=f(x);
Ia=(b-a)*(y(1)+4*y(2)+y(3))/6;
end

