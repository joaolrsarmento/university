format long
epsilon1 = 0.00001; epsilon2 = 0.00001; x0 = 0; x1 = 1; condition = 0; max = 100;
f = @(x) 4*sin(x) - exp(x);
Secante(f, x0, x1, epsilon1, epsilon2, max, condition);
function [r,i] = Secante(f, x0, x1, epsilon1, epsilon2, max, condition)
if abs(f(x0)) < epsilon1
    r = x0;
    fprintf("Raiz aproximada: %.12f encontrada com %d iterações - critério de parada epsilon1\n", r, 0);
    return;
end
if abs(f(x1)) < epsilon1
    r = x1;
    fprintf("Raiz aproximada: %.12f encontrada com %d iterações - critério de parada epsilon1\n", r, 0);
end
if abs(x1-x0) < epsilon2
    r = x1;
    fprintf("Raiz aproximada: %.12f encontrada com %d iterações - critério de parada epsilon2\n", r, 0);
end
i = 0; previous1 = x1; previous2 = x0;
while i < max
    i = i + 1;
    r = previous1 - f(previous1) * (previous1-previous2)/ (f(previous1) - f(previous2));
    if abs(f(r)) < epsilon1
        condition = 1;
        break
    end
    if abs(r-previous1) < epsilon2
        condition = 2;
        break
    end
    previous2 = previous1;
    previous1 = r;
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