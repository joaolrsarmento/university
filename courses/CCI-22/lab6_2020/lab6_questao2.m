format long
x=[1 2 3 4 5 6]; y=[1.487 2.958 5.602 8.003 11.452 13.021];
m=2; n=length(x);
% Calculo das somas
soma_x=sum(x);soma_y=sum(y); soma_x2=sum(x.^2);soma_x3=sum(x.^3);
soma_x4=sum(x.^4);soma_xy=sum(x.*y);
soma_x2y=sum((x.^2).*y);x_med=soma_x/n;y_med=soma_y/n;
% Ajustando as matrizes do sistema
Mc=[n soma_x soma_x2; soma_x soma_x2 soma_x3; soma_x2 soma_x3 soma_x4];
Mb=[soma_y; soma_xy; soma_x2y];
% Resolve o sistema
a=Mc\Mb;
y1=a(1,1)+a(2,1)*x+a(3,1)*x.^2;
% Calculo dos coeficientes
St=sum((y-y_med).^2);
Sr=sum((y-a(1,1)-a(2,1).*x-a(3,1).*x.^2).^2);
Sy_x=sqrt(Sr/(n-(m+1)));
Cd=(St-Sr)/St; r=sqrt(Cd);
% Printando os resultados
fprintf("a0 = %.8f\na1 = %.8f\na2 = %.8f\nCd = %.8f\nr = %.8f\n", a(1,1), a(2,1), a(3,1), Cd, r);
% Plotando os graficos
plot(x,y1); hold on
plot(x,y,'o'); hold off

