format long
x=[1 2 3 4 5 6]; y=[1.487 2.958 5.602 8.003 11.452 13.021]; 
w=log10(x); z=log10(y); % Linearizando
n=length(x); 
soma_w=sum(w); soma_z=sum(z);
soma_w_quad=sum(w.^2); soma_wz=sum(w.*z); w_med=soma_w/n; z_med=soma_z/n;
% Calculo dos coeficientes
a1=(n*soma_wz-soma_w*soma_z)/(n*soma_w_quad-(soma_w)^2); % Calculo do coeficiente angular
a0=z_med-a1*w_med; % Calculo do coeficiente linear
alfa=10^a0; beta=a1;
y1=a1*x+a0; y2=alfa*x.^beta;
St=sum((z-z_med).^2); Sr=sum((z-a0-a1*w).^2);
Sy=sqrt(St/(n-1)); Sy_x=sqrt(Sr/(n-2));
Cd=(St-Sr)/St; % Coeficiente de determinacao
r=sqrt(Cd); % Coeficiente de correlacao
% Printando os valores
fprintf("a0 = %.8f\na1 = %.8f\n", a0, a1);
fprintf("alpha = %.8f\nbeta = %.8f\n", alfa, beta);
fprintf("Cd = %.8f\nr = %.8f\n", Cd, r);
% Plotando os graficos
figure(1)
plot(x, y1); hold on;
plot(x, y, 'o'); hold off;
figure(2);
plot(x, y2); hold on;
plot(x, y, 'o'); hold off;

