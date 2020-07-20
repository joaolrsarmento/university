format long
dydt=@(t,y) t-y;
t0=0;
y0=2;
h=[0.4; 0.1; 0.01];
tn=0.4;
yn_exact=1.41096;

n=size(h,1);
fprintf('Método de Runge-Kutta 4 ordem\n');
for i= 1:n % testa para todo valor de h
    [yn]=RK4aordem(dydt,t0,y0,h(i),tn); % calcula o valor
    fprintf('Com h = %.2f\nO valor de y(%.2f) é %.5f.\n',h(i),tn,yn); 
    fprintf('O erro absoluto é %.8f.\n\n',abs(yn-yn_exact)); 
end

function [yn] = RK4aordem(dydt,t0,y0,h,tn)
    y(1)=y0;
    t(1)=t0;
    t = (t0:h:tn); n = length(t);
    for i = 1:n-1 %implementa o método de Runge-Kutta 4a ordem
        k1=dydt(t(i),y(i));
        k2=dydt(t(i)+0.5*h,y(i)+0.5*k1*h);
        k3=dydt(t(i)+0.5*h,y(i)+0.5*k2*h);
        k4=dydt(t(i)+h,y(i)+k3*h);
        y(i+1) = y(i) + (1/6)*(k1+2*k2+2*k3+k4)*h;
    end
    yn=y(i+1);
end

