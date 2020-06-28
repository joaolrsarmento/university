format long
n = 10;
a = 0; b = 1;
f=@(x) 2 +5*x -3*x.^2 +6*x.^3 -7*x.^4 -3*x.^5 +x.^6;
I=integral(f,a,b);
Ia=MultiSegSimpson13(f,a,b,n);
Et=I-Ia;
fprintf("Regra de 1/3 de Simpson para 10 segmentos\n");
fprintf('Ia = %.8f\n',Ia);
fprintf('Et = %.8f\n',Et);
function Ia=MultiSegSimpson13(f,a,b,n)
    h=(b-a)/n;
    x=[a:h:b];
    y=f(x);
    somaxpar=0;
    somaximpar=0;
    for i=2:2:n
        somaximpar=somaximpar+y(i);
    end
    for i=3:2:n-1
        somaxpar=somaxpar+y(i);
    end
    Ia=(b-a)*(y(1)+4*somaximpar+2*somaxpar+y(n+1))/(3*n);
end


