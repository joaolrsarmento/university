format long
f=@(x) exp(-x) - x;
phi=@(x) exp(-x);
epsilon1 = 0.0001; epsilon2 = 0.0001; max = 100; x0 = 0.55;
PontoFixo(f, phi, x0, epsilon1, epsilon2, max);
function [r,i] = PontoFixo (f, phi, x0, epsilon1, epsilon2, max)
if abs(f(x0)) < epsilon1
    fprintf("Raiz aproximada: %.12f obtida com 0 iterações - critério de parada epsilon1.\n", x0);
    return;
end
i = 0;
r = x0;
while i < max
    i = i + 1;
    previous = r;
    r = phi(r);
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
    fprintf("Raiz aproximada: %.12f obtida com %d iterações - critério de parada número de iterações.\n", r, i);
end
if condition == 1
    fprintf("Raiz aproximada: %.12f obtida com %d iterações - critério de parada epsilon1.\n", r, i);
end
if condition == 2
    fprintf("Raiz aproximada: %.12f obtida com %d iterações - critério de parada epsilon2.\n", r, i);
end

end