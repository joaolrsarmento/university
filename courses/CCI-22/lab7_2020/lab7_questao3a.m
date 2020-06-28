format long
a = 0; b = 1;
f=@(x) 2 +5*x -3*x.^2 +6*x.^3 -7*x.^4 -3*x.^5 +x.^6;
I=integral(f,a,b);
Ia=Simpson38(f,a,b);
Et=I-Ia;
fprintf("Regra de 3/8 de Simpson para 1 segmento\n");
fprintf('Ia = %.8f\n',Ia);
fprintf('Et = %.8f\n',Et);
function Ia=Simpson38(f,a,b)
    h=(b-a)/3;
    x=[a:h:b];
    y=f(x);
    Ia=(b-a)*(y(1)+3*(y(2)+y(3))+y(4))/8;
end

