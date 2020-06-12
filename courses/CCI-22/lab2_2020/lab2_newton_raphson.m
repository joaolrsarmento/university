format long
epsilon1 = 0.00001; epsilon2 = 0.00001; x0 = 0.5; max = 100; condition = 0;
f=@(x) 4*sin(x) - exp(x);
df=@(x) 4*cos(x) - exp(x);
NewtonRaphson(f, df, x0, epsilon1, epsilon2, max);
function [r,i] = NewtonRaphson(f, df, x0, epsilon1, epsilon2, max)
r = x0;
if abs(f(r)) < epsilon1
    fprintf("Raiz aproximada: %.12f encontrada com %d iterações - critério de parada epsilon1\n", r, 0);
    return;
end
i = 0;
while i < max
    i = i + 1;
    previous = r;
    r = r - f(r)/df(r);
    if abs(f(r)) < epsilon1
        condition = 1;
        break
    end
    if abs(r - previous) < epsilon2
        condition = 2;
        break
    end
end
if condition == 0
    fprintf("Raiz aproximada: %.12f encontrada com %d iterações - critério de parada número de iterações\n", r, i);   
end
if condition == 1
    fprintf("Raiz aproximada: %.12f encontrada com %d iterações - critério de parada epsilon1\n", r, i);
end
if condition == 2
    fprintf("Raiz aproximada: %.12f encontrada com %d iterações - critério de parada epsilon2\n", r, i);
end
end