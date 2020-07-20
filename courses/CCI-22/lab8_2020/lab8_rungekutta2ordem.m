format long
dydt=@(t,y) t-y;
t0=0;
y0=2;
h=[0.4; 0.1; 0.01];
tn=0.4;
yn_exact=1.41096;

n=size(h,1);
fprintf('Método de Runge-Kutta 2 ordem\n');
for i= 1:n % testa para todo valor de h
    [yn]=RK2aordem(dydt,t0,y0,h(i),tn); % calcula o valor
    fprintf('Com h = %.2f\nO valor de y(%.2f) é %.5f.\n',h(i),tn,yn); 
    fprintf('O erro absoluto é %.8f.\n\n',abs(yn-yn_exact)); 
end

function [yn] = RK2aordem(dydt,t0,y0,h,tn)
    y(1)=y0;
    t(1)=t0;
    t = (t0:h:tn); n = length(t);
    for i = 1:n-1 % implementa o método de Runge-Kutta 2 ordem
        k1=dydt(t(i),y(i));
        k2=dydt(t(i+1),y(i)+k1*h);
        y(i+1) = y(i) + h*(k1+k2)/2;
    end
    yn=y(i+1);
end

